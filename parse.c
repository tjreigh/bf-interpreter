#include "parse.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int parse(char filename[], OPCODE **opcodes) {
  int capacity = 100;
  int opCount = 0;

  *opcodes = malloc(capacity * sizeof(OPCODE));
  if (opcodes == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return -1;
  }

  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("Error opening file with name %s\n", filename);
    exit(1);
  }

  char inChar;
  while ((inChar = fgetc(fp)) != EOF) {
    OPCODE opcode = getOpcode(inChar);

    if (opcode != NONE) {
      // check if we need to grow the opcodes string
      if (opCount >= capacity) {
        capacity *= 2;
        void *temp = realloc(*opcodes, capacity * sizeof(OPCODE));
        if (temp == NULL) {
          fprintf(stderr, "Memory allocation failed\n");
          free(opcodes);
          return -1;
        }
        *opcodes = temp;        
      }

      (*opcodes)[opCount] = opcode;
      opCount++;
    }
  }

  // clean up any wasted memory
  void *temp = realloc(*opcodes, opCount * sizeof(OPCODE));
  if (temp == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    free(opcodes);
    return -1;
  }
  *opcodes = temp; 

  fclose(fp);
  return opCount;
}

OPCODE getOpcode(char inChar) {
  OPCODE opcode = NONE;
  //printf("%c", inChar);

  switch (inChar)
  {
  case '>':
    opcode = RIGHT;
    break;
  case '<':
    opcode = LEFT;
    break;
  case '+':
    opcode = INC;
    break;
  case '-':
    opcode = DEC;
    break;
  case '.':
    opcode = OUTPUT;
    break;
  case ',':
    opcode = INPUT;
    break;
  case '[':
    opcode = LOOP_START;
    break;
  case ']':
    opcode = END;
    break;
  default:
    opcode = NONE;
  }

  // if (opcode == NONE)
   // printf("-1");
  return opcode;
}