// AI proxy for the astronaut dashboard (no dependencies, Node 18+).
// The ESP32 cannot hold an API key, so the dashboard calls this server instead.
//
// Pick ONE backend:
//   GEMINI_API_KEY=...      node ai_server.js   (free key: https://aistudio.google.com/apikey)
//   ANTHROPIC_API_KEY=...   node ai_server.js   (Claude, paid)
//   node ai_server.js                           (no key: free local model via Ollama)
// Listens on :3000.  Endpoints:  GET /ai/health   POST /ai/chat   POST /ai/report
const http = require('http');

const PORT = process.env.PORT || 3000;
const GEMINI_KEY = process.env.GEMINI_API_KEY;
const KEY = GEMINI_KEY ? null : process.env.ANTHROPIC_API_KEY;
const OLLAMA_URL = process.env.OLLAMA_URL || 'http://localhost:11434';
const MODEL = process.env.AI_MODEL || (GEMINI_KEY ? 'gemini-flash-lite-latest' : KEY ? 'claude-sonnet-5-5' : 'qwen2.5:3b');

const CHAT_SYSTEM = `You are the on-board psychological support assistant for an astronaut on a long-duration mission.
You receive the astronaut's message plus live context: heart rate / HRV stress index versus their personal baseline, SpO2, recent check-in scores and voice-tone flags.
Rules:
- Be warm, calm and brief (2-4 sentences). Reply in the same language the astronaut writes in (Arabic or English).
- Help them express feelings: ask one gentle open question, and suggest one simple step (breathing, short break, sleep routine, contacting family).
- Use the physiological context only as a soft hint ("your heart rate has been a bit elevated"); never diagnose.
- You are NOT a doctor. Never give medication advice.
- Judge how concerning the situation is: "none", "moderate" (persistent stress, loneliness, poor sleep) or "high" (hopelessness, self-harm, panic, unsafe, or severe distress).
Respond ONLY with JSON: {"reply": "<text to the astronaut>", "concern": "none|moderate|high", "note": "<one short line for the ground team, or empty>"}`;

const REPORT_SYSTEM = `You are a flight-surgeon assistant. You get an astronaut's end-of-day health report (exercise, vitals, bone/muscle risk, psychological state).
Write a concise summary for the ground medical team in this structure:
1. Overall status (1-2 sentences)
2. Bone & muscle (exercise adherence, risk trend, any checkup need)
3. Psychological state (stress, mood, voice flags)
4. Recommendations for tomorrow (max 4 bullets)
Use only the data given; say "no data" rather than inventing numbers. Plain text, no markdown headings. Write in the language requested.`;

async function callOllama(system, messages, maxTokens) {
  const r = await fetch(OLLAMA_URL + '/api/chat', {
    method: 'POST',
    headers: { 'content-type': 'application/json' },
    body: JSON.stringify({ model: MODEL, stream: false, options: { num_predict: maxTokens }, messages: [{ role: 'system', content: system }, ...messages] }),
  });
  const j = await r.json();
  if (!r.ok) throw new Error(j.error || 'Ollama error ' + r.status);
  return j.message.content;
}

// If the main Gemini model is overloaded (503) or rate-limited (429), retry on the lighter one.
const GEMINI_FALLBACK = process.env.AI_FALLBACK_MODEL || 'gemini-flash-lite-latest';
// A stalled request on a weak connection is cut after 12 s and retried (up to 3 tries),
// instead of waiting a long time for an answer that never comes.
async function callGemini(system, messages, maxTokens) {
  const body = JSON.stringify({
    systemInstruction: { parts: [{ text: system }] },
    contents: messages.map((m) => ({ role: m.role === 'assistant' ? 'model' : 'user', parts: [{ text: m.content }] })),
    // Extra room: newer Gemini models spend part of the budget on internal thinking.
    generationConfig: { maxOutputTokens: maxTokens + 2048 },
  });
  let model = MODEL, lastErr = 'no answer';
  for (let attempt = 1; attempt <= 3; attempt++) {
    const t0 = Date.now();
    try {
      const r = await fetch('https://generativelanguage.googleapis.com/v1beta/models/' + model + ':generateContent', {
        signal: AbortSignal.timeout(12000),
        method: 'POST',
        headers: { 'content-type': 'application/json', 'x-goog-api-key': GEMINI_KEY },
        body,
      });
      const j = await r.json();
      if (r.status === 503 || r.status === 429) {
        lastErr = 'Gemini busy (' + r.status + ')';
        console.log(model + ' busy (' + r.status + '), try ' + attempt + '/3');
        model = GEMINI_FALLBACK;
        continue;
      }
      if (!r.ok) throw Object.assign(new Error((j.error && j.error.message) || 'Gemini error ' + r.status), { fatal: true });
      console.log(model + ' answered in ' + (Date.now() - t0) + ' ms' + (attempt > 1 ? ' (try ' + attempt + ')' : ''));
      const parts = (j.candidates && j.candidates[0] && j.candidates[0].content && j.candidates[0].content.parts) || [];
      return parts.filter((p) => p.text && !p.thought).map((p) => p.text).join('');
    } catch (e) {
      if (e.fatal) throw e;
      lastErr = 'Gemini did not answer in time (slow internet?)';
      console.log(model + ' stalled after ' + (Date.now() - t0) + ' ms, try ' + attempt + '/3');
      model = GEMINI_FALLBACK;
    }
  }
  throw new Error(lastErr);
}

