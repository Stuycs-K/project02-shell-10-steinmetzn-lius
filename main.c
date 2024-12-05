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
    char * input2 = input;
    char * input3 = input;
    while ((token = strsep(&input, ";")) != NULL) {
      char * token2 = token;
      char * token3 = token;
      input2 = strsep(&token2, ">");
      input3 = strsep(&token3, "<");
      if (token2 == NULL && token3 == NULL || strcmp(token2,input2) == 0){ //check if token contained >
        parse_args(token, args);
        execute(args[0], args);
      }
      else{
        if (token3 == NULL){
          sscanf(token2, " %s", token2);
          int place = redirectOut(token2);
          parse_args(input2, args);
          execute(args[0], args);
          redirectOutBack(place);
        }
        else{
          sscanf(token3, " %s", token3);
          int place = redirectIn(token3);
          parse_args(input3, args);
          execute(args[0], args);
          redirectInBack(place);
        }
      }
    }
  }

  return 0;
}
