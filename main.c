#include "parse.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  OPCODE *opcodes;
  int opCount = 0;
  char slice[100] = {};
  char output[30000] = {};

  char *filename = malloc(strlen(argv[1]) + 1);
  strcpy(filename, argv[1]);

  opCount = parse(filename, &opcodes);

  printf("\n%d \t %d \t %d\n", opcodes[0], opcodes[0] <= 1, opCount);

  strcat(output, "#include <stdio.h>\n\nint main() {\n\tchar memory[3000] = {0};\n\tchar *ptr = memory;\n");

  int depth = 1;

  int i;
  int j;
  for (i = 0; i < opCount; i++)
  {
    strcpy(slice, "");
    for (j = 0; j < depth; j++) {
      if (opcodes[i] == END && j == depth - 1)
        break;
      strcat(slice, "\t");
    }

    switch (opcodes[i])
    {
    case RIGHT:
      strcat(slice, "++ptr;\n");
      break;
    case LEFT:
      strcat(slice, "--ptr;\n");
      break;
    case INC:
      strcat(slice, "++*ptr;\n");
      break;
    case DEC:
      strcat(slice, "--*ptr;\n");
      break;
    case OUTPUT:
      strcat(slice, "putchar(*ptr);\n");
      break;
    case INPUT:
      strcat(slice, "*ptr = getchar();\n");
      break;
    case LOOP_START:
      depth++;
      strcat(slice, "while (*ptr) {\n");
      break;
    case END:
      depth--;
      strcat(slice, "}\n");
      break;
    }

    strcat(output, slice);
  }

  strcat(output, "return 0;\n}");

  FILE *outFile = fopen("out.c", "w+");

  for (int j = 0; j < strlen(output); j++)
  {
    fputc(output[j], outFile);
  }

  fclose(outFile);

  free(filename);
  free(opcodes);

  return 0;
}