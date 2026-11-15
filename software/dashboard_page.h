#ifndef DASHBOARD_PAGE_H
#define DASHBOARD_PAGE_H
 
const char DASHBOARD_PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0, viewport-fit=cover" />
  <title>Patient  Health Monitor</title>
  <link rel="preconnect" href="https://fonts.googleapis.com" />
  <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin />
  <link href="https://fonts.googleapis.com/css2?family=Plus+Jakarta+Sans:wght@500;600;700;800&display=swap" rel="stylesheet" />
  <style>
    :root {
      --bg-1: #eef4ff;
      --bg-2: #e8f0fe;
      --sidebar: #0f172a;
      --sidebar-hover: #1e293b;
      --sidebar-active: #2563eb;
      --card: rgba(255,255,255,0.94);
      --text: #0f172a;
      --muted: #64748b;
      --blue: #2563eb;
      --cyan: #06b6d4;
      --green: #16a34a;
      --red: #ef4444;
      --orange: #f59e0b;
      --green-soft: #dcfce7;
      --red-soft: #fee2e2;
      --orange-soft: #fef3c7;
      --blue-soft: #dbeafe;
      --shadow: 0 20px 50px rgba(15,23,42,0.14);
      --radius: 18px;
    }
    * { margin: 0; padding: 0; box-sizing: border-box; }
    html, body { height: 100%; width: 100%; overflow: hidden; }
    body {
      font-family: "Plus Jakarta Sans", "Segoe UI", system-ui, sans-serif;
      color: var(--text);
      background:
        radial-gradient(circle at 8% 10%, rgba(37,99,235,0.18), transparent 30%),
        radial-gradient(circle at 92% 8%, rgba(6,182,212,0.16), transparent 28%),
        linear-gradient(135deg, var(--bg-1), var(--bg-2));
      display: flex;
      align-items: center;
      justify-content: center;
      padding: 0;
    }
    .viewport-wrap {
      aspect-ratio: 15 / 9;
      width: min(100vw, calc(100vh * 15 / 9));
      height: min(100vh, calc(100vw * 9 / 15));
    }
    .app-shell {
      width: 100%;
      height: 100%;
      display: flex;
      border-radius: 0;
      overflow: hidden;
      box-shadow: none;
      border: none;
      background: var(--card);
    }
    .sidebar {
      width: 210px;
      flex-shrink: 0;
      background: linear-gradient(180deg, #0b1224 0%, #111827 55%, #0f172a 100%);
      color: #e2e8f0;
      display: flex;
      flex-direction: column;
      padding: 18px 12px;
      border-right: 1px solid rgba(255,255,255,0.06);
    }
    .sidebar-brand {
      display: flex;
      align-items: center;
      gap: 10px;
      padding: 8px 10px 20px;
      border-bottom: 1px solid rgba(255,255,255,0.08);
      margin-bottom: 14px;
    }
    .sidebar-logo {
      width: 42px; height: 42px; border-radius: 13px;
      background: linear-gradient(135deg, #f43f5e 0%, #e11d48 50%, #be123c 100%);
      display: grid; place-items: center;
      box-shadow: 0 6px 18px rgba(244,63,94,0.45);
      flex-shrink: 0;
    }
    .sidebar-logo svg {
      width: 24px; height: 24px;
      fill: none; stroke: #fff;
      stroke-width: 2.2; stroke-linecap: round; stroke-linejoin: round;
    }
    .sidebar-brand strong {
      display: block; font-size: 0.88rem; letter-spacing: -0.02em;
      background: linear-gradient(90deg, #fff, #fda4af);
      -webkit-background-clip: text; -webkit-text-fill-color: transparent;
      background-clip: text;
    }
    .sidebar-brand span {
      font-size: 0.68rem; color: #94a3b8;
    }
    .nav-label {
      font-size: 0.65rem; text-transform: uppercase;
      letter-spacing: 0.1em; color: #64748b;
      padding: 0 10px; margin-bottom: 8px;
    }
    .nav { flex: 1; display: flex; flex-direction: column; gap: 4px; }
    .nav-item {
      border: none; background: transparent; color: #cbd5e1;
      text-align: left; padding: 10px 12px;
      border-radius: 12px; font-size: 0.84rem; font-weight: 700;
      cursor: pointer; display: flex; align-items: center; gap: 10px;
      transition: background 0.15s, color 0.15s, transform 0.12s;
    }
    .nav-item:hover { background: var(--sidebar-hover); color: #fff; transform: translateX(2px); }
    .nav-item.active {
      background: linear-gradient(90deg, #2563eb, #3b82f6);
      color: #fff;
      box-shadow: 0 8px 22px rgba(37,99,235,0.4);
    }
    .nav-icon-wrap {
      width: 30px; height: 30px; border-radius: 9px;
      display: grid; place-items: center;
      font-size: 14px; flex-shrink: 0;
      background: rgba(255,255,255,0.08);
    }
    .nav-item.active .nav-icon-wrap { background: rgba(255,255,255,0.22); }
    .nav-item[data-page="dashboard"] .nav-icon-wrap { background: rgba(244,63,94,0.2); }
    .nav-item[data-page="patient"] .nav-icon-wrap { background: rgba(59,130,246,0.2); }
    .nav-item[data-page="logging"] .nav-icon-wrap { background: rgba(16,185,129,0.2); }
    .nav-item[data-page="alerts"] .nav-icon-wrap { background: rgba(245,158,11,0.2); }
    .nav-icon { width: auto; text-align: center; opacity: 1; }
    .sidebar-foot {
      padding: 12px 10px 4px;
      border-top: 1px solid rgba(255,255,255,0.08);
      font-size: 0.72rem; color: #94a3b8;
    }
    .live-pill {
      display: flex; align-items: center; gap: 7px;
      margin-bottom: 6px; font-weight: 800; color: #e2e8f0;
    }
    .live-dot {
      width: 8px; height: 8px; border-radius: 50%;
      background: var(--green);
      animation: pulse 1.5s infinite;
    }
    .live-dot.off { background: var(--red); animation: none; }
    @keyframes pulse {
      0% { box-shadow: 0 0 0 0 rgba(22,163,74,0.5); }
      75% { box-shadow: 0 0 0 8px rgba(22,163,74,0); }
      100% { box-shadow: 0 0 0 0 rgba(22,163,74,0); }
    }
    .main {
      flex: 1; min-width: 0;
      display: flex; flex-direction: column;
      background: linear-gradient(180deg, #fafbff, #f1f5f9);
    }
    .topbar {
      flex-shrink: 0;
      padding: 10px 16px;
      display: flex; justify-content: space-between; align-items: center;
      gap: 12px;
      border-bottom: 1px solid rgba(148,163,184,0.15);
      background: linear-gradient(90deg, rgba(255,255,255,0.98), rgba(239,246,255,0.98));
    }
    .topbar h1 {
      font-size: 1.12rem; letter-spacing: -0.03em; font-weight: 800;
    }
    .topbar p { font-size: 0.76rem; color: var(--muted); margin-top: 2px; font-weight: 600; }
    .topbar-actions {
      display: flex; align-items: center; gap: 12px;
      flex-shrink: 0;
    }
    .topbar-meta {
      text-align: right; font-size: 0.72rem; color: var(--muted); font-weight: 700;
    }
    .topbar-meta strong { display: block; color: var(--text); font-size: 0.86rem; font-weight: 800; }
    .sound-toggle {
      width: 36px; height: 36px;
      border-radius: 11px;
      border: 1.5px solid #e2e8f0;
      background: #fff;
      color: #64748b;
      font-size: 16px; line-height: 1;
      cursor: pointer;
      display: grid; place-items: center;
      transition: background 0.15s, border-color 0.15s, color 0.15s, transform 0.12s;
      flex-shrink: 0;
    }
    .sound-toggle:hover { background: #f8fafc; border-color: #cbd5e1; }
    .sound-toggle:active { transform: scale(0.94); }
    .sound-toggle.muted { opacity: 0.5; background: #f1f5f9; }
    .sound-toggle:not(.muted) {
      background: #eff6ff;
      border-color: #93c5fd;
      color: #2563eb;
    }
    .sound-toggle svg {
      width: 18px; height: 18px;
      stroke: currentColor; fill: none;
      stroke-width: 2; stroke-linecap: round; stroke-linejoin: round;
    }
    .sound-toggle .sound-off { display: none; }
    .sound-toggle.muted .sound-on { display: none; }
    .sound-toggle.muted .sound-off { display: block; }
    .topbar-actions .sound-toggle + .topbar-meta {
      padding-left: 12px;
      border-left: 1px solid #e2e8f0;
    }
    .page-area {
      flex: 1; min-height: 0;
      overflow: hidden; position: relative;
    }
    .page {
      display: none;
      position: absolute;
      inset: 0;
      overflow-y: auto;
      overflow-x: hidden;
      padding: 14px 18px 16px;
      -webkit-overflow-scrolling: touch;
    }
    .page.active {
      display: block;
      z-index: 1;
    }
    #page-patient.page.active {
      display: flex;
      flex-direction: column;
      overflow: hidden;
      padding: 10px 14px 12px;
      background: linear-gradient(180deg, #f0f4fa 0%, #e8eef6 100%);
    }
    .record-page {
      flex: 1; min-height: 0;
      display: flex; flex-direction: column; gap: 10px;
      overflow: hidden;
    }
    .record-banner {
      flex-shrink: 0;
      position: relative; overflow: hidden;
      border-radius: 18px;
      padding: 0;
    }
    .record-banner-bg {
      position: absolute; inset: 0;
      background: linear-gradient(120deg, #1e3a8a 0%, #2563eb 45%, #0891b2 100%);
    }
    .record-banner-bg::after {
      content: "";
      position: absolute; inset: 0;
      background:
        radial-gradient(circle at 85% 20%, rgba(255,255,255,0.2), transparent 42%),
        radial-gradient(circle at 12% 88%, rgba(255,255,255,0.12), transparent 38%);
    }
    .record-profile {
      position: relative; z-index: 1;
      display: flex; align-items: center; gap: 14px;
      padding: 16px 18px;
      color: #fff;
    }
    .record-avatar-ring {
      padding: 3px;
      border-radius: 20px;
      background: linear-gradient(135deg, rgba(255,255,255,0.95), rgba(255,255,255,0.35));
      flex-shrink: 0;
    }
    .record-profile .patient-avatar {
      width: 68px; height: 68px;
      border-radius: 16px;
      font-size: 1.4rem;
      box-shadow: 0 8px 20px rgba(0,0,0,0.2);
    }
    .record-profile-main { flex: 1; min-width: 0; }
    .record-profile-main h2 {
      margin: 0 0 8px;
      font-size: 1.45rem; font-weight: 900;
      letter-spacing: -0.03em;
      line-height: 1.15;
      word-break: break-word;
    }
    .record-profile .patient-chips {
      display: flex; flex-wrap: wrap; gap: 6px;
    }
    .record-profile .patient-chip {
      font-size: 0.78rem; font-weight: 800;
      padding: 5px 11px;
      border-radius: 999px;
      background: rgba(255,255,255,0.18);
      border: 1px solid rgba(255,255,255,0.35);
      color: #fff;
    }
    .record-profile .patient-chip.loc {
      color: #e0f2fe;
    }
    .btn-glow {
      flex-shrink: 0;
      box-shadow: 0 6px 20px rgba(15,23,42,0.25);
      background: #fff !important;
      color: #1d4ed8 !important;
      font-weight: 900;
      padding: 10px 16px;
      font-size: 0.8rem;
      white-space: nowrap;
    }
    .record-scroll {
      flex: 1; min-height: 0;
      overflow-y: auto;
      overflow-x: hidden;
      -webkit-overflow-scrolling: touch;
      display: flex; flex-direction: column; gap: 10px;
      padding-bottom: 4px;
    }
    .record-section-title {
      font-size: 0.72rem; font-weight: 900;
      text-transform: uppercase; letter-spacing: 0.08em;
      color: var(--muted);
      margin: 0 0 8px 2px;
    }
    .record-stats-row {
      display: grid;
      grid-template-columns: repeat(3, 1fr);
      gap: 8px;
    }
    .record-stat {
      padding: 14px 10px;
      border-radius: 14px;
      text-align: center;
      display: flex; flex-direction: column; align-items: center; gap: 6px;
    }
    .record-stat-icon {
      width: 40px; height: 40px; border-radius: 12px;
      display: grid; place-items: center;
      font-size: 18px;
    }
    .record-stat.rc-age { background: linear-gradient(180deg, #eff6ff, #fff); border: 1px solid #bfdbfe; }
    .record-stat.rc-age .record-stat-icon { background: #dbeafe; }
    .record-stat.rc-gender { background: linear-gradient(180deg, #fdf2f8, #fff); border: 1px solid #fbcfe8; }
    .record-stat.rc-gender .record-stat-icon { background: #fce7f3; }
    .record-stat.rc-blood { background: linear-gradient(180deg, #fef2f2, #fff); border: 1px solid #fecaca; }
    .record-stat.rc-blood .record-stat-icon { background: #fee2e2; }
    .record-stat-label {
      font-size: 0.65rem; font-weight: 800;
      text-transform: uppercase; letter-spacing: 0.06em;
      color: var(--muted);
    }
    .record-stat-value {
      font-size: 1.05rem; font-weight: 900;
      color: var(--text); line-height: 1.2;
      word-break: break-word;
    }
    .record-contact-row {
      display: grid;
      grid-template-columns: 1fr 1fr;
      gap: 8px;
    }
    .record-detail-card {
      padding: 14px 16px;
      border-radius: 14px;
      display: flex; align-items: center; gap: 12px;
    }
    .record-detail-card.rc-phone {
      background: linear-gradient(135deg, #ecfdf5, #fff);
      border: 1px solid #bbf7d0;
    }
    .record-detail-card.rc-id {
      background: linear-gradient(135deg, #f5f3ff, #fff);
      border: 1px solid #ddd6fe;
    }
    .record-detail-card .field-icon {
      width: 38px; height: 38px; font-size: 16px; border-radius: 11px;
      flex-shrink: 0;
    }
    .record-detail-label {
      font-size: 0.65rem; font-weight: 800;
      text-transform: uppercase; letter-spacing: 0.05em;
      color: var(--muted);
    }
    .record-detail-value {
      font-size: 0.95rem; font-weight: 800;
      color: var(--text); margin-top: 2px;
      word-break: break-word;
    }
    .record-notes-card {
      padding: 14px 16px;
      border-radius: 14px;
      background: linear-gradient(180deg, #fffbeb, #ffffff);
      border: 1px solid #fde68a;
    }
    .record-notes-card .record-section-title { margin-bottom: 10px; }
    .record-notes-body {
      padding: 12px 14px;
      background: #fff;
      border-radius: 10px;
      border: 1px solid #fef3c7;
      font-size: 0.92rem; font-weight: 600;
      color: #475569; line-height: 1.55;
      min-height: 88px;
      word-break: break-word;
    }
    #page-logging.page.active,
    #page-alerts.page.active {
      display: flex;
      flex-direction: column;
      overflow: hidden;
      padding: 10px 14px 12px;
      gap: 10px;
      background: linear-gradient(180deg, #f0f4fa 0%, #e8eef6 100%);
    }
    .logging-page, .alerts-page {
      flex: 1; min-height: 0;
      display: flex; flex-direction: column; gap: 10px;
    }
    .logging-toolbar {
      flex-shrink: 0;
      padding: 14px 16px;
      display: flex; align-items: center; justify-content: space-between;
      gap: 12px; flex-wrap: wrap;
      border-radius: 16px;
    }
    .logging-controls {
      display: flex; align-items: center; gap: 10px; flex-wrap: wrap;
    }
    .logging-controls label {
      font-size: 0.72rem; font-weight: 900;
      text-transform: uppercase; letter-spacing: 0.06em;
      color: var(--muted);
    }
    .logging-controls select {
      padding: 9px 12px; border-radius: 10px;
      border: 1px solid #e2e8f0; background: #fff;
      font-size: 0.85rem; font-weight: 700;
      font-family: inherit; color: var(--text);
    }
    .btn-log { padding: 9px 14px; font-size: 0.78rem; }
    .btn-log-start { background: #16a34a; color: #fff; }
    .btn-log-stop { background: #ef4444; color: #fff; }
    .btn-log-export { background: #2563eb; color: #fff; }
    .logging-stats {
      display: flex; align-items: center; gap: 14px;
      font-size: 0.78rem; font-weight: 800; color: var(--muted);
    }
    .log-status-pill {
      padding: 5px 12px; border-radius: 999px;
      font-size: 0.68rem; font-weight: 900;
      letter-spacing: 0.05em; text-transform: uppercase;
    }
    .log-status-pill.stopped { background: #f1f5f9; color: #64748b; }
    .log-status-pill.running { background: #dcfce7; color: #16a34a; }
    .logging-table-wrap {
      flex: 1; min-height: 0;
      overflow: hidden;
      border-radius: 16px;
      display: flex; flex-direction: column;
    }
    .logging-table-head {
      flex-shrink: 0;
      padding: 12px 16px;
      border-bottom: 1px solid #e2e8f0;
      display: flex; justify-content: space-between; align-items: center;
    }
    .logging-table-head h4 {
      font-size: 0.85rem; font-weight: 900;
      display: flex; align-items: center; gap: 8px;
    }
    .logging-table-scroll {
      flex: 1; min-height: 0; overflow: auto;
      -webkit-overflow-scrolling: touch;
    }
    .log-table {
      width: 100%; border-collapse: collapse;
      font-size: 0.78rem;
    }
    .log-table th {
      position: sticky; top: 0; z-index: 1;
      background: #f1f5f9;
      padding: 10px 12px;
      text-align: left; font-weight: 900;
      color: #475569; text-transform: uppercase;
      letter-spacing: 0.05em; font-size: 0.68rem;
      border-bottom: 2px solid #e2e8f0;
    }
    .log-table td {
      padding: 9px 12px;
      border-bottom: 1px solid #f1f5f9;
      font-weight: 600; color: var(--text);
    }
    .log-table tbody tr:nth-child(even) { background: #fafbfc; }
    .log-table tbody tr:hover { background: #eff6ff; }
    .log-empty {
      padding: 40px; text-align: center;
      color: var(--muted); font-weight: 700; font-size: 0.85rem;
    }
    .alerts-hero {
      flex-shrink: 0;
      padding: 14px 16px;
      display: flex; justify-content: space-between; align-items: center;
      gap: 12px;
      border-radius: 16px;
      background: linear-gradient(120deg, #7f1d1d 0%, #dc2626 40%, #ea580c 100%);
      color: #fff;
      box-shadow: 0 8px 28px rgba(220,38,38,0.25);
    }
    .alerts-hero h3 {
      font-size: 1.05rem; font-weight: 900;
      letter-spacing: -0.02em; margin: 0 0 3px;
      color: #fff;
    }
    .alerts-hero p {
      font-size: 0.72rem; color: rgba(255,255,255,0.85); margin: 0;
      font-weight: 600;
    }
    .alerts-status-badge {
      font-size: 0.68rem; font-weight: 900;
      padding: 8px 14px; border-radius: 999px;
      letter-spacing: 0.06em; text-transform: uppercase;
      flex-shrink: 0;
      background: rgba(255,255,255,0.95);
    }
    .alerts-status-badge.good { color: #16a34a; }
    .alerts-status-badge.watch { color: #b45309; }
    .alerts-status-badge.bad { color: #ef4444; }
    .alerts-summary {
      flex-shrink: 0;
      display: grid;
      grid-template-columns: repeat(3, 1fr);
      gap: 8px;
    }
    .alerts-summary-card {
      padding: 10px 12px;
      border-radius: 12px;
      text-align: center;
      font-size: 0.65rem; font-weight: 800;
      text-transform: uppercase; letter-spacing: 0.05em;
    }
    .alerts-summary-card span {
      display: block;
      font-size: 1.35rem; font-weight: 1000;
      letter-spacing: -0.04em;
      margin-bottom: 2px;
    }
    .alerts-summary-card.warn { background: #fff7ed; border: 1px solid #fdba74; color: #c2410c; }
    .alerts-summary-card.warn span { color: #ea580c; }
    .alerts-summary-card.ok { background: #f0fdf4; border: 1px solid #86efac; color: #15803d; }
    .alerts-summary-card.ok span { color: #16a34a; }
    .alerts-summary-card.info { background: #eff6ff; border: 1px solid #93c5fd; color: #1d4ed8; }
    .alerts-summary-card.info span { color: #2563eb; }
    .alerts-scroll {
      flex: 1; min-height: 0;
      overflow-y: auto;
      overflow-x: hidden;
      -webkit-overflow-scrolling: touch;
      display: flex; flex-direction: column; gap: 12px;
      padding-bottom: 4px;
    }
    .alerts-section-title {
      font-size: 0.7rem; font-weight: 900;
      text-transform: uppercase; letter-spacing: 0.08em;
      color: var(--muted);
      margin: 0 0 8px 2px;
      display: flex; align-items: center; gap: 6px;
    }
    .alert-row {
      display: flex; gap: 12px; align-items: flex-start;
      padding: 12px 14px;
      border-radius: 14px;
      margin-bottom: 8px;
      border: 1px solid #e8eef5;
      background: #fff;
      transition: box-shadow 0.15s;
    }
    .alert-row:last-child { margin-bottom: 0; }
    .alert-row.alert-ok { border-left: 4px solid #22c55e; background: linear-gradient(90deg, #f0fdf4, #fff); }
    .alert-row.alert-warn { border-left: 4px solid #f59e0b; background: linear-gradient(90deg, #fffbeb, #fff); }
    .alert-row.alert-bad { border-left: 4px solid #ef4444; background: linear-gradient(90deg, #fef2f2, #fff); }
    .alert-row.alert-info { border-left: 4px solid #3b82f6; background: linear-gradient(90deg, #eff6ff, #fff); }
    .alert-row-icon {
      width: 42px; height: 42px; flex-shrink: 0;
      border-radius: 12px;
      display: grid; place-items: center;
      font-size: 20px;
    }
    .alert-row.alert-ok .alert-row-icon { background: #dcfce7; }
    .alert-row.alert-warn .alert-row-icon { background: #fef3c7; }
    .alert-row.alert-bad .alert-row-icon { background: #fee2e2; }
    .alert-row.alert-info .alert-row-icon { background: #dbeafe; }
    .alert-row-body { flex: 1; min-width: 0; }
    .alert-row-top {
      display: flex; align-items: flex-start; justify-content: space-between;
      gap: 8px; margin-bottom: 4px;
    }
    .alert-row-top strong {
      font-size: 0.88rem; color: var(--text); line-height: 1.3;
    }
    .alert-pill {
      flex-shrink: 0;
      font-size: 0.58rem; font-weight: 900;
      padding: 3px 8px; border-radius: 999px;
      letter-spacing: 0.05em; text-transform: uppercase;
    }
    .alert-pill.ok { background: #dcfce7; color: #16a34a; }
    .alert-pill.warn { background: #fef3c7; color: #b45309; }
    .alert-pill.bad { background: #fee2e2; color: #ef4444; }
    .alert-pill.info { background: #dbeafe; color: #2563eb; }
    .alert-row-body > p {
      font-size: 0.78rem; color: #475569;
      line-height: 1.4; margin: 0 0 6px; font-weight: 600;
    }
    .alert-tip {
      font-size: 0.72rem; color: #64748b;
      line-height: 1.4; margin: 0;
      padding: 7px 10px;
      background: rgba(255,255,255,0.7);
      border-radius: 8px;
      border: 1px dashed #cbd5e1;
      font-weight: 600;
    }
    .alert-tip::before { content: "💡 "; }
    .alerts-suggestions {
      padding: 14px 16px;
      border-radius: 14px;
      background: linear-gradient(135deg, #eff6ff, #f0fdf4);
      border: 1px solid #bfdbfe;
    }
    .alerts-suggestions .alerts-section-title { color: #1d4ed8; }
    .alert-suggest-list {
      list-style: none; margin: 0; padding: 0;
      display: flex; flex-direction: column; gap: 8px;
    }
    .alert-suggest-list li {
      font-size: 0.78rem; font-weight: 600;
      color: #334155; line-height: 1.45;
      padding: 9px 12px 9px 32px;
      background: #fff;
      border-radius: 10px;
      border: 1px solid #e2e8f0;
      position: relative;
    }
    .alert-suggest-list li::before {
      content: "✓";
      position: absolute; left: 10px; top: 9px;
      width: 18px; height: 18px; border-radius: 50%;
      background: #dbeafe; color: #2563eb;
      font-size: 0.62rem; font-weight: 900;
      display: grid; place-items: center;
    }
    .patient-page {
      flex: 1; min-height: 0;
      display: flex; flex-direction: column;
    }
    .patient-panel {
      flex: 1; min-height: 0;
      display: flex; flex-direction: column;
      overflow: hidden;
      padding: 0;
    }
    .patient-hero {
      flex-shrink: 0;
      padding: 16px 20px;
      background: linear-gradient(120deg, #eff6ff 0%, #ecfeff 45%, #ffffff 100%);
      border-bottom: 1px solid rgba(148, 163, 184, 0.25);
      display: flex; align-items: center; gap: 18px;
    }
    .patient-avatar {
      width: 76px; height: 76px; flex-shrink: 0;
      border-radius: 18px;
      background: linear-gradient(145deg, var(--blue), var(--cyan));
      color: #fff; font-size: 1.55rem; font-weight: 900;
      display: grid; place-items: center;
      box-shadow: 0 10px 24px rgba(37, 99, 235, 0.28);
      letter-spacing: 0.02em;
    }
    .patient-hero-main { flex: 1; min-width: 0; }
    .patient-hero-main h2 {
      margin: 0 0 10px; font-size: 1.65rem; font-weight: 900;
      letter-spacing: -0.03em; line-height: 1.15;
      white-space: nowrap; overflow: hidden; text-overflow: ellipsis;
    }
    .patient-chips { display: flex; flex-wrap: wrap; gap: 8px; }
    .patient-chip {
      font-size: 0.88rem; font-weight: 800; padding: 7px 14px;
      border-radius: 999px; background: rgba(255,255,255,0.92);
      border: 1px solid #dbeafe; color: #1d4ed8;
    }
    .patient-chip.loc { border-color: #99f6e4; color: #0f766e; }
    .patient-hero .btn {
      flex-shrink: 0; padding: 12px 20px; font-size: 0.92rem;
    }
    .patient-body {
      flex: 1; min-height: 0;
      display: grid;
      grid-template-columns: 1fr 1fr 1.15fr;
      gap: 12px;
      padding: 12px 14px 14px;
      overflow: hidden;
      align-items: stretch;
    }
    .patient-section {
      background: #f8fafc;
      border: 1px solid #e8eef5;
      border-radius: 14px;
      padding: 16px 18px;
      display: flex; flex-direction: column;
      min-height: 0;
      justify-content: center;
    }
    .patient-section-title {
      font-size: 0.8rem; font-weight: 900; color: var(--muted);
      text-transform: uppercase; letter-spacing: 0.09em;
      margin: 0 0 12px; padding-bottom: 10px;
      border-bottom: 1px solid #e2e8f0;
      flex-shrink: 0;
    }
    .patient-section-rows {
      flex: 1; display: flex; flex-direction: column;
      justify-content: space-evenly; min-height: 0;
    }
    .detail-row {
      display: flex; align-items: center; justify-content: space-between;
      gap: 12px; padding: 11px 0;
      border-bottom: 1px solid rgba(226, 232, 240, 0.7);
    }
    .detail-row:last-child { border-bottom: none; }
    .detail-row .detail-label {
      display: flex; align-items: center; gap: 10px;
      font-size: 0.95rem; color: #64748b; font-weight: 700;
    }
    #page-patient .detail-row .field-icon {
      width: 32px; height: 32px; font-size: 16px; border-radius: 9px;
    }
    .detail-row .detail-value {
      font-size: 1.08rem; font-weight: 800; color: var(--text);
      text-align: right; word-break: break-word;
    }
    .notes-box {
      flex: 1; min-height: 0;
      margin-top: 6px; padding: 14px 16px;
      background: #fff; border-radius: 12px;
      border: 1px solid #e2e8f0;
      font-size: 1rem; font-weight: 600; color: #475569;
      line-height: 1.5; overflow-y: auto;
      display: flex; align-items: flex-start;
    }
    .patient-modal {
      display: none;
      position: fixed; inset: 0; z-index: 200;
      align-items: center; justify-content: center;
      padding: 16px;
    }
    .patient-modal.open { display: flex; }
    .patient-modal-backdrop {
      position: absolute; inset: 0;
      background: rgba(15, 23, 42, 0.5);
    }
    .patient-modal-card {
      position: relative; z-index: 1;
      width: min(580px, 100%);
      max-height: min(92vh, 640px);
      overflow-y: auto;
      padding: 18px 20px 20px;
    }
    .patient-modal-head {
      display: flex; justify-content: space-between; align-items: center;
      margin-bottom: 14px; padding-bottom: 10px;
      border-bottom: 1px solid #e2e8f0;
    }
    .patient-modal-head h3 {
      font-size: 0.98rem; margin: 0;
      display: flex; align-items: center; gap: 8px;
    }
    .btn-icon {
      width: 32px; height: 32px; border-radius: 10px;
      border: 1px solid #e2e8f0; background: #fff;
      color: var(--muted); font-size: 1.1rem; cursor: pointer;
      display: grid; place-items: center; line-height: 1;
    }
    #page-dashboard.page.active {
      display: flex;
      flex-direction: column;
      overflow: hidden;
      padding: 10px 14px 12px;
      gap: 10px;
      z-index: 2;
      background:
        radial-gradient(ellipse 70% 45% at 15% 0%, rgba(244,63,94,0.08), transparent),
        radial-gradient(ellipse 60% 40% at 85% 5%, rgba(37,99,235,0.1), transparent),
        radial-gradient(ellipse 50% 35% at 50% 100%, rgba(6,182,212,0.08), transparent),
        linear-gradient(180deg, #f8faff 0%, #eef2ff 100%);
    }
    .med-dash {
      flex: 1; min-height: 0;
      display: flex; flex-direction: column; gap: 10px;
    }
    .med-status-bar {
      flex-shrink: 0;
      display: flex; align-items: center;
      gap: 8px;
      padding: 8px 10px;
      border-radius: 14px;
      background: #0f172a;
      color: #e2e8f0;
      border: 1px solid #1e293b;
      overflow: hidden;
    }
    .med-status-pill {
      display: flex; align-items: center; gap: 7px;
      padding: 6px 11px;
      border-radius: 999px;
      font-size: 0.68rem; font-weight: 800;
      letter-spacing: 0.05em;
      text-transform: uppercase;
      white-space: nowrap;
      flex-shrink: 0;
    }
    .med-status-pill.live-pill-dash {
      background: rgba(34,197,94,0.15);
      border: 1px solid rgba(34,197,94,0.35);
      color: #86efac;
    }
    .med-status-pill.ward-pill-dash {
      background: rgba(59,130,246,0.12);
      border: 1px solid rgba(59,130,246,0.3);
      color: #93c5fd;
    }
    .med-status-pill.ward-pill-dash svg {
      width: 14px; height: 14px;
      stroke: currentColor; fill: none;
      stroke-width: 2; stroke-linecap: round; stroke-linejoin: round;
    }
    .med-status-patient {
      flex: 1; min-width: 0;
      display: flex; align-items: center; gap: 8px;
      margin-left: auto;
      padding: 6px 12px 6px 8px;
      border-radius: 999px;
      background: rgba(255,255,255,0.1);
      border: 1px solid rgba(255,255,255,0.18);
    }
    .med-status-patient .med-chip-icon {
      background: #3b82f6;
      color: #fff;
      font-size: 12px;
    }
    #dashPatientName {
      font-size: 0.78rem; font-weight: 800;
      text-transform: none; letter-spacing: -0.01em;
      color: #fff;
      white-space: nowrap; overflow: hidden; text-overflow: ellipsis;
      min-width: 0;
      flex: 1;
    }
    .med-status-dot {
      width: 8px; height: 8px; border-radius: 50%;
      background: #22c55e;
      animation: statusPulse 2s infinite;
      flex-shrink: 0;
    }
    @keyframes statusPulse {
      0%, 100% { opacity: 1; }
      50% { opacity: 0.5; }
    }
    .med-chip-icon {
      width: 28px; height: 28px; border-radius: 8px;
      background: rgba(255,255,255,0.14);
      display: grid; place-items: center; font-size: 13px;
      flex-shrink: 0;
    }
    .med-chip-icon svg {
      width: 15px; height: 15px;
      stroke: currentColor; fill: none;
      stroke-width: 2; stroke-linecap: round; stroke-linejoin: round;
    }
    .med-vitals-grid {
      flex-shrink: 0;
      display: grid;
      grid-template-columns: 1.15fr 1.15fr 0.85fr;
      gap: 10px;
      min-height: 0;
    }
    .med-vital {
      display: flex; align-items: center; gap: 14px;
      padding: 16px 18px;
      border-radius: 16px;
      position: relative;
      min-height: 112px;
      box-shadow: none !important;
      transition: border-color 0.25s ease;
    }
    .med-vital-heart {
      background: #fff1f2;
      border: 1.5px solid #fecdd3;
    }
    .med-vital-spo2 {
      background: #eff6ff;
      border: 1.5px solid #bfdbfe;
    }
    .med-vital-icon-wrap {
      flex-shrink: 0;
      width: 56px;
      display: flex; align-items: center; justify-content: center;
    }
    .vital-icon-box {
      width: 52px; height: 52px;
      border-radius: 14px;
      display: grid; place-items: center;
      transform-origin: center;
      box-shadow: none;
    }
    .vital-icon-heart {
      background: #e11d48;
      color: #fff;
    }
    .vital-icon-heart.beating {
      animation: heartbeat var(--beat-dur, 0.85s) ease-in-out infinite;
      will-change: transform;
    }
    @keyframes heartbeat {
      0%, 100% { transform: scale(1); }
      14% { transform: scale(1.07); }
      28% { transform: scale(1); }
      42% { transform: scale(1.04); }
      56% { transform: scale(1); }
    }
    .vital-icon-heart svg {
      width: 26px; height: 26px;
      fill: currentColor;
    }
    .vital-icon-spo2 {
      background: #2563eb;
      color: #fff;
      animation: o2Breathe 3s ease-in-out infinite;
    }
    @keyframes o2Breathe {
      0%, 100% { transform: scale(1); }
      50% { transform: scale(1.06); }
    }
    .vital-icon-spo2 .spo2-symbol {
      font-size: 1rem; font-weight: 800;
      letter-spacing: -0.03em;
      text-shadow: none;
    }
    .med-vital-body { flex: 1; min-width: 0; }
    .med-vital-top {
      display: flex; justify-content: space-between; align-items: center;
      margin-bottom: 6px; gap: 6px;
    }
    .med-vital-title {
      font-size: 0.7rem; font-weight: 700;
      text-transform: uppercase; letter-spacing: 0.08em;
      color: #64748b;
      display: flex; align-items: center; gap: 6px;
    }
    .vt-ico {
      width: 18px; height: 18px; border-radius: 5px;
      display: grid; place-items: center;
      flex-shrink: 0;
    }
    .vt-ico svg {
      width: 11px; height: 11px;
      stroke: currentColor; fill: none;
      stroke-width: 2.2; stroke-linecap: round; stroke-linejoin: round;
    }
    .med-vital-heart .vt-ico { background: #ffe4e6; color: #e11d48; }
    .med-vital-spo2 .vt-ico { background: #dbeafe; color: #2563eb; }
    .dash-section-label {
      font-size: 0.68rem; font-weight: 800;
      text-transform: uppercase; letter-spacing: 0.1em;
      color: #94a3b8;
      padding: 0 2px;
      display: flex; align-items: center; gap: 6px;
    }
    .dash-section-label::before {
      content: "";
      width: 8px; height: 8px; border-radius: 50%;
      background: #22c55e;
      animation: statusPulse 2s infinite;
    }
    .med-vital-value {
      font-size: 2rem; font-weight: 800;
      letter-spacing: -0.04em; line-height: 1;
      margin-bottom: 4px;
      font-variant-numeric: tabular-nums;
      transition: color 0.3s ease;
    }
    #bpm.bpm-pulse {
      animation: bpmGlow 0.55s ease;
    }
    @keyframes bpmGlow {
      0%, 100% { opacity: 1; filter: none; }
      40% { opacity: 0.82; filter: brightness(1.15); }
    }
    .med-vital-value.vital-flash { animation: vitalSoft 0.45s ease; }
    .med-vital-heart .med-vital-value { color: #9f1239; }
    .med-vital-spo2 .med-vital-value { color: #1e40af; }
    .med-unit {
      font-size: 0.75rem; font-weight: 700;
      color: #94a3b8; margin-left: 3px;
      letter-spacing: 0.02em;
    }
    .med-range {
      font-size: 0.65rem; font-weight: 600;
      color: #94a3b8; margin-bottom: 8px;
    }
    .med-bar {
      height: 5px; border-radius: 999px;
      background: rgba(15,23,42,0.06); overflow: hidden;
    }
    .med-vital .bar-fill {
      height: 100%; border-radius: inherit;
      transition: width 0.55s cubic-bezier(0.4, 0, 0.2, 1);
      position: relative;
    }
    .med-vital-heart .bar-fill { background: #f43f5e; }
    .med-vital-spo2 .bar-fill { background: #3b82f6; }
    .med-vitals-side {
      display: flex; flex-direction: column; gap: 8px;
    }
    .med-vital-compact {
      flex: 1;
      display: flex; align-items: center; gap: 12px;
      padding: 12px 14px;
      border-radius: 14px;
      min-height: 0;
      box-shadow: none !important;
      transition: border-color 0.25s ease;
    }
    .med-vital-compact.temp {
      background: #fff7ed;
      border: 1.5px solid #fed7aa;
    }
    .med-vital-compact.room {
      background: #f0fdf4;
      border: 1.5px solid #bbf7d0;
    }
    .med-vital-compact.hum {
      background: #ecfeff;
      border: 1.5px solid #a5f3fc;
    }
    .med-compact-icon {
      width: 38px; height: 38px; flex-shrink: 0;
      border-radius: 11px;
      display: grid; place-items: center;
      box-shadow: none;
    }
    .med-vital-compact.temp .med-compact-icon { background: #ea580c; color: #fff; }
    .med-vital-compact.room .med-compact-icon { background: #16a34a; color: #fff; }
    .med-vital-compact.hum .med-compact-icon { background: #0891b2; color: #fff; }
    .med-compact-icon svg {
      width: 20px; height: 20px;
      stroke: currentColor; fill: none;
      stroke-width: 2; stroke-linecap: round; stroke-linejoin: round;
    }
    .med-compact-body { flex: 1; min-width: 0; }
    .med-compact-body .med-vital-title { margin-bottom: 3px; font-size: 0.65rem; }
    .med-compact-value {
      font-size: 1.3rem; font-weight: 800;
      letter-spacing: -0.03em; line-height: 1.1;
      font-variant-numeric: tabular-nums;
    }
    .med-compact-value.vital-flash { animation: vitalSoft 0.45s ease; }
    @keyframes vitalSoft {
      0%, 100% { opacity: 1; }
      50% { opacity: 0.75; }
    }
    .med-vital-compact.temp .med-compact-value { color: #c2410c; }
    .med-vital-compact.room .med-compact-value { color: #15803d; }
    .med-vital-compact.hum .med-compact-value { color: #0e7490; }
    .med-compact-body .med-unit { font-size: 0.65rem; }
    .med-compact-body .med-bar { height: 4px; margin-top: 6px; }
    .med-vital-compact.temp .bar-fill { background: #f97316; }
    .med-vital-compact.room .bar-fill { background: #22c55e; }
    .med-vital-compact.hum .bar-fill { background: #06b6d4; }
    .med-vital .badge, .med-vital-compact .badge {
      position: static;
      font-size: 0.55rem;
      font-weight: 800;
      padding: 3px 8px;
      letter-spacing: 0.04em;
      border-radius: 6px;
    }
    .med-ecg {
      flex: 1 1 auto; min-height: 0;
      padding: 12px 14px 14px;
      background: #f0fdf4;
      border: 1.5px solid #bbf7d0;
      box-shadow: none !important;
    }
    .ecg-icon-wrap {
      width: 36px; height: 36px; border-radius: 10px;
      background: #16a34a;
      display: grid; place-items: center;
      color: #fff;
      box-shadow: none;
    }
    .ecg-icon-wrap svg {
      width: 18px; height: 18px;
      stroke: currentColor; fill: none;
      stroke-width: 2.2; stroke-linecap: round; stroke-linejoin: round;
    }
    .ecg-title-block {
      display: flex; align-items: center; gap: 10px;
    }
    .ecg-title-block h3 {
      font-size: 0.92rem; letter-spacing: -0.02em;
      margin: 0;
    }
    .ecg-sub {
      font-size: 0.68rem; color: var(--muted); font-weight: 600;
    }
    .ecg-overlay-labels {
      position: absolute; top: 8px; left: 10px; z-index: 2;
      display: flex; gap: 12px;
      font-size: 0.62rem; font-weight: 800;
      color: rgba(103,232,249,0.55);
      letter-spacing: 0.06em;
      text-transform: uppercase;
      pointer-events: none;
    }
    .glass {
      background: var(--card);
      border: 1px solid rgba(226,232,240,0.9);
      border-radius: var(--radius);
      box-shadow: 0 8px 24px rgba(15,23,42,0.06);
    }
    .vitals-row {
      display: grid;
      grid-template-columns: repeat(5, 1fr);
      gap: 10px;
      margin-bottom: 10px;
    }
    .vital-card { padding: 12px 14px; position: relative; overflow: hidden; }
    .vital-card .label {
      font-size: 0.68rem; font-weight: 900; color: var(--muted);
      text-transform: uppercase; letter-spacing: 0.06em;
      margin-bottom: 6px;
    }
    .vital-card .value {
      font-size: 1.85rem; font-weight: 1000;
      letter-spacing: -0.06em; line-height: 1;
      margin-bottom: 8px;
    }
    .vital-card .unit { font-size: 0.8rem; color: var(--muted); font-weight: 800; }
    .vital-card .bar {
      height: 6px; border-radius: 999px; background: #e8eef7; overflow: hidden;
    }
    .vital-card .bar-fill {
      height: 100%; border-radius: inherit;
      background: linear-gradient(90deg, var(--blue), var(--cyan));
      transition: width 0.4s ease;
    }
    .badge {
      position: absolute; top: 10px; right: 10px;
      font-size: 0.62rem; font-weight: 900; padding: 4px 8px;
      border-radius: 999px; letter-spacing: 0.05em;
    }
    .badge.good { background: var(--green-soft); color: var(--green); }
    .badge.watch { background: var(--orange-soft); color: #b45309; }
    .badge.live { background: var(--blue-soft); color: var(--blue); }
    .badge.bad { background: var(--red-soft); color: var(--red); }
    #page-dashboard .ecg-wrap {
      flex: 1 1 auto;
      min-height: 0;
      display: flex;
      flex-direction: column;
    }
    .ecg-wrap {
      flex: 1;
      min-height: 0;
      display: flex;
      flex-direction: column;
    }
    #page-dashboard .ecg-head {
      margin-bottom: 8px;
      flex-shrink: 0;
    }
    #page-dashboard .ecg-stage {
      flex: 1 1 auto;
      min-height: 0;
    }
    .ecg-head {
      display: flex; justify-content: space-between; align-items: center;
      margin-bottom: 8px; gap: 10px;
      position: relative;
    }
    .ecg-head .ecg-badge-pill {
      position: static;
      flex-shrink: 0;
      font-size: 0.62rem; font-weight: 900;
      padding: 5px 12px; border-radius: 999px;
      letter-spacing: 0.06em; text-transform: uppercase;
      background: var(--blue-soft); color: var(--blue);
    }
    .ecg-head .ecg-badge-pill.good { background: var(--green-soft); color: var(--green); }
    .ecg-head .ecg-badge-pill.watch { background: var(--orange-soft); color: #b45309; }
    .ecg-head .ecg-badge-pill.bad { background: var(--red-soft); color: var(--red); }
    .ecg-head .ecg-badge-pill.live { background: #dbeafe; color: #2563eb; }
    .ecg-head h3 { font-size: 0.92rem; letter-spacing: -0.02em; }
    .ecg-head span { font-size: 0.72rem; color: var(--muted); }
    .ecg-stage {
      flex: 1;
      min-height: 0;
      border-radius: 14px;
      overflow: hidden;
      position: relative;
      background:
        linear-gradient(rgba(103,232,249,0.06) 1px, transparent 1px),
        linear-gradient(90deg, rgba(103,232,249,0.06) 1px, transparent 1px),
        linear-gradient(180deg, #06101d, #0f172a 62%, #08111f);
      background-size: 24px 24px;
      border: 1px solid rgba(15,23,42,0.1);
    }
    .ecg-stage canvas {
      position: absolute;
      inset: 0;
      width: 100%;
      height: 100%;
      display: block;
    }
    .info-grid {
      display: grid; grid-template-columns: 1fr 1fr;
      gap: 12px;
    }
    .info-card { padding: 16px; }
    .info-card h3 {
      font-size: 0.95rem; margin-bottom: 12px;
      padding-bottom: 8px; border-bottom: 1px solid #e2e8f0;
    }
    .info-row {
      display: flex; justify-content: space-between; gap: 10px;
      padding: 8px 0; border-bottom: 1px solid #f1f5f9;
      font-size: 0.82rem;
    }
    .info-row span:first-child { color: var(--muted); font-weight: 700; }
    .info-row span:last-child { font-weight: 800; text-align: right; }
    .alert-card {
      padding: 14px; margin-bottom: 10px;
      display: grid; grid-template-columns: 36px 1fr; gap: 12px;
      align-items: start;
    }
    .alert-icon {
      width: 36px; height: 36px; border-radius: 12px;
      background: #fff; display: grid; place-items: center;
      border: 1px solid #e2e8f0; font-size: 16px;
    }
    .alert-card strong { display: block; font-size: 0.88rem; margin-bottom: 4px; }
    .alert-card p { font-size: 0.78rem; color: var(--muted); line-height: 1.4; }
    .form-grid {
      display: grid; grid-template-columns: 1fr 1fr; gap: 9px;
    }
    .form-field {
      display: flex; flex-direction: column; gap: 4px;
    }
    .form-field.full { grid-column: span 2; }
    .form-field label {
      display: flex; align-items: center; gap: 6px;
      font-size: 0.68rem; color: var(--muted); font-weight: 800;
      text-transform: uppercase; letter-spacing: 0.06em;
    }
    .field-icon {
      width: 22px; height: 22px; border-radius: 7px;
      display: grid; place-items: center;
      font-size: 12px; line-height: 1; flex-shrink: 0;
    }
    .field-icon.ic-name { background: #dbeafe; color: #2563eb; }
    .field-icon.ic-id { background: #ede9fe; color: #7c3aed; }
    .field-icon.ic-bed { background: #ccfbf1; color: #0d9488; }
    .field-icon.ic-ward { background: #ffedd5; color: #ea580c; }
    .field-icon.ic-age { background: #cffafe; color: #0891b2; }
    .field-icon.ic-blood { background: #fee2e2; color: #dc2626; }
    .field-icon.ic-gender { background: #fce7f3; color: #db2777; }
    .field-icon.ic-contact { background: #dcfce7; color: #16a34a; }
    .field-icon.ic-notes { background: #fef3c7; color: #d97706; }
    .info-label {
      display: flex; align-items: center; gap: 8px;
      color: var(--muted); font-weight: 700;
    }
    .info-label .field-icon { width: 20px; height: 20px; font-size: 11px; border-radius: 6px; }
    #page-patient .info-card h3 {
      display: flex; align-items: center; gap: 8px;
    }
    #page-patient .info-card h3 .field-icon { width: 24px; height: 24px; font-size: 13px; }
    .form-field input, .form-field select, .form-field textarea {
      padding: 9px 11px; border-radius: 10px;
      border: 1px solid #e2e8f0; background: #fff;
      font-size: 0.88rem; font-weight: 600; color: var(--text);
      font-family: inherit;
    }
    .form-field textarea { min-height: 72px; resize: vertical; }
    .form-field input:focus, .form-field select:focus, .form-field textarea:focus {
      outline: none; border-color: var(--blue);
      box-shadow: 0 0 0 3px rgba(37,99,235,0.12);
    }
    .form-actions {
      display: flex; gap: 8px; margin-top: 14px; flex-wrap: wrap;
    }
    .btn {
      padding: 10px 16px; border-radius: 10px; border: none;
      font-size: 0.82rem; font-weight: 800; cursor: pointer;
    }
    .btn-primary { background: var(--blue); color: #fff; }
    .btn-secondary { background: #e2e8f0; color: var(--text); }
    .btn-danger { background: var(--red-soft); color: var(--red); }
    .save-msg {
      font-size: 0.78rem; color: var(--green); font-weight: 800;
      margin-top: 8px; min-height: 1em;
    }
    .patient-head {
      display: flex; justify-content: space-between; align-items: center;
      margin-bottom: 12px;
    }
    .nav-text-short { display: none; }
    .patient-head h3 { font-size: 0.95rem; border: none; padding: 0; margin: 0; }
 
    /* Astronaut health pages */
    #page-bone.page.active, #page-mind.page.active, #page-report.page.active {
      display: flex; flex-direction: column; gap: 10px;
      padding: 10px 14px 14px;
      background: linear-gradient(180deg, #f0f4fa 0%, #e8eef6 100%);
    }
    .kpi-grid { display: grid; grid-template-columns: repeat(4, 1fr); gap: 8px; flex-shrink: 0; }
    .kpi { padding: 12px 8px; border-radius: 14px; text-align: center; }
    .kpi b { display: block; font-size: 1.3rem; font-weight: 900; letter-spacing: -0.03em; margin-bottom: 2px; }
    .kpi small { font-size: 0.6rem; font-weight: 800; text-transform: uppercase; letter-spacing: 0.05em; color: var(--muted); }
    .two-col { display: grid; grid-template-columns: 1fr 1fr; gap: 10px; }
    .card-pad { padding: 14px 16px; border-radius: 14px; }
    .card-pad h4 { font-size: 0.72rem; font-weight: 900; text-transform: uppercase; letter-spacing: 0.08em; color: var(--muted); margin-bottom: 10px; }
    .meter { height: 10px; border-radius: 999px; background: #e2e8f0; overflow: hidden; margin: 6px 0; }
    .meter > i { display: block; height: 100%; width: 0; background: #3b82f6; transition: width 0.5s; }
    .row-between { display: flex; justify-content: space-between; align-items: center; gap: 8px; font-size: 0.8rem; font-weight: 700; padding: 5px 0; }
    .row-between span:first-child { color: var(--muted); }
    .note-small { font-size: 0.72rem; color: var(--muted); font-weight: 600; line-height: 1.45; margin-top: 6px; }
    .bars7 { display: flex; align-items: flex-end; gap: 6px; height: 96px; }
    .bars7 .col { flex: 1; display: flex; flex-direction: column; justify-content: flex-end; align-items: center; height: 100%; gap: 3px; }
    .bars7 .col i { display: block; width: 100%; background: #3b82f6; border-radius: 6px 6px 0 0; min-height: 3px; }
    .bars7 .col span { font-size: 0.58rem; font-weight: 800; color: var(--muted); }
    .q-row { display: flex; justify-content: space-between; align-items: center; gap: 8px; padding: 6px 0; border-bottom: 1px solid #f1f5f9; font-size: 0.8rem; font-weight: 700; }
    .q-row select { padding: 6px 8px; border-radius: 8px; border: 1px solid #e2e8f0; font-family: inherit; font-weight: 700; }
    .chat-box { max-height: 220px; overflow-y: auto; display: flex; flex-direction: column; gap: 6px; margin-bottom: 8px; }
    .chat-msg { padding: 8px 11px; border-radius: 12px; font-size: 0.8rem; font-weight: 600; line-height: 1.4; max-width: 92%; }
    .chat-msg.ai { background: #eff6ff; border: 1px solid #bfdbfe; align-self: flex-start; }
    .chat-msg.me { background: #dcfce7; border: 1px solid #86efac; align-self: flex-end; }
    .reply-row { display: flex; flex-wrap: wrap; gap: 6px; }
    .reply-row .btn { padding: 7px 11px; font-size: 0.74rem; }
    .report-text { white-space: pre-wrap; font-family: ui-monospace, Menlo, Consolas, monospace; font-size: 0.78rem; line-height: 1.5; background: #fff; border: 1px solid #e2e8f0; border-radius: 12px; padding: 14px; max-height: 52vh; overflow: auto; }
    .queue-item { display: flex; gap: 8px; align-items: flex-start; padding: 8px 10px; border-radius: 10px; background: #fff; border: 1px solid #e2e8f0; margin-bottom: 6px; font-size: 0.76rem; font-weight: 600; }
    .queue-item .alert-pill { margin-top: 1px; }

    /* Tablet */
    @media (max-width: 1024px) {
      .med-vitals-grid { grid-template-columns: 1fr 1fr; }
      .med-vitals-side { grid-column: span 2; flex-direction: row; }
      .med-vital-compact { flex: 1; min-width: 0; }
    }
 
    /* Mobile */
    @media (max-width: 768px) {
      body {
        align-items: stretch;
        justify-content: stretch;
      }
      .viewport-wrap {
        width: 100vw;
        width: 100dvw;
        height: 100vh;
        height: 100dvh;
        max-width: none;
        max-height: none;
        aspect-ratio: auto;
      }
      .app-shell {
        flex-direction: column;
      }
      .main {
        flex: 1;
        min-height: 0;
        order: 1;
      }
      .sidebar {
        order: 2;
        width: 100%;
        flex-shrink: 0;
        flex-direction: column;
        padding: 0;
        border-right: none;
        border-top: 1px solid rgba(255,255,255,0.1);
      }
      .sidebar-brand,
      .nav-label { display: none; }
      .sidebar-foot {
        display: flex;
        align-items: center;
        justify-content: space-between;
        padding: 6px 14px;
        border-top: none;
        border-bottom: 1px solid rgba(255,255,255,0.08);
        margin: 0;
      }
      .nav {
        flex-direction: row;
        flex: none;
        gap: 2px;
        padding: 4px 6px;
        padding-bottom: max(6px, env(safe-area-inset-bottom));
      }
      .nav-item {
        flex: 1;
        flex-direction: column;
        align-items: center;
        justify-content: center;
        gap: 3px;
        padding: 8px 2px;
        min-height: 54px;
        font-size: 0.58rem;
        text-align: center;
        transform: none;
        border-radius: 10px;
      }
      .nav-item:hover { transform: none; }
      .nav-text-long { display: none; }
      .nav-text-short { display: inline; }
      .nav-icon-wrap {
        width: 32px;
        height: 32px;
        font-size: 15px;
      }
      .topbar {
        padding: 8px 12px;
        gap: 8px;
      }
      .topbar h1 { font-size: 1rem; }
      .topbar p { font-size: 0.7rem; display: none; }
      .topbar-meta { font-size: 0.68rem; }
      .topbar-meta strong { font-size: 0.78rem; }
      .page {
        padding: 10px 10px 12px;
      }
      .page.active {
        overflow-y: auto;
        overflow-x: hidden;
        -webkit-overflow-scrolling: touch;
      }
      #page-dashboard.page.active,
      #page-patient.page.active,
      #page-logging.page.active,
      #page-alerts.page.active {
        overflow-y: auto;
        padding: 8px 10px 10px;
      }
      .med-dash {
        gap: 8px;
        min-height: min-content;
      }
      .med-status-bar {
        flex-wrap: wrap;
        gap: 6px;
        padding: 8px 10px;
      }
      .med-status-patient {
        flex: 1 1 100%;
        max-width: 100%;
        width: 100%;
        justify-content: flex-start;
      }
      .ward-pill-dash { display: none; }
      .topbar-actions { gap: 8px; }
      .sound-toggle { width: 32px; height: 32px; font-size: 14px; }
      .med-vitals-grid {
        grid-template-columns: 1fr;
        gap: 8px;
      }
      .med-vitals-side {
        grid-column: auto;
        flex-direction: column;
        gap: 8px;
      }
      .med-vital {
        min-height: auto;
        padding: 12px 14px;
      }
      .med-vital-value { font-size: 2rem; }
      .med-vital-compact { min-height: auto; }
      #page-dashboard .ecg-wrap {
        flex: none;
        min-height: 0;
      }
      #page-dashboard .ecg-stage {
        flex: none;
        min-height: 200px;
        height: 42vw;
        max-height: 280px;
      }
      .record-stats-row { grid-template-columns: 1fr; }
      .record-stat {
        flex-direction: row;
        align-items: center;
        justify-content: flex-start;
        text-align: left;
        padding: 12px 14px;
        gap: 12px;
      }
      .record-stat-label { flex: 1; margin: 0; }
      .record-stat-value { font-size: 1rem; flex-shrink: 0; }
      .record-contact-row { grid-template-columns: 1fr; }
      .record-profile {
        flex-wrap: wrap;
        padding: 14px;
        gap: 12px;
      }
      .record-profile-main { width: calc(100% - 82px); }
      .record-profile-main h2 { font-size: 1.25rem; }
      .record-profile .btn-glow {
        width: 100%;
        margin-top: 2px;
      }
      .record-page { overflow: hidden; }
      #page-patient.page.active { overflow: hidden; }
      #page-alerts.page.active { overflow: hidden; }
      .alerts-summary { grid-template-columns: repeat(3, 1fr); gap: 6px; }
      .alerts-summary-card { padding: 8px 6px; font-size: 0.58rem; }
      .alerts-summary-card span { font-size: 1.15rem; }
      .alerts-hero { flex-wrap: wrap; padding: 12px 14px; }
      .alerts-hero h3 { font-size: 0.95rem; }
      .alert-row { padding: 11px 12px; gap: 10px; }
      .alert-row-icon { width: 38px; height: 38px; font-size: 17px; }
      .alert-row-top strong { font-size: 0.82rem; }
      .alert-tip { font-size: 0.68rem; padding: 6px 8px; }
      .logging-toolbar {
        flex-direction: column;
        align-items: stretch;
        gap: 10px;
      }
      .logging-controls {
        flex-direction: column;
        align-items: stretch;
      }
      .logging-controls select,
      .logging-controls .btn-log {
        width: 100%;
      }
      .logging-stats {
        justify-content: space-between;
        width: 100%;
      }
      .logging-table-scroll {
        overflow-x: auto;
        overflow-y: auto;
      }
      .log-table { min-width: 520px; font-size: 0.72rem; }
      .log-table th, .log-table td { padding: 8px 8px; }
      .form-grid { grid-template-columns: 1fr; }
      .form-field.full { grid-column: span 1; }
      .kpi-grid { grid-template-columns: 1fr 1fr; }
      .two-col { grid-template-columns: 1fr; }
      #page-bone.page.active, #page-mind.page.active, #page-report.page.active { overflow-y: auto; }
      .patient-modal { padding: 10px; align-items: flex-end; }
      .patient-modal-card {
        max-height: 92dvh;
        border-radius: 18px 18px 0 0;
        width: 100%;
      }
      .info-grid { grid-template-columns: 1fr; }
      .vitals-row { grid-template-columns: 1fr; }
    }
 
    /* Small phones */
    @media (max-width: 400px) {
      .med-vital-icon-wrap { width: 52px; }
      .vital-icon-box { width: 46px; height: 46px; }
      .vital-icon-heart svg { width: 22px; height: 22px; }
      .med-vital-value { font-size: 1.75rem; }
      .med-compact-value { font-size: 1.15rem; }
      .nav-item { font-size: 0.52rem; min-height: 50px; }
      .ecg-overlay-labels { font-size: 0.55rem; gap: 8px; }
      #page-dashboard .ecg-stage {
        min-height: 160px;
        height: 38vw;
      }
    }
  </style>
</head>
<body>
  <div class="viewport-wrap">
    <div class="app-shell">
      <aside class="sidebar">
        <div class="sidebar-brand">
          <div class="sidebar-logo">
            <svg viewBox="0 0 24 24" aria-hidden="true">
              <path d="M4 12h2l2-4 3 8 2-5 2 5 3-8 2 4h2"/>
            </svg>
          </div>
          <div>
            <strong>MedMonitor</strong>
            <span>Patient Care IoT</span>
          </div>
        </div>
        <div class="nav-label">Clinical</div>
        <nav class="nav">
          <button class="nav-item active" data-page="dashboard"><span class="nav-icon-wrap"><span class="nav-icon">&#128147;</span></span><span class="nav-text"><span class="nav-text-long">Vitals Monitor</span><span class="nav-text-short">Vitals</span></span></button>
          <button class="nav-item" data-page="patient"><span class="nav-icon-wrap"><span class="nav-icon">&#128100;</span></span><span class="nav-text"><span class="nav-text-long">Astronaut Record</span><span class="nav-text-short">Crew</span></span></button>
          <button class="nav-item" data-page="logging"><span class="nav-icon-wrap"><span class="nav-icon">&#128202;</span></span><span class="nav-text"><span class="nav-text-long">Data Logging</span><span class="nav-text-short">Logging</span></span></button>
          <button class="nav-item" data-page="alerts"><span class="nav-icon-wrap"><span class="nav-icon">&#128680;</span></span><span class="nav-text"><span class="nav-text-long">Alerts</span><span class="nav-text-short">Alerts</span></span></button>
          <button class="nav-item" data-page="bone"><span class="nav-icon-wrap"><span class="nav-icon">&#129460;</span></span><span class="nav-text"><span class="nav-text-long">Bone &amp; Muscle</span><span class="nav-text-short">Bone</span></span></button>
          <button class="nav-item" data-page="mind"><span class="nav-icon-wrap"><span class="nav-icon">&#129504;</span></span><span class="nav-text"><span class="nav-text-long">Mental Health</span><span class="nav-text-short">Mind</span></span></button>
          <button class="nav-item" data-page="report"><span class="nav-icon-wrap"><span class="nav-icon">&#128196;</span></span><span class="nav-text"><span class="nav-text-long">Daily Report</span><span class="nav-text-short">Report</span></span></button>
        </nav>
        <div class="sidebar-foot">
          <div class="live-pill"><span class="live-dot" id="liveDot"></span><span id="connText">Connecting</span></div>
          <span id="clock">--:--:--</span>
        </div>
      </aside>
 
      <div class="main">
        <header class="topbar">
          <div>
            <h1 id="pageTitle">Dashboard</h1>
            <p id="pageSubtitle">Live vitals and ECG waveform</p>
          </div>
          <div class="topbar-actions">
            <button type="button" class="sound-toggle" id="btnSoundToggle" title="Toggle heartbeat sound" aria-label="Toggle heartbeat sound">
              <svg class="sound-on" viewBox="0 0 24 24" aria-hidden="true"><path d="M11 5L6 9H2v6h4l5 4V5z"/><path d="M15.54 8.46a5 5 0 0 1 0 7.07"/><path d="M19.07 4.93a10 10 0 0 1 0 14.14"/></svg>
              <svg class="sound-off" viewBox="0 0 24 24" aria-hidden="true"><path d="M11 5L6 9H2v6h4l5 4V5z"/><line x1="23" y1="9" x2="17" y2="15"/><line x1="17" y1="9" x2="23" y2="15"/></svg>
            </button>
            <div class="topbar-meta">
              <span>Last update</span>
              <strong id="lastUpdate">--</strong>
            </div>
          </div>
        </header>
 
        <div class="page-area">
          <!-- DASHBOARD -->
          <section class="page active" id="page-dashboard">
            <div class="med-dash">
              <div class="med-status-bar">
                <div class="med-status-pill live-pill-dash">
                  <span class="med-status-dot"></span>
                  <span>Live</span>
                </div>
                <div class="med-status-pill ward-pill-dash">
                  <svg viewBox="0 0 24 24" aria-hidden="true"><path d="M3 21h18M5 21V7l7-4 7 4v14M9 21v-6h6v6"/></svg>
                  <span>ISS Crew Monitor</span>
                </div>
                <div class="med-status-patient">
                  <span class="med-chip-icon">
                    <svg viewBox="0 0 24 24" aria-hidden="true"><path d="M20 21v-2a4 4 0 0 0-4-4H8a4 4 0 0 0-4 4v2"/><circle cx="12" cy="7" r="4"/></svg>
                  </span>
                  <span id="dashPatientName">Astronaut Monitor</span>
                </div>
              </div>
 
              <div class="dash-section-label">Live Vitals</div>
 
              <div class="med-vitals-grid">
                <div class="med-vital med-vital-heart glass">
                  <div class="med-vital-icon-wrap">
                    <div class="vital-icon-box vital-icon-heart" id="heartIcon">
                      <svg viewBox="0 0 24 24" aria-hidden="true">
                        <path d="M12 21.35l-1.45-1.32C5.4 15.36 2 12.28 2 8.5 2 5.42 4.42 3 7.5 3c1.74 0 3.41.81 4.5 2.09C13.09 3.81 14.76 3 16.5 3 19.58 3 22 5.42 22 8.5c0 3.78-3.4 6.86-8.55 11.54L12 21.35z"/>
                      </svg>
                    </div>
                  </div>
                  <div class="med-vital-body">
                    <div class="med-vital-top">
                      <span class="med-vital-title"><span class="vt-ico"><svg viewBox="0 0 24 24"><path d="M12 21.35l-1.45-1.32C5.4 15.36 2 12.28 2 8.5 2 5.42 4.42 3 7.5 3c1.74 0 3.41.81 4.5 2.09C13.09 3.81 14.76 3 16.5 3 19.58 3 22 5.42 22 8.5c0 3.78-3.4 6.86-8.55 11.54L12 21.35z" fill="currentColor" stroke="none"/></svg></span>Heart Rate</span>
                      <span class="badge watch" id="bpmBadge">WAIT</span>
                    </div>
                    <div class="med-vital-value" id="bpmWrap"><span id="bpm">--</span><span class="med-unit">BPM</span></div>
                    <div class="med-range">Normal range: 60 – 100 BPM</div>
                    <div class="bar med-bar"><div class="bar-fill" id="bpmBar" style="width:6%"></div></div>
                  </div>
                </div>
 
                <div class="med-vital med-vital-spo2 glass">
                  <div class="med-vital-icon-wrap">
                    <div class="vital-icon-box vital-icon-spo2">
                      <span class="spo2-symbol">O&#8322;</span>
                    </div>
                  </div>
                  <div class="med-vital-body">
                    <div class="med-vital-top">
                      <span class="med-vital-title"><span class="vt-ico"><svg viewBox="0 0 24 24"><circle cx="12" cy="12" r="9"/><path d="M8 12h8M10 9v6M14 9v6"/></svg></span>Blood Oxygen</span>
                      <span class="badge watch" id="spo2Badge">WAIT</span>
                    </div>
                    <div class="med-vital-value" id="spo2Wrap"><span id="spo2">--</span><span class="med-unit">% SpO&#8322;</span></div>
                    <div class="med-range">Normal range: 95 – 100%</div>
                    <div class="bar med-bar"><div class="bar-fill" id="spo2Bar" style="width:6%"></div></div>
                  </div>
                </div>
 
                <div class="med-vitals-side">
                  <div class="med-vital-compact glass temp">
                    <div class="med-compact-icon">
                      <svg viewBox="0 0 24 24" aria-hidden="true"><path d="M14 14.76V3.5a2.5 2.5 0 0 0-5 0v11.26a4.5 4.5 0 1 0 5 0z"/></svg>
                    </div>
                    <div class="med-compact-body">
                      <div class="med-vital-top">
                        <span class="med-vital-title"><span class="vt-ico" style="background:#ffedd5;color:#ea580c"><svg viewBox="0 0 24 24"><path d="M14 14.76V3.5a2.5 2.5 0 0 0-5 0v11.26a4.5 4.5 0 1 0 5 0z" fill="currentColor" stroke="none"/></svg></span>Body Temp</span>
                        <span class="badge watch" id="tempBadge">WAIT</span>
                      </div>
                      <div class="med-compact-value" id="bodyTempWrap"><span id="bodyTemp">--</span><span class="med-unit">&deg;C</span></div>
                      <div class="bar med-bar"><div class="bar-fill" id="bodyTempBar" style="width:6%"></div></div>
                    </div>
                  </div>
                  <div class="med-vital-compact glass room">
                    <div class="med-compact-icon">
                      <svg viewBox="0 0 24 24" aria-hidden="true"><path d="M3 10.5L12 3l9 7.5V20a1 1 0 0 1-1 1h-5v-6H9v6H4a1 1 0 0 1-1-1v-9.5z"/></svg>
                    </div>
                    <div class="med-compact-body">
                      <div class="med-vital-top">
                        <span class="med-vital-title"><span class="vt-ico" style="background:#dcfce7;color:#16a34a"><svg viewBox="0 0 24 24"><path d="M3 10.5L12 3l9 7.5V20a1 1 0 0 1-1 1h-5v-6H9v6H4a1 1 0 0 1-1-1z" fill="currentColor" stroke="none"/></svg></span>Room Temp</span>
                        <span class="badge watch" id="roomBadge">WAIT</span>
                      </div>
                      <div class="med-compact-value" id="roomTempWrap"><span id="roomTemp">--</span><span class="med-unit">&deg;C</span></div>
                      <div class="bar med-bar"><div class="bar-fill" id="roomTempBar" style="width:6%"></div></div>
                    </div>
                  </div>
                  <div class="med-vital-compact glass hum">
                    <div class="med-compact-icon">
                      <svg viewBox="0 0 24 24" aria-hidden="true"><path d="M12 2.69l5.66 5.66a8 8 0 1 1-11.31 0z"/></svg>
                    </div>
                    <div class="med-compact-body">
                      <div class="med-vital-top">
                        <span class="med-vital-title"><span class="vt-ico" style="background:#cffafe;color:#0891b2"><svg viewBox="0 0 24 24"><path d="M12 2.69l5.66 5.66a8 8 0 1 1-11.31 0z" fill="currentColor" stroke="none"/></svg></span>Humidity</span>
                        <span class="badge watch" id="humBadge">WAIT</span>
                      </div>
                      <div class="med-compact-value" id="humidityWrap"><span id="humidity">--</span><span class="med-unit">% RH</span></div>
                      <div class="bar med-bar"><div class="bar-fill" id="humBar" style="width:6%"></div></div>
                    </div>
                  </div>
                </div>
              </div>
 
              <div class="dash-section-label" style="margin-top:2px">ECG Waveform</div>
 
              <div class="ecg-wrap glass med-ecg">
                <div class="ecg-head">
                  <div class="ecg-title-block">
                    <div class="ecg-icon-wrap">
                      <svg viewBox="0 0 24 24" aria-hidden="true"><path d="M4 12h2l2-4 3 8 2-5 2 5 3-8 2 4h2"/></svg>
                    </div>
                    <div>
                      <h3>Electrocardiogram · Lead I</h3>
                    </div>
                  </div>
                  <span class="ecg-badge-pill live" id="ecgBadge">STREAMING</span>
                </div>
                <div class="ecg-stage">
                  <div class="ecg-overlay-labels">
                    <span>1 mV/div</span>
                    <span>25 mm/s</span>
                  </div>
                  <canvas id="ecgCanvas"></canvas>
                </div>
              </div>
            </div>
          </section>
 
          <!-- PATIENT RECORD -->
          <section class="page" id="page-patient">
            <div class="record-page">
              <div class="record-banner glass">
                <div class="record-banner-bg"></div>
                <div class="record-profile">
                  <div class="record-avatar-ring">
                    <div class="patient-avatar" id="viewAvatar">?</div>
                  </div>
                  <div class="record-profile-main">
                    <h2 id="viewName">No patient saved</h2>
                    <div class="patient-chips">
                      <span class="patient-chip" id="viewId">No ID</span>
                      <span class="patient-chip loc">Bed <span id="viewBed">--</span> &middot; Ward <span id="viewWard">--</span></span>
                    </div>
                  </div>
                  <button type="button" class="btn btn-primary btn-glow" id="btnEditPatient">&#9998; Edit</button>
                </div>
              </div>
 
              <div class="record-scroll">
                <div>
                  <h4 class="record-section-title">Personal Information</h4>
                  <div class="record-stats-row">
                    <div class="record-stat glass rc-age">
                      <span class="record-stat-icon">&#127874;</span>
                      <span class="record-stat-label">Age</span>
                      <span class="record-stat-value" id="viewAge">--</span>
                    </div>
                    <div class="record-stat glass rc-gender">
                      <span class="record-stat-icon">&#9895;</span>
                      <span class="record-stat-label">Gender</span>
                      <span class="record-stat-value" id="viewGender">--</span>
                    </div>
                    <div class="record-stat glass rc-blood">
                      <span class="record-stat-icon">&#128167;</span>
                      <span class="record-stat-label">Blood</span>
                      <span class="record-stat-value" id="viewBlood">--</span>
                    </div>
                  </div>
                </div>
 
                <div>
                  <h4 class="record-section-title">Contact &amp; ID</h4>
                  <div class="record-contact-row">
                    <div class="record-detail-card glass rc-phone">
                      <span class="field-icon ic-contact">&#128222;</span>
                      <div>
                        <div class="record-detail-label">Phone</div>
                        <div class="record-detail-value" id="viewContact">--</div>
                      </div>
                    </div>
                    <div class="record-detail-card glass rc-id">
                      <span class="field-icon ic-id">&#127380;</span>
                      <div>
                        <div class="record-detail-label">Patient ID</div>
                        <div class="record-detail-value" id="viewIdDetail">--</div>
                      </div>
                    </div>
                  </div>
                </div>
 
                <div class="record-notes-card glass">
                  <h4 class="record-section-title">&#128221; Clinical Notes</h4>
                  <div class="record-notes-body" id="viewNotes">No notes added.</div>
                </div>
              </div>
            </div>
          </section>
 
          <div class="patient-modal" id="patientModal">
            <div class="patient-modal-backdrop" id="patientModalBackdrop"></div>
            <div class="patient-modal-card glass">
              <div class="patient-modal-head">
                <h3><span class="field-icon ic-name">&#128100;</span>Edit Patient Details</h3>
                <button type="button" class="btn-icon" id="btnClosePatientModal" title="Close">&times;</button>
              </div>
              <form id="patientForm" class="form-grid">
                <div class="form-field">
                  <label for="inpName"><span class="field-icon ic-name">&#128100;</span>Full Name</label>
                  <input type="text" id="inpName" name="name" placeholder="Enter patient name" />
                </div>
                <div class="form-field">
                  <label for="inpId"><span class="field-icon ic-id">&#127380;</span>Patient ID</label>
                  <input type="text" id="inpId" name="patientId" placeholder="e.g. PT-2048" />
                </div>
                <div class="form-field">
                  <label for="inpBed"><span class="field-icon ic-bed">&#128719;</span>Bed</label>
                  <input type="text" id="inpBed" name="bed" placeholder="e.g. 03" />
                </div>
                <div class="form-field">
                  <label for="inpWard"><span class="field-icon ic-ward">&#127973;</span>Ward</label>
                  <input type="text" id="inpWard" name="ward" placeholder="e.g. ICU" />
                </div>
                <div class="form-field">
                  <label for="inpAge"><span class="field-icon ic-age">&#127874;</span>Age</label>
                  <input type="number" id="inpAge" name="age" min="0" max="130" placeholder="Years" />
                </div>
                <div class="form-field">
                  <label for="inpBlood"><span class="field-icon ic-blood">&#128167;</span>Blood Group</label>
                  <select id="inpBlood" name="bloodGroup">
                    <option value="">Select</option>
                    <option value="A+">A+</option>
                    <option value="A-">A-</option>
                    <option value="B+">B+</option>
                    <option value="B-">B-</option>
                    <option value="AB+">AB+</option>
                    <option value="AB-">AB-</option>
                    <option value="O+">O+</option>
                    <option value="O-">O-</option>
                  </select>
                </div>
                <div class="form-field">
                  <label for="inpGender"><span class="field-icon ic-gender">&#9895;</span>Gender</label>
                  <select id="inpGender" name="gender">
                    <option value="">Select</option>
                    <option value="Male">Male</option>
                    <option value="Female">Female</option>
                    <option value="Other">Other</option>
                  </select>
                </div>
                <div class="form-field">
                  <label for="inpContact"><span class="field-icon ic-contact">&#128222;</span>Contact</label>
                  <input type="text" id="inpContact" name="contact" placeholder="Phone or email" />
                </div>
                <div class="form-field">
                  <label for="inpBmd">Baseline bone density (g/cm&sup2;)</label>
                  <input type="number" id="inpBmd" step="0.001" min="0" placeholder="e.g. 1.100" />
                </div>
                <div class="form-field">
                  <label for="inpMuscle">Baseline muscle mass (kg)</label>
                  <input type="number" id="inpMuscle" step="0.1" min="0" placeholder="e.g. 32.5" />
                </div>
                <div class="form-field">
                  <label for="inpMission">Mission start date</label>
                  <input type="date" id="inpMission" />
                </div>
                <div class="form-field">
                  <label for="inpExTarget">Daily exercise target (min)</label>
                  <input type="number" id="inpExTarget" min="10" max="400" placeholder="e.g. 150" />
                </div>
                <div class="form-field full">
                  <label for="inpNotes"><span class="field-icon ic-notes">&#128221;</span>Notes</label>
                  <textarea id="inpNotes" name="notes" placeholder="Medical notes, allergies, etc."></textarea>
                </div>
              </form>
              <div class="form-actions">
                <button type="button" class="btn btn-primary" id="btnSavePatient">Save Changes</button>
                <button type="button" class="btn btn-secondary" id="btnCancelPatient">Cancel</button>
                <button type="button" class="btn btn-danger" id="btnClearPatient">Clear All</button>
              </div>
              <div class="save-msg" id="saveMsg"></div>
            </div>
          </div>
 
          <!-- DATA LOGGING -->
          <section class="page" id="page-logging">
            <div class="logging-page">
              <div class="logging-toolbar glass">
                <div class="logging-controls">
                  <label for="logInterval">Interval</label>
                  <select id="logInterval">
                    <option value="2000">2 seconds</option>
                    <option value="3000">3 seconds</option>
                    <option value="5000" selected>5 seconds</option>
                    <option value="10000">10 seconds</option>
                    <option value="15000">15 seconds</option>
                    <option value="30000">30 seconds</option>
                    <option value="60000">60 seconds</option>
                  </select>
                  <button type="button" class="btn btn-log btn-log-start" id="btnLogStart">&#9654; Start</button>
                  <button type="button" class="btn btn-log btn-log-stop" id="btnLogStop">&#9632; Stop</button>
                  <button type="button" class="btn btn-log btn-secondary" id="btnLogClear">Clear</button>
                  <button type="button" class="btn btn-log btn-log-export" id="btnLogExport">&#128196; Export Excel</button>
                </div>
                <div class="logging-stats">
                  <span id="logCount">0 records</span>
                  <span class="log-status-pill stopped" id="logStatus">Stopped</span>
                </div>
              </div>
              <div class="logging-table-wrap glass">
                <div class="logging-table-head">
                  <h4>&#128202; Vitals Data Log</h4>
                  <span style="font-size:0.72rem;color:var(--muted);font-weight:700" id="logIntervalLabel">Every 5s</span>
                </div>
                <div class="logging-table-scroll">
                  <table class="log-table">
                    <thead>
                      <tr>
                        <th>#</th>
                        <th>Timestamp</th>
                        <th>BPM</th>
                        <th>SpO&#8322; (%)</th>
                        <th>Body Temp (&deg;C)</th>
                        <th>Room Temp (&deg;C)</th>
                        <th>Humidity (%)</th>
                      </tr>
                    </thead>
                    <tbody id="logTableBody">
                      <tr><td colspan="7" class="log-empty">No data logged yet. Press Start to begin recording.</td></tr>
                    </tbody>
                  </table>
                </div>
              </div>
            </div>
          </section>
 
          <!-- BONE & MUSCLE (Problem 1) -->
          <section class="page" id="page-bone">
            <div class="alerts-hero glass" style="background:linear-gradient(120deg,#1e3a8a,#2563eb 50%,#0891b2)">
              <div>
                <h3>&#129460; Bone &amp; Muscle Loss Monitor</h3>
                <p>Exercise adherence, vital signs during training, and estimated bone/muscle loss risk</p>
              </div>
              <span class="alerts-status-badge good" id="boneRiskBadge">NO BASELINE</span>
            </div>
            <div class="kpi-grid">
              <div class="kpi glass"><b id="kMissionDay">--</b><small>Mission day</small></div>
              <div class="kpi glass"><b id="kExToday">0</b><small>Effective min today</small></div>
              <div class="kpi glass"><b id="kAdh7">--</b><small>7-day adherence</small></div>
              <div class="kpi glass"><b id="kCheckup">--</b><small>Days since checkup</small></div>
            </div>
            <div class="two-col">
              <div class="card-pad glass">
                <h4>Exercise session</h4>
                <div class="row-between"><span>Status</span><span id="sesState">Idle</span></div>
                <div class="row-between"><span>Elapsed</span><span id="sesElapsed">00:00</span></div>
                <div class="row-between"><span>Heart rate now / max</span><span id="sesHr">-- / --</span></div>
                <div class="row-between"><span>Training zone (&ge;50% max HR)</span><span id="sesZone">--</span></div>
                <div class="row-between"><span>Lowest SpO&#8322;</span><span id="sesSpo2">--</span></div>
                <div class="meter"><i id="sesMeter"></i></div>
                <div class="note-small" id="sesTarget">Target: --</div>
                <div class="form-actions">
                  <button type="button" class="btn btn-log btn-log-start" id="btnSesStart">&#9654; Start session</button>
                  <button type="button" class="btn btn-log btn-log-stop" id="btnSesStop">&#9632; End session</button>
                </div>
                <div class="alert-tip" id="sesWarn" style="margin-top:8px" hidden></div>
              </div>
              <div class="card-pad glass">
                <h4>Estimated change since baseline</h4>
                <div class="row-between"><span>Bone density</span><span id="estBone">--</span></div>
                <div class="row-between"><span>Estimated bone loss</span><span id="estBoneLoss">--</span></div>
                <div class="row-between"><span>Muscle mass</span><span id="estMuscle">--</span></div>
                <div class="row-between"><span>Estimated muscle loss</span><span id="estMuscleLoss">--</span></div>
                <div class="note-small">Heuristic model (not a diagnosis): unmitigated loss of ~1.2%/month bone and ~1.5%/week muscle, reduced by exercise adherence. Real checkups override these numbers.</div>
                <div class="form-actions">
                  <button type="button" class="btn btn-log btn-log-export" id="btnCheckup">&#10003; Record checkup done</button>
                </div>
              </div>
            </div>
            <div class="card-pad glass">
              <h4>Last 7 days &mdash; exercise adherence</h4>
              <div class="bars7" id="bars7"></div>
            </div>
            <div class="card-pad glass">
              <h4>Recommendations</h4>
              <ul class="alert-suggest-list" id="boneRecs"><li>Enter baseline bone density, muscle mass, mission start and exercise target in the Patient Record (Edit).</li></ul>
            </div>
          </section>

          <!-- MENTAL HEALTH (Problem 2) -->
          <section class="page" id="page-mind">
            <div class="alerts-hero glass" style="background:linear-gradient(120deg,#4c1d95,#7c3aed 50%,#2563eb)">
              <div>
                <h3>&#129504; Psychological &amp; Behavioral Monitor</h3>
                <p>Stress from heart rate &amp; HRV vs. personal baseline, voice, and check-ins</p>
              </div>
              <span class="alerts-status-badge good" id="stressBadge">NO BASELINE</span>
            </div>
            <div class="kpi-grid">
              <div class="kpi glass"><b id="kStress">--</b><small>Stress index</small></div>
              <div class="kpi glass"><b id="kHrv">--</b><small>HRV RMSSD (ms)</small></div>
              <div class="kpi glass"><b id="kBaseHr">--</b><small>Baseline HR / HRV</small></div>
              <div class="kpi glass"><b id="kMood">--</b><small>Last check-in</small></div>
            </div>
            <div class="two-col">
              <div class="card-pad glass">
                <h4>Personal baseline</h4>
                <div class="note-small" style="margin:0 0 8px">Sit at rest with ECG leads on and finger on the SpO&#8322; sensor, then calibrate (60 s).</div>
                <div class="meter"><i id="calMeter"></i></div>
                <div class="form-actions">
                  <button type="button" class="btn btn-log btn-log-export" id="btnCalibrate">Calibrate baseline</button>
                  <button type="button" class="btn btn-log btn-secondary" id="btnVoice">&#127908; Voice check (8 s)</button>
                </div>
                <div class="note-small" id="voiceMsg">Voice tone: compares pitch and energy to your own baseline. First run saves the baseline.</div>
              </div>
              <div class="card-pad glass">
                <h4>Check-in questionnaire</h4>
                <div class="q-row"><span>Mood</span><select id="q1"><option value="1">1 Very low</option><option value="2">2</option><option value="3" selected>3</option><option value="4">4</option><option value="5">5 Very good</option></select></div>
                <div class="q-row"><span>Sleep quality</span><select id="q2"><option value="1">1 Very poor</option><option value="2">2</option><option value="3" selected>3</option><option value="4">4</option><option value="5">5 Very good</option></select></div>
                <div class="q-row"><span>Stress / tension</span><select id="q3"><option value="1">1 None</option><option value="2">2</option><option value="3" selected>3</option><option value="4">4</option><option value="5">5 Extreme</option></select></div>
                <div class="q-row"><span>Isolation / homesickness</span><select id="q4"><option value="1">1 None</option><option value="2">2</option><option value="3" selected>3</option><option value="4">4</option><option value="5">5 Extreme</option></select></div>
                <div class="q-row"><span>Workload pressure</span><select id="q5"><option value="1">1 None</option><option value="2">2</option><option value="3" selected>3</option><option value="4">4</option><option value="5">5 Extreme</option></select></div>
                <div class="form-actions"><button type="button" class="btn btn-primary" id="btnSurvey">Submit check-in</button></div>
                <div class="note-small" id="surveyMsg"></div>
              </div>
            </div>
            <div class="two-col">
              <div class="card-pad glass">
                <h4>&#128172; Support assistant</h4>
                <div class="chat-box" id="chatBox"></div>
                <div class="reply-row" id="chatReplies"></div>
                <div class="reply-row" style="margin-top:8px">
                  <input type="text" id="chatInput" placeholder="Talk to the assistant (Arabic or English)..." style="flex:1;min-width:140px;padding:8px 10px;border-radius:10px;border:1px solid #cbd5e1;font:inherit" />
                  <button type="button" class="btn btn-primary" id="btnChatSend">Send</button>
                </div>
                <div class="note-small"><span id="aiDot">&#9899;</span> <span id="aiStatus">AI: checking...</span> &middot; server <input type="text" id="aiUrl" style="width:170px;font-size:0.72rem;padding:3px 6px;border-radius:6px;border:1px solid #cbd5e1" /></div>
              </div>
              <div class="card-pad glass">
                <h4>&#128225; Ground team queue</h4>
                <div id="queueList"></div>
                <div class="form-actions">
                  <button type="button" class="btn btn-log btn-log-start" id="btnComm">&#128225; Communication session: send queue</button>
                </div>
                <div class="note-small">Alerts are held on board and delivered to ground specialists at the next communication session.</div>
              </div>
            </div>
          </section>

          <!-- DAILY REPORT -->
          <section class="page" id="page-report">
            <div class="logging-toolbar glass">
              <div class="logging-controls">
                <label for="reportDate">Day</label>
                <select id="reportDate"></select>
                <button type="button" class="btn btn-log btn-log-export" id="btnReportDownload">&#128196; Download report</button>
              </div>
              <div class="logging-stats"><span id="reportNote">End-of-day reports are saved automatically at midnight.</span></div>
            </div>
            <div class="report-text glass" id="reportBody">No data yet.</div>
            <div class="form-actions" style="margin-top:10px">
              <button type="button" class="btn btn-primary" id="btnAiReport">&#10024; AI summary for ground team</button>
              <select id="aiLang"><option value="English">English</option><option value="Arabic">العربية</option></select>
            </div>
            <div class="report-text glass" id="aiReportBody" style="margin-top:10px" hidden></div>
          </section>

          <!-- ALERTS -->
          <section class="page" id="page-alerts">
            <div class="alerts-page">
              <div class="alerts-hero glass">
                <div>
                  <h3>&#128680; Clinical Alert Center</h3>
                  <p>Live sensor status, warnings &amp; care suggestions</p>
                </div>
                <span class="alerts-status-badge good" id="alertBadge">SAFE</span>
              </div>
 
              <div class="alerts-summary">
                <div class="alerts-summary-card warn glass">
                  <span id="alertWarnCount">0</span>Warnings
                </div>
                <div class="alerts-summary-card ok glass">
                  <span id="alertOkCount">0</span>Normal
                </div>
                <div class="alerts-summary-card info glass">
                  <span id="alertInfoCount">0</span>Info
                </div>
              </div>
 
              <div class="alerts-scroll">
                <div class="alerts-section">
                  <h4 class="alerts-section-title">&#10084; Cardiac Monitoring</h4>
                  <div class="alert-row alert-info glass" id="alertRow1">
                    <div class="alert-row-icon" id="alertIcon1">&#10084;</div>
                    <div class="alert-row-body">
                      <div class="alert-row-top">
                        <strong id="alertTitle1">Heart Rate</strong>
                        <span class="alert-pill info" id="alertPill1">INFO</span>
                      </div>
                      <p id="alertMsg1">Waiting for sensor data...</p>
                      <p class="alert-tip" id="alertTip1">Normal resting range: 60–100 BPM.</p>
                    </div>
                  </div>
                  <div class="alert-row alert-info glass" id="alertRow2">
                    <div class="alert-row-icon" id="alertIcon2">&#9889;</div>
                    <div class="alert-row-body">
                      <div class="alert-row-top">
                        <strong id="alertTitle2">ECG Waveform</strong>
                        <span class="alert-pill info" id="alertPill2">INFO</span>
                      </div>
                      <p id="alertMsg2">Checking ECG signal...</p>
                      <p class="alert-tip" id="alertTip2">Ensure RA, LA, and RL electrodes are firmly attached.</p>
                    </div>
                  </div>
                </div>
 
                <div class="alerts-section">
                  <h4 class="alerts-section-title">&#128167; Oxygen &amp; Respiratory</h4>
                  <div class="alert-row alert-info glass" id="alertRow3">
                    <div class="alert-row-icon" id="alertIcon3">O&#8322;</div>
                    <div class="alert-row-body">
                      <div class="alert-row-top">
                        <strong id="alertTitle3">Blood Oxygen (SpO&#8322;)</strong>
                        <span class="alert-pill info" id="alertPill3">INFO</span>
                      </div>
                      <p id="alertMsg3">Place finger on pulse oximeter sensor.</p>
                      <p class="alert-tip" id="alertTip3">Keep hand still; normal SpO&#8322; is 95–100%.</p>
                    </div>
                  </div>
                </div>
 
                <div class="alerts-section">
                  <h4 class="alerts-section-title">&#127777; Temperature &amp; Environment</h4>
                  <div class="alert-row alert-info glass" id="alertRow4">
                    <div class="alert-row-icon" id="alertIcon4">&#127777;</div>
                    <div class="alert-row-body">
                      <div class="alert-row-top">
                        <strong id="alertTitle4">Body Temperature</strong>
                        <span class="alert-pill info" id="alertPill4">INFO</span>
                      </div>
                      <p id="alertMsg4">Monitoring body temperature...</p>
                      <p class="alert-tip" id="alertTip4">Normal body temp: 36.1–37.2 &deg;C.</p>
                    </div>
                  </div>
                  <div class="alert-row alert-info glass" id="alertRow5">
                    <div class="alert-row-icon" id="alertIcon5">&#127968;</div>
                    <div class="alert-row-body">
                      <div class="alert-row-top">
                        <strong id="alertTitle5">Room Environment</strong>
                        <span class="alert-pill info" id="alertPill5">INFO</span>
                      </div>
                      <p id="alertMsg5">Checking room temp and humidity...</p>
                      <p class="alert-tip" id="alertTip5">Ideal room: 20–24 &deg;C, humidity 40–60%.</p>
                    </div>
                  </div>
                </div>
 
                <div class="alerts-section">
                  <h4 class="alerts-section-title">&#128225; System Status</h4>
                  <div class="alert-row alert-info glass" id="alertRow6">
                    <div class="alert-row-icon" id="alertIcon6">&#128246;</div>
                    <div class="alert-row-body">
                      <div class="alert-row-top">
                        <strong id="alertTitle6">Device Connection</strong>
                        <span class="alert-pill info" id="alertPill6">INFO</span>
                      </div>
                      <p id="alertMsg6">Connecting to ESP32 monitor...</p>
                      <p class="alert-tip" id="alertTip6">Ensure ESP32 is powered and on the same WiFi network.</p>
                    </div>
                  </div>
                </div>
 
                <div class="alerts-suggestions glass">
                  <h4 class="alerts-section-title">&#128161; Clinical Suggestions</h4>
                  <ul class="alert-suggest-list" id="alertSuggestions">
                    <li>All systems initializing — suggestions will appear as data arrives.</li>
                  </ul>
                </div>
              </div>
            </div>
          </section>
        </div>
      </div>
    </div>
  </div>
 
  <script>
    const $ = (id) => document.getElementById(id);
    const pages = {
      dashboard: { title: "Vitals Monitor", sub: "Real-time cardiac and physiological monitoring" },
      patient: { title: "Astronaut Record", sub: "View and edit astronaut information and baselines" },
      logging: { title: "Data Logging", sub: "Record vitals at selected intervals and export" },
      alerts: { title: "Clinical Alerts", sub: "System warnings and sensor status" },
      bone: { title: "Bone & Muscle", sub: "Exercise adherence and bone/muscle loss risk" },
      mind: { title: "Mental Health", sub: "Stress, voice, check-ins and support" },
      report: { title: "Daily Report", sub: "End-of-day health summary for the crew surgeon" }
    };
    const ui = {
      clock: $("clock"), lastUpdate: $("lastUpdate"), pageTitle: $("pageTitle"), pageSubtitle: $("pageSubtitle"),
      bpm: $("bpm"), spo2: $("spo2"), bodyTemp: $("bodyTemp"),
      roomTemp: $("roomTemp"), humidity: $("humidity"),
      bpmBar: $("bpmBar"), spo2Bar: $("spo2Bar"), bodyTempBar: $("bodyTempBar"),
      roomTempBar: $("roomTempBar"), humBar: $("humBar"),
      bpmBadge: $("bpmBadge"), spo2Badge: $("spo2Badge"), tempBadge: $("tempBadge"),
      roomBadge: $("roomBadge"), humBadge: $("humBadge"),
      ecgBadge: $("ecgBadge"),
      alertBadge: $("alertBadge"),
      alertWarnCount: $("alertWarnCount"), alertOkCount: $("alertOkCount"), alertInfoCount: $("alertInfoCount"),
      alertSuggestions: $("alertSuggestions"),
      connText: $("connText"), liveDot: $("liveDot"),
      alertTitle1: $("alertTitle1"), alertMsg1: $("alertMsg1"), alertTip1: $("alertTip1"),
      alertIcon1: $("alertIcon1"), alertPill1: $("alertPill1"), alertRow1: $("alertRow1"),
      alertTitle2: $("alertTitle2"), alertMsg2: $("alertMsg2"), alertTip2: $("alertTip2"),
      alertIcon2: $("alertIcon2"), alertPill2: $("alertPill2"), alertRow2: $("alertRow2"),
      alertTitle3: $("alertTitle3"), alertMsg3: $("alertMsg3"), alertTip3: $("alertTip3"),
      alertIcon3: $("alertIcon3"), alertPill3: $("alertPill3"), alertRow3: $("alertRow3"),
      alertTitle4: $("alertTitle4"), alertMsg4: $("alertMsg4"), alertTip4: $("alertTip4"),
      alertIcon4: $("alertIcon4"), alertPill4: $("alertPill4"), alertRow4: $("alertRow4"),
      alertTitle5: $("alertTitle5"), alertMsg5: $("alertMsg5"), alertTip5: $("alertTip5"),
      alertIcon5: $("alertIcon5"), alertPill5: $("alertPill5"), alertRow5: $("alertRow5"),
      alertTitle6: $("alertTitle6"), alertMsg6: $("alertMsg6"), alertTip6: $("alertTip6"),
      alertIcon6: $("alertIcon6"), alertPill6: $("alertPill6"), alertRow6: $("alertRow6"),
      patientForm: $("patientForm"), saveMsg: $("saveMsg"),
      patientModal: $("patientModal"),
      viewAvatar: $("viewAvatar"),
      viewName: $("viewName"), viewId: $("viewId"), viewIdDetail: $("viewIdDetail"),
      viewBed: $("viewBed"), viewWard: $("viewWard"),
      viewAge: $("viewAge"), viewGender: $("viewGender"),
      viewBlood: $("viewBlood"),
      viewContact: $("viewContact"), viewNotes: $("viewNotes"),
      heartIcon: $("heartIcon"), dashPatientName: $("dashPatientName")
    };
 
    const PATIENT_KEY = "phm_patient_v1";
    const defaultPatient = {
      name: "", patientId: "", bed: "", ward: "",
      age: "", bloodGroup: "", gender: "", contact: "", notes: "",
      bmd: "", muscle: "", mission: "", exTarget: ""
    };
 
    const PLOT_MAX = 1023;
    const ECG_POLL_MS = 25;
    const BPM_UI_MS = 1000;
    const ECG_Y_MARGIN = 24;
    const SCROLL_STEP = 1;
    let ecgFail = 0, vitalsFail = 0;
    let connOnline = false;
    let connFailStreak = 0;
    const CONN_FAIL_LIMIT = 12;
    let canvasW = 0, canvasH = 0;
    let heightOld = 0;
    let traceReady = false;
    let ecgPollBusy = false;
    let leadsOffState = true;
    let lastVitals = { spo2: -1, finger: false, spo2Valid: false, bodyT: -999, roomT: 0, hum: 0, bme: false, hrv: -1 };
    let heartAudioCtx = null;
    let heartSoundOn = true;
    let heartSoundTimer = null;
    let lastSoundBpm = 0;
    let audioUnlocked = false;
    let latestBpm = 0;
    let displayedBpm = -1;
    let lastBpmUiTick = 0;
    let lastBeatAnimBpm = 0;
    let bpmUiReady = false;
    let prevLeadsOff = true;
    let logData = [];
    let logTimer = null;
    let logRunning = false;
    const LOG_KEY = "phm_log_v1";
    const MAX_LOG_ROWS = 500;
 
    const canvas = $("ecgCanvas");
    const ctx = canvas.getContext("2d");
 
    document.querySelectorAll(".nav-item").forEach((btn) => {
      btn.addEventListener("click", () => {
        const id = btn.dataset.page;
        document.querySelectorAll(".nav-item").forEach((b) => b.classList.remove("active"));
        document.querySelectorAll(".page").forEach((p) => p.classList.remove("active"));
        btn.classList.add("active");
        $("page-" + id).classList.add("active");
        ui.pageTitle.textContent = pages[id].title;
        ui.pageSubtitle.textContent = pages[id].sub;
        const soundBtn = $("btnSoundToggle");
        if (soundBtn) soundBtn.style.display = id === "dashboard" ? "" : "none";
        if (id === "dashboard") requestAnimationFrame(resizeCanvas);
        window.scrollTo(0, 0);
        const activePage = $("page-" + id);
        if (activePage) activePage.scrollTop = 0;
      });
    });
 
    const ecgStage = () => canvas.parentElement;
 
    function resizeCanvas() {
      const stage = ecgStage();
      if (!stage) return;
      const w = stage.clientWidth;
      const h = stage.clientHeight;
      if (w < 10 || h < 10) return;
      if (w === canvasW && h === canvasH) return;
      canvasW = w;
      canvasH = h;
      canvas.width = w;
      canvas.height = h;
      ctx.setTransform(1, 0, 0, 1, 0, 0);
      ctx.clearRect(0, 0, w, h);
      heightOld = h * 0.54;
      traceReady = false;
    }
 
    if (window.ResizeObserver && ecgStage()) {
      const ro = new ResizeObserver(() => resizeCanvas());
      ro.observe(ecgStage());
    }
    window.addEventListener("resize", resizeCanvas);
    window.addEventListener("orientationchange", () => {
      setTimeout(() => {
        resizeCanvas();
      }, 200);
    });
    requestAnimationFrame(() => requestAnimationFrame(resizeCanvas));
 
    function setBar(el, pct) { el.style.width = Math.max(6, Math.min(pct, 100)) + "%"; }
    function flashVital(el) {
      if (!el) return;
      el.classList.remove("vital-flash");
      void el.offsetWidth;
      el.classList.add("vital-flash");
    }
    function pulseBpmValue() {
      const el = ui.bpm;
      if (!el) return;
      el.classList.remove("bpm-pulse");
      void el.offsetWidth;
      el.classList.add("bpm-pulse");
    }
    function setBadge(el, text, kind) {
      el.textContent = text;
      if (el.id === "alertBadge") {
        el.className = "alerts-status-badge " + kind;
      } else if (el.id === "ecgBadge") {
        el.className = "ecg-badge-pill " + kind;
      } else {
        el.className = "badge " + kind;
      }
    }
    function fmtTime() {
      return new Date().toLocaleTimeString([], { hour: "2-digit", minute: "2-digit", second: "2-digit" });
    }
    function touchUpdate() { ui.lastUpdate.textContent = "Just now"; ui.clock.textContent = fmtTime(); }
 
    function setConn(ok) {
      if (connOnline === ok) return;
      connOnline = ok;
      ui.connText.textContent = ok ? "Live" : "Offline";
      ui.liveDot.className = ok ? "live-dot" : "live-dot off";
    }
 
    function markConnSuccess() {
      connFailStreak = 0;
      ecgFail = 0;
      setConn(true);
    }
 
    function markConnFailure() {
      connFailStreak++;
      if (connFailStreak >= CONN_FAIL_LIMIT) {
        setConn(false);
      }
    }
 
    function loadPatientForm(data) {
      $("inpName").value = data.name || "";
      $("inpId").value = data.patientId || "";
      $("inpBed").value = data.bed || "";
      $("inpWard").value = data.ward || "";
      $("inpAge").value = data.age || "";
      $("inpBlood").value = data.bloodGroup || "";
      $("inpGender").value = data.gender || "";
      $("inpContact").value = data.contact || "";
      $("inpNotes").value = data.notes || "";
      $("inpBmd").value = data.bmd || "";
      $("inpMuscle").value = data.muscle || "";
      $("inpMission").value = data.mission || "";
      $("inpExTarget").value = data.exTarget || "";
      updatePatientPreview(data);
    }
 
    function readPatientForm() {
      return {
        name: $("inpName").value.trim(),
        patientId: $("inpId").value.trim(),
        bed: $("inpBed").value.trim(),
        ward: $("inpWard").value.trim(),
        age: $("inpAge").value.trim(),
        bloodGroup: $("inpBlood").value,
        gender: $("inpGender").value,
        contact: $("inpContact").value.trim(),
        notes: $("inpNotes").value.trim(),
        bmd: $("inpBmd").value.trim(),
        muscle: $("inpMuscle").value.trim(),
        mission: $("inpMission").value,
        exTarget: $("inpExTarget").value.trim()
      };
    }
 
    function patientInitials(name) {
      const parts = (name || "").trim().split(/\s+/).filter(Boolean);
      if (!parts.length) return "?";
      if (parts.length === 1) return parts[0].slice(0, 2).toUpperCase();
      return (parts[0][0] + parts[parts.length - 1][0]).toUpperCase();
    }
 
    function updatePatientPreview(data) {
      const hasPatient = !!(data.name || data.patientId);
      ui.viewName.textContent = data.name || "No patient saved";
      ui.viewAvatar.textContent = patientInitials(data.name);
      ui.viewId.textContent = data.patientId || "No ID";
      ui.viewIdDetail.textContent = data.patientId || "--";
      ui.viewBed.textContent = data.bed || "--";
      ui.viewWard.textContent = data.ward || "--";
      ui.viewAge.textContent = data.age ? data.age + " yrs" : "--";
      ui.viewGender.textContent = data.gender || "--";
      ui.viewBlood.textContent = data.bloodGroup || "--";
      ui.viewContact.textContent = data.contact || "--";
      ui.viewNotes.textContent = data.notes || (hasPatient ? "No notes added." : "No notes added.");
      updateDashPatient();
    }
 
    function openPatientModal() {
      let data = defaultPatient;
      try {
        const saved = localStorage.getItem(PATIENT_KEY);
        if (saved) data = { ...defaultPatient, ...JSON.parse(saved) };
      } catch (e) {}
      loadPatientForm(data);
      ui.saveMsg.textContent = "";
      ui.patientModal.classList.add("open");
    }
 
    function closePatientModal() {
      ui.patientModal.classList.remove("open");
      ui.saveMsg.textContent = "";
    }
 
    function savePatient() {
      const data = readPatientForm();
      if (!data.name && !data.patientId) {
        ui.saveMsg.textContent = "Enter at least a name or patient ID.";
        ui.saveMsg.style.color = "#ef4444";
        return;
      }
      try {
        localStorage.setItem(PATIENT_KEY, JSON.stringify(data));
        updatePatientPreview(data);
        ui.saveMsg.textContent = "Patient details saved.";
        ui.saveMsg.style.color = "#16a34a";
        setTimeout(closePatientModal, 400);
      } catch (e) {
        ui.saveMsg.textContent = "Could not save. Browser storage may be full.";
        ui.saveMsg.style.color = "#ef4444";
      }
    }
 
    function clearPatientForm() {
      loadPatientForm(defaultPatient);
      try { localStorage.removeItem(PATIENT_KEY); } catch (e) {}
      ui.saveMsg.textContent = "All patient data cleared.";
      ui.saveMsg.style.color = "#64748b";
      setTimeout(closePatientModal, 500);
    }
 
    function initPatientForm() {
      let data = defaultPatient;
      try {
        const saved = localStorage.getItem(PATIENT_KEY);
        if (saved) data = { ...defaultPatient, ...JSON.parse(saved) };
      } catch (e) {}
      updatePatientPreview(data);
      $("btnEditPatient").addEventListener("click", openPatientModal);
      $("btnClosePatientModal").addEventListener("click", closePatientModal);
      $("btnCancelPatient").addEventListener("click", closePatientModal);
      $("patientModalBackdrop").addEventListener("click", closePatientModal);
      $("btnSavePatient").addEventListener("click", savePatient);
      $("btnClearPatient").addEventListener("click", clearPatientForm);
      ui.patientForm.addEventListener("submit", (e) => { e.preventDefault(); savePatient(); });
    }
    initPatientForm();
 
    function loadPatientData() {
      try {
        const saved = localStorage.getItem(PATIENT_KEY);
        if (saved) return { ...defaultPatient, ...JSON.parse(saved) };
      } catch (e) {}
      return { ...defaultPatient };
    }
 
    function fmtLogTime(d) {
      return d.toLocaleString([], {
        year: "numeric", month: "2-digit", day: "2-digit",
        hour: "2-digit", minute: "2-digit", second: "2-digit"
      });
    }
 
    function captureLogRow() {
      const bpmVal = parseInt(ui.bpm.textContent, 10);
      return {
        ts: fmtLogTime(new Date()),
        bpm: (!isNaN(bpmVal) && ui.bpm.textContent !== "--") ? bpmVal : "",
        spo2: (lastVitals.spo2Valid && lastVitals.spo2 > 0) ? lastVitals.spo2 : "",
        bodyT: (lastVitals.bodyT > -100) ? lastVitals.bodyT.toFixed(1) : "",
        roomT: lastVitals.bme ? lastVitals.roomT.toFixed(1) : "",
        hum: lastVitals.bme ? lastVitals.hum.toFixed(1) : ""
      };
    }
 
    function updateLogTable() {
      const tbody = $("logTableBody");
      if (!logData.length) {
        tbody.innerHTML = '<tr><td colspan="7" class="log-empty">No data logged yet. Press Start to begin recording.</td></tr>';
        $("logCount").textContent = "0 records";
        return;
      }
      $("logCount").textContent = logData.length + " record" + (logData.length === 1 ? "" : "s");
      let html = "";
      const start = Math.max(0, logData.length - 200);
      for (let i = start; i < logData.length; i++) {
        const r = logData[i];
        html += "<tr><td>" + (i + 1) + "</td><td>" + r.ts + "</td><td>" + (r.bpm !== "" ? r.bpm : "--") +
          "</td><td>" + (r.spo2 !== "" ? r.spo2 : "--") + "</td><td>" + (r.bodyT !== "" ? r.bodyT : "--") +
          "</td><td>" + (r.roomT !== "" ? r.roomT : "--") + "</td><td>" + (r.hum !== "" ? r.hum : "--") + "</td></tr>";
      }
      tbody.innerHTML = html;
      const scroll = tbody.closest(".logging-table-scroll");
      if (scroll) scroll.scrollTop = scroll.scrollHeight;
    }
 
    function saveLogData() {
      try { localStorage.setItem(LOG_KEY, JSON.stringify(logData)); } catch (e) {}
    }
 
    function loadLogData() {
      try {
        const saved = localStorage.getItem(LOG_KEY);
        if (saved) logData = JSON.parse(saved);
      } catch (e) { logData = []; }
      updateLogTable();
    }
 
    function addLogEntry() {
      logData.push(captureLogRow());
      if (logData.length > MAX_LOG_ROWS) logData.shift();
      updateLogTable();
      saveLogData();
    }
 
    function getLogIntervalMs() {
      return parseInt($("logInterval").value, 10) || 5000;
    }
 
    function updateLogIntervalLabel() {
      const ms = getLogIntervalMs();
      const sec = ms / 1000;
      $("logIntervalLabel").textContent = "Every " + sec + "s";
    }
 
    function startLogging() {
      if (logRunning) return;
      logRunning = true;
      $("logStatus").textContent = "Recording";
      $("logStatus").className = "log-status-pill running";
      addLogEntry();
      logTimer = setInterval(addLogEntry, getLogIntervalMs());
    }
 
    function stopLogging() {
      logRunning = false;
      if (logTimer) { clearInterval(logTimer); logTimer = null; }
      $("logStatus").textContent = "Stopped";
      $("logStatus").className = "log-status-pill stopped";
    }
 
    function restartLoggingIfActive() {
      if (!logRunning) return;
      stopLogging();
      startLogging();
    }
 
    function clearLogging() {
      stopLogging();
      logData = [];
      try { localStorage.removeItem(LOG_KEY); } catch (e) {}
      updateLogTable();
    }
 
    function csvCell(v) {
      return '"' + String(v == null ? "" : v).replace(/"/g, '""') + '"';
    }
 
    function exportLogExcel() {
      if (!logData.length) {
        alert("No data to export. Start logging first.");
        return;
      }
      const p = loadPatientData();
      const rows = [];
      rows.push(["Patient  Health Monitor - Vitals Data Log"]);
      rows.push([]);
      rows.push(["Patient Name", p.name || "N/A"]);
      rows.push(["Patient ID", p.patientId || "N/A"]);
      rows.push(["Bed", p.bed || "N/A"]);
      rows.push(["Ward", p.ward || "N/A"]);
      rows.push(["Age", p.age ? p.age + " years" : "N/A"]);
      rows.push(["Gender", p.gender || "N/A"]);
      rows.push(["Blood Group", p.bloodGroup || "N/A"]);
      rows.push(["Contact", p.contact || "N/A"]);
      rows.push(["Clinical Notes", p.notes || "N/A"]);
      rows.push(["Export Date", fmtLogTime(new Date())]);
      rows.push(["Logging Interval", (getLogIntervalMs() / 1000) + " seconds"]);
      rows.push(["Total Records", logData.length]);
      rows.push([]);
      rows.push(["#", "Timestamp", "BPM", "SpO2 (%)", "Body Temp (C)", "Room Temp (C)", "Humidity (%)"]);
      logData.forEach((r, i) => {
        rows.push([i + 1, r.ts, r.bpm, r.spo2, r.bodyT, r.roomT, r.hum]);
      });
      const csv = rows.map((row) => row.map(csvCell).join(",")).join("\r\n");
      const blob = new Blob(["\ufeff" + csv], { type: "application/vnd.ms-excel;charset=utf-8;" });
      const url = URL.createObjectURL(blob);
      const a = document.createElement("a");
      const date = new Date().toISOString().slice(0, 10);
      const pname = (p.name || "Patient").replace(/[^a-z0-9]/gi, "_");
      a.href = url;
      a.download = "PHM_Vitals_" + pname + "_" + date + ".xls";
      document.body.appendChild(a);
      a.click();
      document.body.removeChild(a);
      URL.revokeObjectURL(url);
    }
 
    function initLogging() {
      loadLogData();
      updateLogIntervalLabel();
      $("logInterval").addEventListener("change", () => {
        updateLogIntervalLabel();
        restartLoggingIfActive();
      });
      $("btnLogStart").addEventListener("click", startLogging);
      $("btnLogStop").addEventListener("click", stopLogging);
      $("btnLogClear").addEventListener("click", () => {
        if (!logData.length || confirm("Clear all logged data?")) clearLogging();
      });
      $("btnLogExport").addEventListener("click", exportLogExcel);
    }
    initLogging();
 
    function updateRoomUi(roomT, hum, bmeOk) {
      if (bmeOk) {
        ui.roomTemp.textContent = roomT.toFixed(1);
        ui.humidity.textContent = hum.toFixed(1);
        flashVital($("roomTempWrap"));
        flashVital($("humidityWrap"));
        setBar(ui.roomTempBar, Math.min(roomT * 3, 100));
        setBar(ui.humBar, hum);
        setBadge(ui.roomBadge, "NORMAL", "good");
        setBadge(ui.humBadge, "NORMAL", "good");
      } else {
        ui.roomTemp.textContent = "--";
        ui.humidity.textContent = "--";
        setBar(ui.roomTempBar, 6);
        setBar(ui.humBar, 6);
        setBadge(ui.roomBadge, "WAIT", "watch");
        setBadge(ui.humBadge, "WAIT", "watch");
      }
    }
 
    function getHeartAudioCtx() {
      if (!heartAudioCtx) {
        heartAudioCtx = new (window.AudioContext || window.webkitAudioContext)();
      }
      return heartAudioCtx;
    }
 
    async function unlockHeartAudio() {
      try {
        const ctx = getHeartAudioCtx();
        if (ctx.state === "suspended") await ctx.resume();
        const buffer = ctx.createBuffer(1, 1, 22050);
        const source = ctx.createBufferSource();
        source.buffer = buffer;
        source.connect(ctx.destination);
        source.start(0);
        audioUnlocked = true;
        if (heartSoundOn && latestBpm > 0 && !leadsOffState) startHeartSound(latestBpm);
      } catch (e) {}
    }
 
    function playMonitorBeep() {
      if (!heartSoundOn || !audioUnlocked) return;
      try {
        const ctx = getHeartAudioCtx();
        const t = ctx.currentTime;
        const master = ctx.createGain();
        master.gain.setValueAtTime(0.14, t);
        master.connect(ctx.destination);
 
        const osc1 = ctx.createOscillator();
        const g1 = ctx.createGain();
        osc1.type = "sine";
        osc1.frequency.setValueAtTime(920, t);
        osc1.frequency.exponentialRampToValueAtTime(720, t + 0.05);
        g1.gain.setValueAtTime(0, t);
        g1.gain.linearRampToValueAtTime(1, t + 0.006);
        g1.gain.exponentialRampToValueAtTime(0.001, t + 0.065);
        osc1.connect(g1);
        g1.connect(master);
        osc1.start(t);
        osc1.stop(t + 0.07);
 
        const osc2 = ctx.createOscillator();
        const g2 = ctx.createGain();
        osc2.type = "sine";
        osc2.frequency.setValueAtTime(580, t + 0.09);
        g2.gain.setValueAtTime(0, t + 0.09);
        g2.gain.linearRampToValueAtTime(0.55, t + 0.1);
        g2.gain.exponentialRampToValueAtTime(0.001, t + 0.17);
        osc2.connect(g2);
        g2.connect(master);
        osc2.start(t + 0.09);
        osc2.stop(t + 0.18);
      } catch (e) {}
    }
 
    function stopHeartSound() {
      if (heartSoundTimer) {
        clearInterval(heartSoundTimer);
        heartSoundTimer = null;
      }
      lastSoundBpm = 0;
    }
 
    function startHeartSound(bpm) {
      if (!bpm || bpm <= 0 || leadsOffState) {
        stopHeartSound();
        return;
      }
      if (!heartSoundOn) {
        stopHeartSound();
        return;
      }
      if (heartSoundTimer && lastSoundBpm === bpm) return;
      stopHeartSound();
      lastSoundBpm = bpm;
      const interval = 60000 / bpm;
      if (audioUnlocked) playMonitorBeep();
      heartSoundTimer = setInterval(() => {
        if (audioUnlocked) playMonitorBeep();
      }, interval);
    }
 
    function syncSoundToggleBtn() {
      const btn = $("btnSoundToggle");
      if (!btn) return;
      btn.classList.toggle("muted", !heartSoundOn);
      btn.title = heartSoundOn ? "Mute heartbeat sound" : "Enable heartbeat sound";
      btn.setAttribute("aria-label", btn.title);
    }
 
    function initHeartSound() {
      syncSoundToggleBtn();
      const unlockOnce = () => { unlockHeartAudio(); };
      document.addEventListener("click", unlockOnce, { once: true, passive: true, capture: true });
      document.addEventListener("touchstart", unlockOnce, { once: true, passive: true, capture: true });
      $("btnSoundToggle").addEventListener("click", async (e) => {
        e.stopPropagation();
        await unlockHeartAudio();
        heartSoundOn = !heartSoundOn;
        syncSoundToggleBtn();
        if (heartSoundOn) {
          if (latestBpm > 0 && !leadsOffState) startHeartSound(latestBpm);
        } else {
          stopHeartSound();
        }
      });
    }
    initHeartSound();
 
    function updateDashPatient() {
      try {
        const saved = localStorage.getItem(PATIENT_KEY);
        if (saved) {
          const p = JSON.parse(saved);
          if (p.name) {
            ui.dashPatientName.textContent = p.name;
            return;
          }
        }
      } catch (e) {}
      ui.dashPatientName.textContent = "Astronaut Monitor";
    }
 
    function setHeartBeatAnim(bpm) {
      const el = ui.heartIcon;
      if (!el) return;
      const active = bpm > 0 && !leadsOffState;
      if (!active) {
        el.classList.remove("beating");
        lastBeatAnimBpm = 0;
        stopHeartSound();
        return;
      }
      if (!el.classList.contains("beating")) el.classList.add("beating");
      if (lastBeatAnimBpm !== bpm) {
        lastBeatAnimBpm = bpm;
        el.style.setProperty("--beat-dur", (60 / bpm) + "s");
      }
      startHeartSound(bpm);
    }
 
    function applyBpmUi(bpm) {
      displayedBpm = bpm;
      if (bpm > 0) {
        const changed = ui.bpm.textContent !== String(bpm);
        ui.bpm.textContent = bpm;
        if (changed) pulseBpmValue();
        setBar(ui.bpmBar, bpm);
        setBadge(ui.bpmBadge, bpm >= 60 && bpm <= 100 ? "NORMAL" : "CHECK", bpm >= 60 && bpm <= 100 ? "good" : "watch");
        setHeartBeatAnim(bpm);
      } else {
        ui.bpm.textContent = "--";
        setBar(ui.bpmBar, 6);
        setBadge(ui.bpmBadge, "WAIT", "watch");
        setHeartBeatAnim(0);
      }
    }
 
    function maybeUpdateBpmUi(bpm) {
      latestBpm = bpm;
      const now = Date.now();
      const leadsChanged = prevLeadsOff !== leadsOffState;
      prevLeadsOff = leadsOffState;
      const urgent = bpm <= 0 || leadsOffState || leadsChanged;
      if (urgent) {
        lastBpmUiTick = now;
        bpmUiReady = false;
        applyBpmUi(bpm);
        return;
      }
      if (!bpmUiReady || now - lastBpmUiTick >= BPM_UI_MS) {
        lastBpmUiTick = now;
        bpmUiReady = true;
        applyBpmUi(bpm);
      }
    }
 
    function updateSpo2Ui(spo2, finger, spo2Valid) {
      if (finger && spo2Valid && spo2 > 0) {
        ui.spo2.textContent = spo2;
        flashVital($("spo2Wrap"));
        setBar(ui.spo2Bar, spo2);
        setBadge(ui.spo2Badge, spo2 >= 95 ? "NORMAL" : "LOW", spo2 >= 95 ? "good" : "watch");
      } else {
        ui.spo2.textContent = "--";
        setBar(ui.spo2Bar, 6);
        setBadge(ui.spo2Badge, finger ? "WAIT" : "WAIT", "watch");
      }
    }
 
    function updateBodyUi(temp) {
      if (temp > -100) {
        ui.bodyTemp.textContent = temp.toFixed(1);
        flashVital($("bodyTempWrap"));
        setBar(ui.bodyTempBar, temp * 2);
        const ok = temp >= 36.1 && temp <= 37.2;
        setBadge(ui.tempBadge, ok ? "NORMAL" : "CHECK", ok ? "good" : "watch");
      } else {
        ui.bodyTemp.textContent = "--";
        setBar(ui.bodyTempBar, 6);
        setBadge(ui.tempBadge, "WAIT", "watch");
      }
    }
 
    function setAlertRow(n, cfg) {
      const row = ui["alertRow" + n];
      const pill = ui["alertPill" + n];
      ui["alertTitle" + n].textContent = cfg.title;
      ui["alertMsg" + n].textContent = cfg.msg;
      if (ui["alertTip" + n]) ui["alertTip" + n].textContent = cfg.tip;
      if (ui["alertIcon" + n]) ui["alertIcon" + n].textContent = cfg.icon;
      pill.textContent = cfg.pill;
      pill.className = "alert-pill " + cfg.state;
      row.className = "alert-row alert-" + cfg.state + " glass";
      return cfg.state;
    }
 
    function updateAlerts(leadsOff, bpm, spo2, finger, bodyT) {
      const v = lastVitals;
      let warnN = 0, okN = 0, infoN = 0;
      const suggestions = [];
 
      function countState(s) {
        if (s === "ok") okN++;
        else if (s === "warn" || s === "bad") warnN++;
        else infoN++;
      }
 
      // 1 — Heart rate
      if (leadsOff) {
        countState(setAlertRow(1, {
          title: "Heart Rate — Leads Off",
          msg: "Cannot measure BPM without ECG electrodes.",
          tip: "Attach RA, LA, and RL pads. Clean skin with alcohol wipe first.",
          icon: "\u26A0", pill: "ALERT", state: "bad"
        }));
        suggestions.push("Re-attach all three ECG electrodes and verify cable connections.");
      } else if (bpm > 100) {
        countState(setAlertRow(1, {
          title: "Elevated Heart Rate",
          msg: bpm + " BPM detected — above normal resting range.",
          tip: "Ensure patient is at rest. Recheck in 5 minutes.",
          icon: "\u2764", pill: "CHECK", state: "warn"
        }));
        suggestions.push("Heart rate is elevated — confirm patient is resting and hydrated.");
      } else if (bpm > 0 && bpm < 60) {
        countState(setAlertRow(1, {
          title: "Low Heart Rate",
          msg: bpm + " BPM detected — below normal resting range.",
          tip: "Verify electrode placement. Consult clinician if persistent.",
          icon: "\u2764", pill: "CHECK", state: "warn"
        }));
        suggestions.push("Bradycardia detected — verify sensor contact and patient status.");
      } else if (bpm > 0) {
        countState(setAlertRow(1, {
          title: "Heart Rate Normal",
          msg: bpm + " BPM — within healthy resting range.",
          tip: "Continue routine monitoring every few minutes.",
          icon: "\u2705", pill: "NORMAL", state: "ok"
        }));
      } else {
        countState(setAlertRow(1, {
          title: "Detecting Heartbeat",
          msg: "Leads connected. Waiting for stable BPM reading.",
          tip: "Keep patient still for accurate heart rate detection.",
          icon: "\u23F3", pill: "WAIT", state: "info"
        }));
      }
 
      // 2 — ECG waveform
      if (leadsOff) {
        countState(setAlertRow(2, {
          title: "No ECG Signal",
          msg: "Waveform unavailable — leads disconnected.",
          tip: "Press electrodes firmly. Check LO+ and LO- indicator wires.",
          icon: "\u26A1", pill: "ALERT", state: "bad"
        }));
      } else {
        countState(setAlertRow(2, {
          title: "ECG Streaming Live",
          msg: "PQRST waveform updating in real time on dashboard.",
          tip: "Trace should stay centered. Report unusual spikes to clinician.",
          icon: "\u26A1", pill: "LIVE", state: "ok"
        }));
      }
 
      // 3 — SpO2
      if (!finger) {
        countState(setAlertRow(3, {
          title: "SpO\u2082 — No Finger Detected",
          msg: "Place index finger on the MAX30102 sensor.",
          tip: "Remove nail polish. Warm cold fingers before measuring.",
          icon: "O\u2082", pill: "WAIT", state: "info"
        }));
        suggestions.push("Place finger on SpO\u2082 sensor with light, steady pressure.");
      } else if (spo2 > 0 && spo2 < 90 && v.spo2Valid) {
        countState(setAlertRow(3, {
          title: "Critical Low SpO\u2082",
          msg: spo2 + "% — critically low oxygen saturation.",
          tip: "Seek immediate clinical attention. Check airway and breathing.",
          icon: "\u26A0", pill: "CRITICAL", state: "bad"
        }));
        suggestions.push("URGENT: SpO\u2082 critically low — notify clinical staff immediately.");
      } else if (spo2 > 0 && spo2 < 95 && v.spo2Valid) {
        countState(setAlertRow(3, {
          title: "Low SpO\u2082",
          msg: spo2 + "% — below normal range (95–100%).",
          tip: "Reposition finger. Ensure sensor is clean and finger is warm.",
          icon: "O\u2082", pill: "CHECK", state: "warn"
        }));
        suggestions.push("Reposition finger on oximeter — reading below 95%.");
      } else if (spo2 > 0 && v.spo2Valid) {
        countState(setAlertRow(3, {
          title: "SpO\u2082 Normal",
          msg: "Blood oxygen at " + spo2 + "% — within healthy range.",
          tip: "Maintain steady finger contact for continuous monitoring.",
          icon: "\u2705", pill: "NORMAL", state: "ok"
        }));
      } else {
        countState(setAlertRow(3, {
          title: "Calculating SpO\u2082",
          msg: "Finger detected. Algorithm stabilizing reading...",
          tip: "Hold perfectly still for 10–15 seconds.",
          icon: "O\u2082", pill: "WAIT", state: "info"
        }));
      }
 
      // 4 — Body temperature
      if (bodyT > 37.5) {
        countState(setAlertRow(4, {
          title: "Elevated Body Temperature",
          msg: bodyT.toFixed(1) + " \u00B0C — above normal (fever range).",
          tip: "Monitor for other symptoms. Notify clinician if rising.",
          icon: "\uD83C\uDF21", pill: "CHECK", state: "warn"
        }));
        suggestions.push("Body temperature elevated — monitor closely and log readings.");
      } else if (bodyT > 0 && bodyT < 35.5) {
        countState(setAlertRow(4, {
          title: "Low Body Temperature",
          msg: bodyT.toFixed(1) + " \u00B0C — below normal range.",
          tip: "Check sensor placement on skin. Keep patient warm.",
          icon: "\uD83C\uDF21", pill: "CHECK", state: "warn"
        }));
        suggestions.push("Hypothermia range detected — verify probe contact and warm patient.");
      } else if (bodyT > -100) {
        countState(setAlertRow(4, {
          title: "Body Temperature Normal",
          msg: bodyT.toFixed(1) + " \u00B0C — within normal range.",
          tip: "NTC thermistor reading stable.",
          icon: "\u2705", pill: "NORMAL", state: "ok"
        }));
      } else {
        countState(setAlertRow(4, {
          title: "Body Temp — Waiting",
          msg: "NTC thermistor sensor initializing...",
          tip: "Ensure thermistor has firm skin contact.",
          icon: "\uD83C\uDF21", pill: "WAIT", state: "info"
        }));
      }
 
      // 5 — Room environment
      if (v.bme) {
        let envState = "ok";
        let envPill = "NORMAL";
        let envTitle = "Room Environment Normal";
        let envMsg = "Room " + v.roomT.toFixed(1) + " \u00B0C \u00B7 Humidity " + v.hum.toFixed(1) + "%";
        let envTip = "Conditions within comfortable clinical range.";
        if (v.roomT > 28 || v.roomT < 18) {
          envState = "warn"; envPill = "CHECK";
          envTitle = "Room Temperature Alert";
          envMsg = "Room temp " + v.roomT.toFixed(1) + " \u00B0C — outside ideal 18–28 \u00B0C.";
          envTip = "Adjust HVAC or ventilation for patient comfort.";
          suggestions.push("Room temperature out of range — check ventilation.");
        }
        if (v.hum > 70 || v.hum < 30) {
          envState = "warn"; envPill = "CHECK";
          envTitle = "Humidity Alert";
          envMsg = "Humidity " + v.hum.toFixed(1) + "% — outside ideal 30–70%.";
          envTip = "Use dehumidifier or humidifier as needed.";
          suggestions.push("Room humidity out of range — adjust environmental controls.");
        }
        countState(setAlertRow(5, {
          title: envTitle, msg: envMsg, tip: envTip,
          icon: "\uD83C\uDFE0", pill: envPill, state: envState
        }));
      } else {
        countState(setAlertRow(5, {
          title: "BME280 Sensor Waiting",
          msg: "Room temperature and humidity sensor not ready.",
          tip: "Check BME280 I2C wiring (SDA=21, SCL=22).",
          icon: "\uD83C\uDFE0", pill: "WAIT", state: "info"
        }));
      }
 
      // 6 — Connection
      if (connOnline) {
        countState(setAlertRow(6, {
          title: "Monitor Connected",
          msg: "ESP32 live link active. Data streaming normally.",
          tip: "If readings freeze, refresh browser or check WiFi signal.",
          icon: "\uD83D\uDCF6", pill: "LIVE", state: "ok"
        }));
      } else {
        countState(setAlertRow(6, {
          title: "Monitor Offline",
          msg: "Lost connection to ESP32  health monitor.",
          tip: "Verify ESP32 power, WiFi credentials, and router range.",
          icon: "\u274C", pill: "OFFLINE", state: "bad"
        }));
        suggestions.push("Device offline — check ESP32 power and WiFi connection.");
      }
 
      ui.alertWarnCount.textContent = warnN;
      ui.alertOkCount.textContent = okN;
      ui.alertInfoCount.textContent = infoN;
 
      if (!suggestions.length) {
        suggestions.push("All vitals within normal limits. Continue routine monitoring.");
      }
      ui.alertSuggestions.innerHTML = suggestions.map((s) => "<li>" + s + "</li>").join("");
 
      const overall = warnN > 0 ? "watch" : (okN > 0 ? "good" : "watch");
      setBadge(ui.alertBadge, warnN > 0 ? "CHECK" : "SAFE", overall);
    }
 
    function valueToY(v, h, leadsOff) {
      if (leadsOff) return h * 0.54;
      const plotH = h - ECG_Y_MARGIN * 2;
      const c = Math.max(0, Math.min(PLOT_MAX, v));
      return ECG_Y_MARGIN + plotH * (1 - c / PLOT_MAX);
    }
 
    function drawEcgPoint(v, leadsOff) {
      const w = canvasW;
      const h = canvasH;
      if (w < 8 || h < 8) return;
 
      const y = valueToY(v, h, leadsOff);
 
      if (traceReady) {
        const imageData = ctx.getImageData(SCROLL_STEP, 0, w - SCROLL_STEP, h);
        ctx.putImageData(imageData, 0, 0);
        ctx.clearRect(w - SCROLL_STEP, 0, SCROLL_STEP, h);
      } else {
        traceReady = true;
        heightOld = y;
      }
 
      const x0 = Math.max(0, w - SCROLL_STEP - 1);
      const x1 = w - 1;
      ctx.beginPath();
      ctx.moveTo(x0, heightOld);
      ctx.lineTo(x1, y);
      ctx.strokeStyle = leadsOff ? "#67e8f9" : "#16a34a";
      ctx.lineWidth = 2.2;
      ctx.lineJoin = "round";
      ctx.lineCap = "round";
      ctx.stroke();
      heightOld = y;
    }
 
    function drawEcgSamples(samples, leadsOff) {
      if (!samples || !samples.length) return;
      for (let i = 0; i < samples.length; i++) {
        drawEcgPoint(samples[i], leadsOff);
      }
    }
 
    async function pollEcg() {
      if (ecgPollBusy) return;
      ecgPollBusy = true;
      try {
        const r = await fetch("/api/ecg", { cache: "no-store" });
        if (!r.ok) throw new Error("ecg");
        const d = await r.json();
        markConnSuccess();
        touchUpdate();
        leadsOffState = !!d.lo;
        maybeUpdateBpmUi(d.bpm);
        setBadge(ui.ecgBadge, d.lo ? "LEADS OFF" : "LIVE", d.lo ? "watch" : "live");
        const samples = Array.isArray(d.v) ? d.v : [d.v];
        drawEcgSamples(samples, d.lo);
        updateAlerts(leadsOffState, displayedBpm > 0 ? displayedBpm : d.bpm, lastVitals.spo2, lastVitals.finger, lastVitals.bodyT);
      } catch (e) {
        ecgFail++;
        markConnFailure();
        if (!connOnline) setBadge(ui.ecgBadge, "ERROR", "bad");
      } finally {
        ecgPollBusy = false;
      }
    }
 
    async function pollVitals() {
      try {
        const r = await fetch("/api/vitals", { cache: "no-store" });
        if (!r.ok) throw new Error("vitals");
        const d = await r.json();
        vitalsFail = 0;
        markConnSuccess();
        touchUpdate();
        lastVitals = { spo2: d.spo2, finger: d.finger, bodyT: d.bodyT, roomT: d.roomT, hum: d.hum, bme: d.bme, spo2Valid: !!d.spo2Valid, hrv: (typeof d.hrv === "number") ? d.hrv : -1 };
        updateSpo2Ui(d.spo2, d.finger, d.spo2Valid);
        updateBodyUi(d.bodyT);
        updateRoomUi(d.roomT, d.hum, d.bme);
        const bpm = displayedBpm > 0 ? displayedBpm : latestBpm;
        updateAlerts(leadsOffState, bpm > 0 ? bpm : -1, d.spo2, d.finger, d.bodyT);
      } catch (e) {
        vitalsFail++;
        markConnFailure();
      }
    }
 
    // ================= Astronaut health layer (PDF: bone/muscle + psychological) =================
    const ASTRO_KEY = "phm_astro_v1";
    const CHECKUP_DUE_DAYS = 14;
    const PERSIST_MS = 10 * 60 * 1000;
    const QUEUE_DEDUPE_MS = 30 * 60 * 1000;
    const STRESS_HIGH = 60;
    const CALIB_MS = 60 * 1000;
    const pad2 = (n) => (n < 10 ? "0" : "") + n;
    const esc = (s) => String(s).replace(/[&<>"]/g, (c) => ({ "&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;" }[c]));
    const clamp = (v, lo, hi) => Math.max(lo, Math.min(hi, v));
    const mean = (a) => a.reduce((s, x) => s + x, 0) / a.length;

    function dayKey(d) {
      d = d || new Date();
      return d.getFullYear() + "-" + pad2(d.getMonth() + 1) + "-" + pad2(d.getDate());
    }
    function parseDay(k) { const p = k.split("-"); return new Date(+p[0], +p[1] - 1, +p[2]); }
    function daysBetween(a, b) {
      const ka = typeof a === "string" ? a : dayKey(a);
      const kb = typeof b === "string" ? b : dayKey(b);
      return Math.round((parseDay(kb) - parseDay(ka)) / 86400000);
    }

    function loadAstro() {
      const base = { days: {}, baseline: null, voiceBase: null, lastCheckup: "", queue: [], lastSurvey: null };
      try {
        const s = localStorage.getItem(ASTRO_KEY);
        if (s) {
          const a = { ...base, ...JSON.parse(s) };
          const keys = Object.keys(a.days).sort();
          while (keys.length > 60) delete a.days[keys.shift()];
          return a;
        }
      } catch (e) {}
      return base;
    }
    let astro = loadAstro();
    function saveAstro() { try { localStorage.setItem(ASTRO_KEY, JSON.stringify(astro)); } catch (e) {} }
    function getDay(key) {
      key = key || dayKey();
      if (!astro.days[key]) {
        astro.days[key] = { zoneSec: 0, sesSec: 0, sessions: 0, hrMax: 0, spo2Min: 0,
          hrSum: 0, hrN: 0, hrvSum: 0, hrvN: 0, spo2Sum: 0, spo2N: 0, tSum: 0, tN: 0,
          stressSum: 0, stressN: 0, stressMax: 0, highSec: 0, surveys: [], voice: [] };
      }
      return astro.days[key];
    }
    function setHeroBadge(el, text, kind) { el.textContent = text; el.className = "alerts-status-badge " + kind; }

    // ---------- Ground queue ----------
    function queueAlert(level, text, key) {
      const now = Date.now();
      if (key && astro.queue.some((q) => q.key === key && now - q.ts < QUEUE_DEDUPE_MS)) return;
      astro.queue.push({ ts: now, level: level, text: text, key: key || "", sent: false });
      if (astro.queue.length > 100) astro.queue.shift();
      saveAstro();
      renderQueue();
    }
    function renderQueue() {
      const pending = astro.queue.filter((q) => !q.sent).length;
      $("btnComm").innerHTML = "&#128225; Communication session: send queue (" + pending + " pending)";
      const items = astro.queue.slice(-8).reverse();
      $("queueList").innerHTML = items.length ? items.map((q) => {
        const cls = q.level === "bad" ? "bad" : q.level === "warn" ? "warn" : "info";
        const t = new Date(q.ts).toLocaleTimeString([], { hour: "2-digit", minute: "2-digit" });
        return '<div class="queue-item"><span class="alert-pill ' + cls + '">' + (q.sent ? "SENT" : "PENDING") + "</span><span>" + t + " &mdash; " + esc(q.text) + "</span></div>";
      }).join("") : '<div class="note-small">No alerts queued.</div>';
    }

    // ---------- Patient-derived settings ----------
    function astroSettings() {
      const p = loadPatientData();
      const age = parseFloat(p.age);
      return {
        p: p,
        maxHr: age > 0 ? 220 - age : 190,
        target: parseFloat(p.exTarget) > 0 ? parseFloat(p.exTarget) : 120,
        bmd: parseFloat(p.bmd) || 0,
        muscle: parseFloat(p.muscle) || 0,
        mission: p.mission || ""
      };
    }

    // ---------- Problem 1: exercise session + bone/muscle model ----------
    let ses = { running: false, startMs: 0, sec: 0, hr: 0, hrMax: 0, spo2Min: 0, lowSpo2Run: 0, highHrRun: 0 };

    function startSession() {
      if (ses.running) return;
      ses = { running: true, startMs: Date.now(), sec: 0, hr: 0, hrMax: 0, spo2Min: 0, lowSpo2Run: 0, highHrRun: 0 };
      getDay().sessions++;
      $("sesWarn").hidden = true;
      saveAstro();
    }
    function stopSession() { ses.running = false; saveAstro(); }

    function computeBone() {
      const s = astroSettings();
      const today = new Date();
      const keys = Object.keys(astro.days).sort();
      const first = keys.length ? keys[0] : null;
      const hasBase = s.bmd > 0 && s.muscle > 0 && !!s.mission;
      const dayAdh = (k) => { const d = astro.days[k]; return d ? clamp(d.zoneSec / 60 / s.target, 0, 1) : 0; };
      let adh7 = null;
      if (first) {
        const vals = [];
        for (let i = 6; i >= 0; i--) {
          const dt = new Date(today.getFullYear(), today.getMonth(), today.getDate() - i);
          if (dayKey(dt) >= first) vals.push(dayAdh(dayKey(dt)));
        }
        if (vals.length) adh7 = mean(vals);
      }
      let missionDay = 0, elapsed = 0, adhAll = 0, boneLoss = 0, muscleLoss = 0;
      if (s.mission) {
        missionDay = daysBetween(s.mission, today) + 1;
        elapsed = Math.max(0, missionDay - 1);
        if (first) {
          const from = first > s.mission ? first : s.mission;
          const n = daysBetween(from, today) + 1;
          if (n > 0) {
            let sum = 0;
            for (let i = 0; i < n; i++) {
              const dt = new Date(parseDay(from).getFullYear(), parseDay(from).getMonth(), parseDay(from).getDate() + i);
              sum += dayAdh(dayKey(dt));
            }
            adhAll = sum / n;
          }
        }
        boneLoss = 1.2 * (elapsed / 30) * (1 - 0.8 * adhAll);
        muscleLoss = Math.min(40, 1.5 * (elapsed / 7) * (1 - 0.8 * adhAll));
      }
      let risk = "low";
      if (boneLoss >= 3 || muscleLoss >= 10 || (adh7 !== null && adh7 < 0.4 && elapsed >= 7)) risk = "high";
      else if (boneLoss >= 1.5 || muscleLoss >= 5 || (adh7 !== null && adh7 < 0.7)) risk = "moderate";
      const since = astro.lastCheckup ? daysBetween(astro.lastCheckup, today) : null;
      const checkupDue = hasBase && (since === null ? elapsed >= CHECKUP_DUE_DAYS : (since >= CHECKUP_DUE_DAYS || (risk === "high" && since >= 7)));
      return { s: s, hasBase: hasBase, adh7: adh7, missionDay: missionDay, boneLoss: boneLoss, muscleLoss: muscleLoss, risk: risk, since: since, checkupDue: checkupDue, dayAdh: dayAdh };
    }

    function boneRecs(m) {
      const r = [];
      if (!m.hasBase) r.push("Enter baseline bone density, muscle mass, mission start and exercise target (Astronaut Record &rarr; Edit).");
      if (m.adh7 !== null && m.adh7 < 0.7) r.push("Exercise adherence is " + Math.round(m.adh7 * 100) + "% over 7 days (goal &ge; 70%). Schedule the missed resistive/aerobic sessions.");
      if (m.checkupDue) r.push("Periodic bone/muscle checkup is due" + (m.since !== null ? " (" + m.since + " days since last)" : "") + " &mdash; confirm actual condition with the crew surgeon.");
      if (m.risk === "high") r.push("Risk is HIGH: increase resistive exercise time and notify ground team.");
      if (!r.length) r.push("On track. Keep following the assigned exercise schedule.");
      return r;
    }

    function renderBone() {
      const m = computeBone();
      const s = m.s;
      const d = getDay();
      $("kMissionDay").textContent = m.missionDay > 0 ? m.missionDay : "--";
      $("kExToday").textContent = Math.round(d.zoneSec / 60) + " / " + s.target;
      $("kAdh7").textContent = m.adh7 === null ? "--" : Math.round(m.adh7 * 100) + "%";
      $("kCheckup").textContent = m.since === null ? "never" : m.since;
      $("sesState").textContent = ses.running ? "Running" : "Idle";
      $("sesElapsed").textContent = pad2(Math.floor(ses.sec / 60)) + ":" + pad2(ses.sec % 60);
      $("sesHr").textContent = (ses.hr > 0 ? ses.hr : "--") + " / " + (ses.hrMax > 0 ? ses.hrMax : "--");
      $("sesZone").textContent = ses.hr > 0 ? (ses.hr >= 0.5 * s.maxHr ? "In zone" : "Below zone") + " (max HR " + Math.round(s.maxHr) + ")" : "--";
      $("sesSpo2").textContent = ses.spo2Min > 0 ? ses.spo2Min + "%" : "--";
      $("sesMeter").style.width = clamp(d.zoneSec / 60 / s.target * 100, 0, 100) + "%";
      $("sesTarget").textContent = "Today: " + Math.round(d.zoneSec / 60) + " effective min of " + s.target + " min target";
      if (m.hasBase) {
        $("estBone").textContent = (s.bmd * (1 - m.boneLoss / 100)).toFixed(3) + " g/cm² (baseline " + s.bmd + ")";
        $("estBoneLoss").textContent = m.boneLoss.toFixed(2) + "%";
        $("estMuscle").textContent = (s.muscle * (1 - m.muscleLoss / 100)).toFixed(1) + " kg (baseline " + s.muscle + ")";
        $("estMuscleLoss").textContent = m.muscleLoss.toFixed(2) + "%";
        setHeroBadge($("boneRiskBadge"), m.risk.toUpperCase() + " RISK", m.risk === "high" ? "bad" : m.risk === "moderate" ? "watch" : "good");
      } else {
        ["estBone", "estBoneLoss", "estMuscle", "estMuscleLoss"].forEach((id) => { $(id).textContent = "--"; });
        setHeroBadge($("boneRiskBadge"), "NO BASELINE", "watch");
      }
      const today = new Date();
      let bars = "";
      for (let i = 6; i >= 0; i--) {
        const dt = new Date(today.getFullYear(), today.getMonth(), today.getDate() - i);
        const k = dayKey(dt);
        const has = !!astro.days[k];
        const a = m.dayAdh(k);
        const col = !has ? "#cbd5e1" : a >= 0.7 ? "#16a34a" : a >= 0.4 ? "#f59e0b" : "#ef4444";
        bars += '<div class="col" title="' + Math.round(a * 100) + '%"><i style="height:' + Math.max(3, a * 100) + "%;background:" + col + '"></i><span>' + dt.toLocaleDateString([], { weekday: "short" }) + "</span></div>";
      }
      $("bars7").innerHTML = bars;
      $("boneRecs").innerHTML = boneRecs(m).map((x) => "<li>" + x + "</li>").join("");
    }

    // ---------- Problem 2: stress, calibration, voice, check-ins, support chat ----------
    let physioWin = [];
    let calib = { running: false, startMs: 0, hr: [], hrv: [] };
    let stressNow = null, highSec = 0, lastIntervention = 0, persistStart = 0, voiceFlagUntil = 0;
    let lowSpo2Run = 0;

    function stressFrom(hr, hrv) {
      const b = astro.baseline;
      const hrPart = clamp(((hr - b.hr) / b.hr) / 0.3, 0, 1);
      if (b.hrv > 0 && hrv > 0) {
        const hrvPart = clamp(((b.hrv - hrv) / b.hrv) / 0.5, 0, 1);
        return 100 * (0.5 * hrPart + 0.5 * hrvPart);
      }
      return 100 * hrPart;
    }

    function chatAdd(who, text) {
      const box = $("chatBox");
      const div = document.createElement("div");
      div.className = "chat-msg " + who;
      div.textContent = text;
      box.appendChild(div);
      while (box.children.length > 40) box.removeChild(box.firstChild);
      box.scrollTop = box.scrollHeight;
    }
    function chatReplies(opts) {
      const row = $("chatReplies");
      row.innerHTML = "";
      opts.forEach((o) => {
        const b = document.createElement("button");
        b.type = "button"; b.className = "btn btn-secondary"; b.textContent = o.label;
        b.addEventListener("click", () => { chatAdd("me", o.label); o.fn(); });
        row.appendChild(b);
      });
    }
    const FEEL_TIPS = {
      Stressed: "Try slow breathing: inhale 4 seconds, hold 2, exhale 6, for 2 minutes. Then step away from the task for a short break.",
      Tired: "Rest matters. If your schedule allows, take a short break, dim the lights, and keep a consistent sleep time tonight.",
      Lonely: "Feeling distant from home is common on long missions. A call or message to family or friends can help; I can flag that you would like contact.",
      Fine: "Good to hear. Keep up your routine, exercise and sleep."
    };
    function chatFeeling(f) {
      chatAdd("ai", FEEL_TIPS[f]);
      if (f === "Fine") { chatReplies([]); return; }
      chatAdd("ai", "Did that help?");
      chatReplies([
        { label: "Feeling better", fn: () => { chatAdd("ai", "Glad to hear it. I will keep monitoring."); persistStart = 0; chatReplies([]); } },
        { label: "Not really", fn: () => {
            chatAdd("ai", "Thank you for telling me. I will flag this for the ground team at the next communication session. If you feel unsafe or in crisis, contact the flight surgeon immediately.");
            queueAlert("warn", "Astronaut reports ongoing '" + f.toLowerCase() + "' after self-support steps.", "selfreport-" + f);
            chatReplies([{ label: "Start over", fn: chatStart }]);
          } }
      ]);
    }
    function chatStart(prefix) {
      chatAdd("ai", (typeof prefix === "string" && prefix ? prefix + " " : "") + "How are you feeling right now?");
      chatReplies(["Stressed", "Tired", "Lonely", "Fine"].map((f) => ({ label: f, fn: () => chatFeeling(f) })));
    }
    function intervene(reason) {
      lastIntervention = Date.now();
      persistStart = lastIntervention;
      chatStart(reason);
      queueAlert("info", "Support conversation started: " + reason, "intervene");
    }

    function startCalibration() {
      if (calib.running) return;
      calib = { running: true, startMs: Date.now(), hr: [], hrv: [] };
    }
    function stepCalibration(valid, bpm, hrv) {
      const btn = $("btnCalibrate");
      if (!calib.running) return;
      if (valid) { calib.hr.push(bpm); if (hrv > 0) calib.hrv.push(hrv); }
      const pct = clamp((Date.now() - calib.startMs) / CALIB_MS * 100, 0, 100);
      $("calMeter").style.width = pct + "%";
      btn.textContent = "Calibrating " + Math.round(pct) + "%";
      if (pct >= 100) {
        calib.running = false;
        if (calib.hr.length >= 30) {
          astro.baseline = { hr: mean(calib.hr), hrv: calib.hrv.length >= 10 ? mean(calib.hrv) : 0, ts: Date.now() };
          saveAstro();
          btn.textContent = "Recalibrate baseline";
        } else {
          btn.textContent = "No stable signal - retry calibration";
          $("calMeter").style.width = "0%";
        }
      }
    }

    function stressTick(valid, bpm, hrv) {
      stepCalibration(valid, bpm, hrv);
      if (!astro.baseline) { stressNow = null; return; }
      if (ses.running || !valid) { highSec = 0; return; }
      physioWin.push({ hr: bpm, hrv: hrv });
      if (physioWin.length > 60) physioWin.shift();
      if (physioWin.length < 20) return;
      const hr = mean(physioWin.map((x) => x.hr));
      const hv = physioWin.filter((x) => x.hrv > 0).map((x) => x.hrv);
      let v = stressFrom(hr, hv.length ? mean(hv) : -1);
      if (Date.now() < voiceFlagUntil) v += 15;
      stressNow = Math.round(clamp(v, 0, 100));
      const d = getDay();
      d.stressSum += stressNow; d.stressN++; d.stressMax = Math.max(d.stressMax, stressNow);
      if (stressNow >= STRESS_HIGH) { highSec++; d.highSec++; } else { highSec = 0; }
      if (highSec >= 120 && Date.now() - lastIntervention > QUEUE_DEDUPE_MS) {
        intervene("Your heart rate and HRV suggest sustained tension.");
      }
      if (persistStart > 0) {
        if (stressNow < 45) persistStart = 0;
        else if (Date.now() - persistStart >= PERSIST_MS) {
          queueAlert("bad", "Stress indicators persisted over 10 minutes after support. Ground specialists should contact the astronaut and assess.", "persist");
          persistStart = 0;
        }
      }
    }

    function renderMind() {
      const b = astro.baseline;
      $("kStress").textContent = stressNow === null ? "--" : stressNow;
      $("kHrv").textContent = lastVitals.hrv > 0 ? lastVitals.hrv : "--";
      $("kBaseHr").textContent = b ? Math.round(b.hr) + " / " + (b.hrv > 0 ? Math.round(b.hrv) : "--") : "--";
      const sv = astro.lastSurvey;
      $("kMood").textContent = sv ? sv.mood + "/5" : "--";
      if (!b) setHeroBadge($("stressBadge"), "NO BASELINE", "watch");
      else if (stressNow === null) setHeroBadge($("stressBadge"), "MEASURING", "watch");
      else if (stressNow >= STRESS_HIGH) setHeroBadge($("stressBadge"), "HIGH STRESS", "bad");
      else if (stressNow >= 35) setHeroBadge($("stressBadge"), "MODERATE", "watch");
      else setHeroBadge($("stressBadge"), "CALM", "good");
      if (!calib.running) $("btnCalibrate").textContent = b ? "Recalibrate baseline" : "Calibrate baseline";
    }

    function submitSurvey() {
      const v = (id) => parseInt($(id).value, 10);
      const r = { ts: Date.now(), mood: v("q1"), sleep: v("q2"), stress: v("q3"), iso: v("q4"), work: v("q5") };
      r.score = Math.round(((5 - r.mood) + (5 - r.sleep) + (r.stress - 1) + (r.iso - 1) + (r.work - 1)) / 20 * 100);
      getDay().surveys.push(r);
      astro.lastSurvey = r;
      saveAstro();
      let msg = "Check-in saved. Wellbeing concern score: " + r.score + "/100.";
      if (r.score >= 75) {
        msg += " High concern: flagged for ground team.";
        queueAlert("bad", "Check-in shows high concern (score " + r.score + "/100, mood " + r.mood + "/5, sleep " + r.sleep + "/5).", "survey");
        intervene("Your check-in suggests you are having a hard time.");
      } else if (r.score >= 55 || r.mood <= 2) {
        msg += " Moderate concern: flagged for ground team.";
        queueAlert("warn", "Check-in shows moderate concern (score " + r.score + "/100, mood " + r.mood + "/5, sleep " + r.sleep + "/5).", "survey");
        intervene("Your check-in suggests some strain.");
      }
      $("surveyMsg").textContent = msg;
      renderMind();
    }

    // Voice: pitch (autocorrelation) + energy, compared to the astronaut's own first recording
    function detectPitch(buf, sr) {
      const n = buf.length, minLag = Math.floor(sr / 400), maxLag = Math.min(Math.floor(sr / 70), n - 1);
      const span = n - maxLag;
      if (span < 256) return 0;
      let r0 = 0;
      for (let i = 0; i < span; i++) r0 += buf[i] * buf[i];
      if (r0 <= 0) return 0;
      let best = 0, bestLag = 0;
      for (let lag = minLag; lag <= maxLag; lag++) {
        let c = 0;
        for (let i = 0; i < span; i++) c += buf[i] * buf[i + lag];
        if (c > best) { best = c; bestLag = lag; }
      }
      return best / r0 > 0.5 ? sr / bestLag : 0;
    }
    async function voiceCheck() {
      const msg = $("voiceMsg"), btn = $("btnVoice");
      if (!(navigator.mediaDevices && navigator.mediaDevices.getUserMedia)) {
        msg.textContent = "Microphone is not available here: browsers only allow it on HTTPS or localhost. Use the questionnaire instead, or open the dashboard from a secure origin.";
        return;
      }
      let stream, actx;
      try {
        stream = await navigator.mediaDevices.getUserMedia({ audio: true });
        actx = new (window.AudioContext || window.webkitAudioContext)();
      } catch (e) {
        msg.textContent = "Microphone access was denied or unavailable.";
        return;
      }
      btn.disabled = true;
      msg.textContent = "Recording 8 s - speak normally (e.g. describe your day)...";
      const an = actx.createAnalyser();
      an.fftSize = 2048;
      actx.createMediaStreamSource(stream).connect(an);
      const buf = new Float32Array(an.fftSize), pitches = [], energies = [];
      const t0 = Date.now();
      const timer = setInterval(() => {
        an.getFloatTimeDomainData(buf);
        let s = 0;
        for (let i = 0; i < buf.length; i++) s += buf[i] * buf[i];
        const rms = Math.sqrt(s / buf.length);
        if (rms > 0.015) {
          const p = detectPitch(buf, actx.sampleRate);
          if (p > 0) { pitches.push(p); energies.push(rms); }
        }
        if (Date.now() - t0 >= 8000) {
          clearInterval(timer);
          stream.getTracks().forEach((t) => t.stop());
          actx.close();
          btn.disabled = false;
          finishVoice(pitches, energies);
        }
      }, 100);
    }
    function finishVoice(pitches, energies) {
      const msg = $("voiceMsg");
      if (pitches.length < 15) { msg.textContent = "Not enough speech detected. Try again closer to the microphone."; return; }
      const sorted = pitches.slice().sort((a, b) => a - b);
      const pm = sorted[Math.floor(sorted.length / 2)];
      const pAvg = mean(pitches);
      const ps = Math.sqrt(mean(pitches.map((x) => (x - pAvg) * (x - pAvg))));
      const em = mean(energies);
      const cur = { pitch: pm, std: ps, energy: em };
      if (!astro.voiceBase) {
        astro.voiceBase = cur; saveAstro();
        msg.textContent = "Voice baseline saved (pitch " + Math.round(pm) + " Hz). Future checks compare against it.";
        return;
      }
      const vb = astro.voiceBase;
      const dp = (pm - vb.pitch) / vb.pitch;
      let score = 0;
      if (dp > 0.15) score++;
      if (vb.std > 0 && ps / vb.std < 0.6) score++;
      if (em / vb.energy < 0.6) score++;
      const flag = score >= 2;
      getDay().voice.push({ ts: Date.now(), dp: dp, flag: flag });
      if (flag) {
        voiceFlagUntil = Date.now() + QUEUE_DEDUPE_MS;
        msg.textContent = "Voice differs from your baseline (pitch " + (dp * 100).toFixed(0) + "%, flatter/quieter). Flagged.";
        queueAlert("info", "Voice tone changed vs baseline (pitch " + (dp * 100).toFixed(0) + "%, reduced variation/energy).", "voice");
        intervene("Your voice tone differs from your usual.");
      } else {
        msg.textContent = "Voice within your normal range (pitch " + (dp * 100).toFixed(0) + "% vs baseline).";
      }
      saveAstro();
    }

    // ---------- Daily report ----------
    function buildReport(key) {
      const d = astro.days[key];
      const s = astroSettings();
      const m = computeBone();
      const L = [];
      const avg = (sum, n, dec) => (n > 0 ? (sum / n).toFixed(dec) : "n/a");
      L.push("ASTRONAUT DAILY HEALTH REPORT - " + key);
      L.push("Astronaut: " + (s.p.name || "N/A") + " (ID " + (s.p.patientId || "N/A") + ")" + (m.missionDay > 0 ? " | Mission day " + m.missionDay : ""));
      L.push("");
      if (!d) { L.push("No data recorded for this day."); return L.join("\n"); }
      const effMin = Math.round(d.zoneSec / 60);
      const adh = Math.round(clamp(d.zoneSec / 60 / s.target, 0, 1) * 100);
      L.push("== PHYSICAL ACTIVITY & EXERCISE ==");
      L.push("Sessions: " + d.sessions + " | Session time: " + Math.round(d.sesSec / 60) + " min");
      L.push("Effective training (>=50% max HR): " + effMin + " min of " + s.target + " min target (" + adh + "% adherence)");
      L.push("Peak heart rate: " + (d.hrMax > 0 ? d.hrMax + " BPM" : "n/a") + " | Lowest SpO2 in session: " + (d.spo2Min > 0 ? d.spo2Min + "%" : "n/a"));
      L.push("");
      L.push("== VITAL SIGNS (daily averages) ==");
      L.push("Heart rate: " + avg(d.hrSum, d.hrN, 0) + " BPM | HRV (RMSSD): " + avg(d.hrvSum, d.hrvN, 0) + " ms");
      L.push("SpO2: " + avg(d.spo2Sum, d.spo2N, 1) + "% | Body temperature: " + avg(d.tSum, d.tN, 1) + " C");
      L.push("");
      if (key === dayKey()) {
        L.push("== BONE & MUSCLE (current estimate) ==");
        if (m.hasBase) {
          L.push("Estimated bone loss: " + m.boneLoss.toFixed(2) + "% | muscle loss: " + m.muscleLoss.toFixed(2) + "% | risk: " + m.risk.toUpperCase());
        } else L.push("No baseline entered.");
        L.push("7-day adherence: " + (m.adh7 === null ? "n/a" : Math.round(m.adh7 * 100) + "%") + " | Days since checkup: " + (m.since === null ? "never" : m.since));
        L.push("");
      }
      L.push("== PSYCHOLOGICAL STATE ==");
      L.push("Stress index: avg " + avg(d.stressSum, d.stressN, 0) + ", max " + d.stressMax + " | Time at high stress: " + Math.round(d.highSec / 60) + " min");
      if (d.surveys.length) d.surveys.forEach((r) => L.push("Check-in " + new Date(r.ts).toLocaleTimeString([], { hour: "2-digit", minute: "2-digit" }) + ": mood " + r.mood + "/5, sleep " + r.sleep + "/5, concern score " + r.score + "/100"));
      else L.push("No check-in submitted.");
      if (d.voice.length) L.push("Voice checks: " + d.voice.length + " (" + d.voice.filter((v) => v.flag).length + " flagged)");
      L.push("");
      L.push("== ITEMS REQUIRING ATTENTION ==");
      const att = [];
      if (adh < 70) att.push("Exercise adherence below 70% (" + adh + "%).");
      if (d.spo2Min > 0 && d.spo2Min < 90) att.push("SpO2 dropped to " + d.spo2Min + "% during exercise.");
      if (d.stressMax >= STRESS_HIGH) att.push("High stress detected (max index " + d.stressMax + ").");
      d.surveys.forEach((r) => { if (r.score >= 55 || r.mood <= 2) att.push("Check-in indicates concern (score " + r.score + ")."); });
      if (d.voice.some((v) => v.flag)) att.push("Voice tone changed vs baseline.");
      if (key === dayKey() && m.checkupDue) att.push("Bone/muscle checkup is due.");
      astro.queue.filter((q) => dayKey(new Date(q.ts)) === key && q.level !== "info").forEach((q) => att.push("Queued alert: " + q.text));
      if (!att.length) att.push("None.");
      att.forEach((x) => L.push("- " + x));
      return L.join("\n");
    }
    function refreshReportList() {
      const sel = $("reportDate");
      const keep = sel.value;
      const keys = Object.keys(astro.days);
      if (keys.indexOf(dayKey()) < 0) keys.push(dayKey());
      keys.sort().reverse();
      sel.innerHTML = keys.map((k) => '<option value="' + k + '">' + k + "</option>").join("");
      sel.value = keys.indexOf(keep) >= 0 ? keep : keys[0];
    }
    function renderReport() { $("reportBody").textContent = buildReport($("reportDate").value || dayKey()); }
    function downloadReport() {
      const key = $("reportDate").value || dayKey();
      const blob = new Blob([buildReport(key)], { type: "text/plain;charset=utf-8" });
      const url = URL.createObjectURL(blob);
      const a = document.createElement("a");
      a.href = url; a.download = "Astronaut_Report_" + key + ".txt";
      document.body.appendChild(a); a.click(); document.body.removeChild(a);
      URL.revokeObjectURL(url);
    }

    // ---------- 1 Hz tick ----------
    let tickCount = 0;
    function astroTick() {
      tickCount++;
      const bpm = displayedBpm > 0 ? displayedBpm : latestBpm;
      const valid = connOnline && !leadsOffState && bpm > 0;
      const hrv = lastVitals.hrv;
      const spo2ok = connOnline && lastVitals.finger && lastVitals.spo2Valid && lastVitals.spo2 > 0;
      const s = astroSettings();
      const d = getDay();
      if (valid) {
        d.hrSum += bpm; d.hrN++;
        if (hrv > 0) { d.hrvSum += hrv; d.hrvN++; }
      }
      if (connOnline && lastVitals.bodyT > 0) { d.tSum += lastVitals.bodyT; d.tN++; }
      if (spo2ok) { d.spo2Sum += lastVitals.spo2; d.spo2N++; }

      if (ses.running) {
        ses.sec++; d.sesSec++;
        if (valid) {
          ses.hr = bpm; ses.hrMax = Math.max(ses.hrMax, bpm); d.hrMax = Math.max(d.hrMax, bpm);
          if (bpm >= 0.5 * s.maxHr) d.zoneSec++;
          ses.highHrRun = bpm > 0.95 * s.maxHr ? ses.highHrRun + 1 : 0;
        }
        if (spo2ok) {
          const sp = lastVitals.spo2;
          ses.spo2Min = ses.spo2Min ? Math.min(ses.spo2Min, sp) : sp;
          d.spo2Min = d.spo2Min ? Math.min(d.spo2Min, sp) : sp;
          ses.lowSpo2Run = sp < 90 ? ses.lowSpo2Run + 1 : 0;
        }
        const w = $("sesWarn");
        if (ses.lowSpo2Run >= 5) {
          w.hidden = false; w.textContent = "SpO2 below 90% - stop and rest.";
          queueAlert("bad", "SpO2 below 90% during exercise (" + lastVitals.spo2 + "%).", "ex-spo2");
        } else if (ses.highHrRun >= 10) {
          w.hidden = false; w.textContent = "Heart rate above 95% of max - reduce intensity.";
          queueAlert("warn", "Heart rate above 95% of max during exercise (" + bpm + " BPM).", "ex-hr");
        } else w.hidden = true;
      }

      stressTick(valid, bpm, hrv);

      if (tickCount % 60 === 0) {
        const m = computeBone();
        if (m.checkupDue) queueAlert("warn", "Periodic bone/muscle checkup is due" + (m.since !== null ? " (" + m.since + " days since last)." : "."), "checkup");
        if (m.hasBase && m.adh7 !== null && m.adh7 < 0.5 && m.missionDay > 7) queueAlert("warn", "Exercise adherence is " + Math.round(m.adh7 * 100) + "% over 7 days.", "adherence");
        if (m.risk === "high") queueAlert("bad", "Bone/muscle loss risk is HIGH (bone " + m.boneLoss.toFixed(1) + "%, muscle " + m.muscleLoss.toFixed(1) + "%).", "boneRisk");
      }
      if (tickCount % 10 === 0) saveAstro();

      if ($("page-bone").classList.contains("active")) renderBone();
      renderMind();
    }

    // ---------- AI layer (Claude via the PC proxy ai_server.js) ----------
    let aiUrl = "";
    try { aiUrl = localStorage.getItem("aiUrl") || ""; } catch (e) {}
    if (!aiUrl) aiUrl = "http://10.143.110.204:3000";
    let aiOnline = false;
    const aiHistory = [];
    async function aiPost(path, body) {
      const r = await fetch(aiUrl.replace(/\/$/, "") + path, {
        method: "POST", headers: { "Content-Type": "application/json" }, body: JSON.stringify(body)
      });
      const j = await r.json();
      if (!r.ok) throw new Error(j.error || ("HTTP " + r.status));
      return j;
    }
    async function aiHealth() {
      try {
        const r = await fetch(aiUrl.replace(/\/$/, "") + "/ai/health", { cache: "no-store" });
        const j = await r.json();
        aiOnline = !!j.ok;
        $("aiStatus").textContent = aiOnline ? "AI online (" + j.model + ")" : "AI server up but API key missing";
      } catch (e) {
        aiOnline = false;
        $("aiStatus").textContent = "AI offline - using built-in rules";
      }
      $("aiDot").style.color = aiOnline ? "#16a34a" : "#ef4444";
    }
    function aiContext() {
      const d = getDay(), m = computeBone(), sv = astro.lastSurvey, b = astro.baseline;
      return {
        stressIndex: stressNow, stressHighThreshold: STRESS_HIGH,
        baselineHrHrv: b ? { hr: Math.round(b.hr), hrv: Math.round(b.hrv) } : null,
        hrvNow: lastVitals.hrv > 0 ? lastVitals.hrv : null,
        spo2: lastVitals.spo2Valid ? lastVitals.spo2 : null,
        bodyTempC: lastVitals.bodyT > 0 ? lastVitals.bodyT : null,
        lastCheckin: sv ? { mood: sv.mood, sleep: sv.sleep, stress: sv.stress, isolation: sv.iso, workload: sv.work, concernScore: sv.score } : null,
        voiceFlagsToday: d.voice.filter((v) => v.flag).length,
        minutesHighStressToday: Math.round(d.highSec / 60),
        boneMuscleRisk: m.hasBase ? m.risk : null, missionDay: m.missionDay
      };
    }
    async function chatSend() {
      const inp = $("chatInput");
      const text = inp.value.trim();
      if (!text) return;
      inp.value = "";
      chatAdd("me", text);
      chatReplies([]);
      if (!aiOnline) {
        chatAdd("ai", "AI server is offline. I can still help with the quick options below.");
        chatStart("");
        return;
      }
      chatAdd("ai", "...");
      const box = $("chatBox"), pending = box.lastChild;
      try {
        const j = await aiPost("/ai/chat", { message: text, context: aiContext(), history: aiHistory });
        pending.textContent = j.reply;
        aiHistory.push({ role: "user", text: text }, { role: "assistant", text: j.reply });
        if (aiHistory.length > 20) aiHistory.splice(0, 2);
        if (j.concern === "high") {
          queueAlert("bad", "AI support chat: HIGH concern. " + (j.note || "Ground specialists should contact the astronaut."), "ai-high");
          persistStart = 0;
        } else if (j.concern === "moderate") {
          queueAlert("warn", "AI support chat: moderate concern. " + (j.note || ""), "ai-mod");
        }
      } catch (e) {
        pending.textContent = "Could not reach the AI (" + e.message + "). Using built-in support instead.";
        chatStart("");
      }
    }
    async function aiReport() {
      const out = $("aiReportBody"), btn = $("btnAiReport");
      out.hidden = false;
      if (!aiOnline) { out.textContent = "AI server offline. Start ai_server.js on the PC and set its address in the Mental Health page."; return; }
      out.textContent = "Generating summary...";
      btn.disabled = true;
      try {
        const j = await aiPost("/ai/report", { report: buildReport($("reportDate").value || dayKey()), lang: $("aiLang").value });
        out.textContent = "AI SUMMARY (for ground team)\n\n" + j.summary;
      } catch (e) { out.textContent = "AI error: " + e.message; }
      btn.disabled = false;
    }

    function initAstro() {
      $("aiUrl").value = aiUrl;
      $("aiUrl").addEventListener("change", () => {
        aiUrl = $("aiUrl").value.trim();
        try { localStorage.setItem("aiUrl", aiUrl); } catch (e) {}
        aiHealth();
      });
      $("btnChatSend").addEventListener("click", chatSend);
      $("chatInput").addEventListener("keydown", (e) => { if (e.key === "Enter") chatSend(); });
      $("btnAiReport").addEventListener("click", aiReport);
      aiHealth(); setInterval(aiHealth, 30000);
      $("btnSesStart").addEventListener("click", () => { startSession(); renderBone(); });
      $("btnSesStop").addEventListener("click", () => { stopSession(); renderBone(); });
      $("btnCheckup").addEventListener("click", () => { astro.lastCheckup = dayKey(); saveAstro(); renderBone(); });
      $("btnCalibrate").addEventListener("click", () => { if (!connOnline || leadsOffState) { $("btnCalibrate").textContent = "Attach ECG leads first"; return; } startCalibration(); });
      $("btnVoice").addEventListener("click", voiceCheck);
      $("btnSurvey").addEventListener("click", submitSurvey);
      $("btnComm").addEventListener("click", () => {
        const now = Date.now();
        astro.queue.forEach((q) => { if (!q.sent) { q.sent = true; q.sentAt = now; } });
        saveAstro(); renderQueue();
      });
      $("reportDate").addEventListener("change", renderReport);
      $("btnReportDownload").addEventListener("click", downloadReport);
      $("reportNote").textContent = "Reports are built from each day's stored data.";
      document.querySelectorAll(".nav-item").forEach((b) => b.addEventListener("click", () => {
        if (b.dataset.page === "bone") renderBone();
        if (b.dataset.page === "mind") renderMind();
        if (b.dataset.page === "report") { refreshReportList(); renderReport(); }
      }));
      chatStart("Hello, I am your support assistant.");
      renderQueue(); renderBone(); renderMind();
      setInterval(astroTick, 1000);
    }
    initAstro();

    setInterval(() => { ui.clock.textContent = fmtTime(); }, 1000);
    setInterval(pollEcg, ECG_POLL_MS);
    setInterval(pollVitals, 1500);
    pollEcg();
    pollVitals();
  </script>
</body>
</html>
)rawliteral";
 
#endif