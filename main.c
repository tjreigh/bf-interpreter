#include "parse.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int buildJumpTable(OPCODE *opcodes, int opCount, int *jumpTable);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <filename.bf>\n", argv[0]);
    return 1;
  }

  OPCODE *opcodes;
  int opCount = 0;
  
  char memory[3000] = {0};
  char *ptr = memory;

  opCount = parse(argv[1], &opcodes);
  
  int *jumpTable = malloc(opCount * sizeof(int));
  if (buildJumpTable(opcodes, opCount, jumpTable) != 0) {
    free(opcodes);
    free(jumpTable);
    return 1;
  }

  int i;
  for (i = 0; i < opCount; i++)
  {
    switch (opcodes[i])
    {
    case RIGHT:
      ++ptr;
      break;
    case LEFT:
      --ptr;
      break;
    case INC:
      ++*ptr;
      break;
    case DEC:
      --*ptr;
      break;
    case OUTPUT:
      putchar(*ptr);
      break;
    case INPUT:
      *ptr = getchar();
      break;
    case LOOP_START:
      if (*ptr == 0) {
        i = jumpTable[i];
      }
      break;
    case END:
      if (*ptr != 0) {
        i = jumpTable[i];
      }
      break;
    case NONE:
      break;
    }
  }

  free(opcodes);
  free(jumpTable);

  return 0;
}

int buildJumpTable(OPCODE *opcodes, int opCount, int *jumpTable) {
  int *bracketStack = malloc(opCount * sizeof(int));
  int stackTop = 0;

  for (int i = 0; i < opCount; i++) {
    jumpTable[i] = -1;
  }

  for (int i = 0; i < opCount; i++) {
    if (opcodes[i] == LOOP_START) {
      bracketStack[stackTop] = i;
      stackTop++;
    } else if (opcodes[i] == END) {
      if (stackTop == 0) {
        fprintf(stderr, "Error: Unmatched closing bracket ']' at position %d\n", i);
        free(bracketStack);
        return 1;
      }
      
      stackTop--;
      int openIndex = bracketStack[stackTop];
      jumpTable[openIndex] = i;
      jumpTable[i] = openIndex;
    }
  }

  if (stackTop != 0) {
    fprintf(stderr, "Error: %d unmatched opening bracket(s) '['\n", stackTop);
    free(bracketStack);
    return 1;
  }

  free(bracketStack);
  return 0;
}