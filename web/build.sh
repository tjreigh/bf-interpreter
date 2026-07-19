#!/bin/sh
set -e
cd "$(dirname "$0")"

emcc ../main.c ../parse.c \
  -O2 \
  -s MODULARIZE=1 \
  -s EXPORT_NAME=BFModule \
  -s EXPORTED_RUNTIME_METHODS='["callMain","FS"]' \
  -s ENVIRONMENT=worker \
  -s ALLOW_MEMORY_GROWTH=1 \
  -s INVOKE_RUN=0 \
  -s EXIT_RUNTIME=1 \
  -o bf.js
