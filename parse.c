#include "parse.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 99999

int parse(char filename[], OPCODE **opcodes)
{
  int opCount = 0;
  char line[MAX_LINE] = {};

  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("Error opening file with name %s\n", filename);
    exit(1);
  }

  while (fgets(line, sizeof(line), fp))
  {
    for (int i = 0; i < strlen(line); i++)
    {
      OPCODE opcode = getOpcode(line[i]);
      //printf("%d ", opcode);
      if (opcode != NONE)
        opCount++;
    }
  }

  fclose(fp);

  *opcodes = malloc(opCount * sizeof(OPCODE));

  int i = 0;
  fp = fopen(filename, "r");
  char inChar = fgetc(fp);
  while (inChar != EOF)
  {
    OPCODE opcode = getOpcode(inChar);
    if (opcode != NONE)
    {
      (*opcodes)[i] = opcode;
      i++;
      printf("%d", opcode);
    }
    inChar = fgetc(fp);
  }

  fclose(fp);

  return opCount;
}

OPCODE getOpcode(char inChar)
{
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