#include <stdio.h>
#include "shell.h"

int main() {
  while (1){
    print_prompt();
    char * args[50];
    char line[250];
    fgets(line, sizeof(line), stdin);
    parse_args(line, args);
    execute(args[0], args);
  }

  return 0;
}
