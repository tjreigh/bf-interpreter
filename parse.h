#include <stdio.h>

typedef enum
{
  RIGHT = 1,
  LEFT,
  INC,
  DEC,
  OUTPUT,
  INPUT,
  LOOP_START,
  END,
  NONE = -1
} OPCODE;

int parse(char [], OPCODE **);
OPCODE getOpcode(char);