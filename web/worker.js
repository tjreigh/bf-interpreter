importScripts('bf.js');

function runProgram(source, stdinText) {
  const stdinBytes = new TextEncoder().encode(stdinText || '');
  let stdinPos = 0;
  let outBuf = [];

  function flushOut() {
    if (outBuf.length > 0) {
      postMessage({ type: 'output', text: outBuf.join('') });
      outBuf = [];
    }
  }

  function stdinCb() {
    if (stdinPos < stdinBytes.length) return stdinBytes[stdinPos++];
    return null;
  }

  function stdoutCb(byte) {
    outBuf.push(String.fromCharCode(byte));
    if (outBuf.length >= 256) flushOut();
  }

  function stderrCb(byte) {
    postMessage({ type: 'stderr', text: String.fromCharCode(byte) });
  }

  BFModule({ noFSInit: true })
    .then((Module) => {
      Module.FS.writeFile('/program.bf', source);
      Module.FS.init(stdinCb, stdoutCb, stderrCb);
      try {
        const exitCode = Module.callMain(['/program.bf']);
        flushOut();
        postMessage({ type: 'done', exitCode });
      } catch (e) {
        flushOut();
        if (e && e.name === 'ExitStatus') {
          postMessage({ type: 'done', exitCode: e.status });
        } else {
          postMessage({ type: 'error', message: (e && e.message) || String(e) });
        }
      }
    })
    .catch((e) => {
      postMessage({ type: 'error', message: (e && e.message) || String(e) });
    });
}

self.onmessage = (ev) => {
  runProgram(ev.data.source, ev.data.stdin);
};
