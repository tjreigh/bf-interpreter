#include "parse.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  OPCODE *opcodes;
  int opCount = 0;
  char output[30000] = {};

  char *filename = malloc(strlen(argv[1]));
  strcpy(filename, argv[1]);

  opCount = parse(filename, &opcodes);

  printf("\n%d \t %d \t %d\n", opcodes[0], opcodes[0] <= 1, opCount);

  strcat(output, "#include <stdio.h>\n\nint main() {\n\tchar memory[3000] = {0};\nchar *ptr = memory;\n");

  int i;
  for (i = 0; i < opCount; i++)
  {
    switch (opcodes[i])
    {
    case RIGHT:
      strcat(output, "++ptr;\n");
      break;
    case LEFT:
      strcat(output, "--ptr;\n");
      break;
    case INC:
      strcat(output, "++*ptr;\n");
      break;
    case DEC:
      strcat(output, "--*ptr;\n");
      break;
    case OUTPUT:
      strcat(output, "putchar(*ptr);\n");
      break;
    case INPUT:
      strcat(output, "*ptr = getchar();\n");
      break;
    case LOOP_START:
      strcat(output, "while (*ptr) {\n");
      break;
    case END:
      strcat(output, "}\n");
      break;
    }
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