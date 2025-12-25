# bf-interpreter
except it's really only a transpiler (for now)

## Usage

1. Build the program
```
make
```

2. Run it with a filename for a bf program
```
./main.e [program.bf]
./main.e examples/hello.bf
```

3. Compile the output C code
```
gcc out.c
```

4. Run the output
```
./a.out
```

5. profit