const sourceEl = document.getElementById('source');
const stdinEl = document.getElementById('stdin');
const outputEl = document.getElementById('output');
const statusEl = document.getElementById('status');
const runBtn = document.getElementById('run');
const stopBtn = document.getElementById('stop');

const DEFAULT_SOURCE = `++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.`;
sourceEl.value = DEFAULT_SOURCE;

let worker = null;

function setRunning(running) {
  runBtn.disabled = running;
  stopBtn.disabled = !running;
  statusEl.textContent = running ? 'running…' : '';
}

function run() {
  if (worker) worker.terminate();
  outputEl.textContent = '';
  outputEl.classList.remove('error');
  setRunning(true);

  worker = new Worker('worker.js');

  worker.onmessage = (ev) => {
    const msg = ev.data;
    if (msg.type === 'output') {
      outputEl.textContent += msg.text;
    } else if (msg.type === 'stderr') {
      outputEl.classList.add('error');
      outputEl.textContent += msg.text;
    } else if (msg.type === 'done') {
      statusEl.textContent = `exited (code ${msg.exitCode})`;
      setRunning(false);
      worker.terminate();
      worker = null;
    } else if (msg.type === 'error') {
      outputEl.classList.add('error');
      outputEl.textContent += `\n[error] ${msg.message}`;
      statusEl.textContent = 'error';
      setRunning(false);
      worker.terminate();
      worker = null;
    }
  };

  worker.onerror = (ev) => {
    outputEl.classList.add('error');
    outputEl.textContent += `\n[worker error] ${ev.message}`;
    statusEl.textContent = 'error';
    setRunning(false);
    worker = null;
  };

  worker.postMessage({ source: sourceEl.value, stdin: stdinEl.value });
}

function stop() {
  if (worker) {
    worker.terminate();
    worker = null;
  }
  statusEl.textContent = 'stopped';
  setRunning(false);
}

runBtn.addEventListener('click', run);
stopBtn.addEventListener('click', stop);