async function callClaude(system, messages, maxTokens) {
  if (GEMINI_KEY) return callGemini(system, messages, maxTokens);
  if (!KEY) return callOllama(system, messages, maxTokens);
  const r = await fetch(process.env.ANTHROPIC_URL || 'https://api.anthropic.com/v1/messages', {
    method: 'POST',
    headers: { 'content-type': 'application/json', 'x-api-key': KEY, 'anthropic-version': '2023-06-01' },
    body: JSON.stringify({ model: MODEL, max_tokens: maxTokens, system, messages }),
  });
  const j = await r.json();
  if (!r.ok) throw new Error((j.error && j.error.message) || 'API error ' + r.status);
  return j.content.filter((b) => b.type === 'text').map((b) => b.text).join('');
}

function readBody(req) {
  return new Promise((resolve, reject) => {
    let s = '';
    req.on('data', (c) => { s += c; if (s.length > 200000) { reject(new Error('too large')); req.destroy(); } });
    req.on('end', () => { try { resolve(JSON.parse(s || '{}')); } catch (e) { reject(e); } });
  });
}

http.createServer(async (req, res) => {
  const cors = {
    'Access-Control-Allow-Origin': '*',
    'Access-Control-Allow-Headers': 'content-type',
    'Access-Control-Allow-Methods': 'GET,POST,OPTIONS',
    'Access-Control-Allow-Private-Network': 'true',
  };
  const send = (code, obj) => { res.writeHead(code, { ...cors, 'content-type': 'application/json' }); res.end(JSON.stringify(obj)); };
  if (req.method === 'OPTIONS') { res.writeHead(204, cors); return res.end(); }
  const path = new URL(req.url, 'http://x').pathname;
  try {
    if (path === '/ai/health') {
      if (GEMINI_KEY || KEY) return send(200, { ok: true, model: MODEL });
      const ok = await fetch(OLLAMA_URL + '/api/tags').then((r) => r.json()).then((j) => (j.models || []).some((m) => m.name === MODEL)).catch(() => false);
      return send(200, { ok, model: MODEL + ' (free, local)' });
    }
    if (path === '/ai/chat' && req.method === 'POST') {
      const { message, context, history } = await readBody(req);
      const msgs = (Array.isArray(history) ? history : []).slice(-10).map((m) => ({ role: m.role === 'assistant' ? 'assistant' : 'user', content: String(m.text || '') }));
      msgs.push({ role: 'user', content: 'LIVE CONTEXT:\n' + JSON.stringify(context || {}) + '\n\nASTRONAUT SAYS:\n' + String(message || '') });
      // Keep roles alternating (drop leading assistant turns).
      while (msgs.length && msgs[0].role !== 'user') msgs.shift();
      const text = await callClaude(CHAT_SYSTEM, msgs, 500);
      let out;
      try { out = JSON.parse(text.slice(text.indexOf('{'), text.lastIndexOf('}') + 1)); }
      catch (e) { out = { reply: text, concern: 'none', note: '' }; }
      return send(200, out);
    }
    if (path === '/ai/report' && req.method === 'POST') {
      const { report, lang } = await readBody(req);
      const text = await callClaude(REPORT_SYSTEM + '\nLanguage: ' + (lang || 'English'), [{ role: 'user', content: String(report || '') }], 900);
      return send(200, { summary: text });
    }
    send(404, { error: 'not found' });
  } catch (e) {
    send(500, { error: String(e.message || e) });
  }
}).listen(PORT, () => console.log('AI proxy on :' + PORT + ' model=' + MODEL + (GEMINI_KEY ? '  (Google Gemini)' : KEY ? '  (Claude)' : '  (no API key: using free local Ollama at ' + OLLAMA_URL + ')')));
