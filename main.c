#include <stdio.h>
#include <string.h>
#include "shell.h"

int main() {
  while (1){
    print_prompt();
    char * args[50];
    char line[250];
    char * token;
    fgets(line, sizeof(line), stdin);
    char * input = line;
    while (token = strsep(&input, ";")) {
      printf("token: %s\n", token);
      parse_args(token, args);
      execute(args[0], args);
    }

    //parse_args(line, args);
    //execute(args[0], args);
  }

  return 0;
}
