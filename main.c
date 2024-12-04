#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

int main() {
  while (1){
    print_prompt();
    char * args[50];
    char line[250];
    char * token;
    if (fgets(line, sizeof(line), stdin) == NULL) {
      exit(1); // ctrl d
    }
    char * input = line;
    while ((token = strsep(&input, ";")) != NULL) {
      parse_args(token, args);
      execute(args[0], args);
    }
  }

  return 0;
}
