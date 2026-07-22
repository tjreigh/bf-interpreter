# bf-interpreter
world's most sophisticated program for the world's most sophisticated programming language. just trust me.

you can also run it in your browser, no install needed: **[bf.tjreigh.mobi](https://bf.tjreigh.mobi)**. it's the same interpreter compiled to WebAssembly, web interface source is in [`web/`](web).

see the [esolangs wiki page](https://esolangs.org/wiki/Brainfuck) for more info on the language.

## Usage

1. Build the program
```
make
```

2. Run it with a filename for a bf program
```
./main.e <program.bf>
./main.e examples/hello.bf
```

3. profit

## Why WASM?

the web version runs entirely on your machine, in the browser. i don't have a server running anyone's bf code, so i don't have to worry about sandboxing it, rate limiting it, or any of that. the browser already handles keeping wasm contained, so i get that for free.

if you want to build it yourself, install [emscripten](https://emscripten.org/docs/getting_started/downloads.html) and run:
```
web/build.sh
```
that compiles `main.c` and `parse.c` into `web/bf.js` and `web/bf.wasm`. then serve the `web/` folder with whatever's lying around, e.g.:
```
cd web && python3 -m http.server
```
and open `localhost:8000` in a browser.