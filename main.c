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
    char * token2;
    if (fgets(line, sizeof(line), stdin) == NULL) {
      exit(1); // ctrl d
    }
    char * input = line;
    while ((token = strsep(&input, ";")) != NULL) {
      char * command = token;
      while ((token2 = strsep(&command, ">"))) {
        //sophie remove space after ls -al
        printf("token2: %s000\n", token2);
        int place = redirectOut(command);
        parse_args(token2, args);
        execute(token2, args);
        redirectOutBack(place);
      }
      //parse_args(token, args);
      //execute(args[0], args);
    }
  //   char * input2 = input;
  //   while ((token = strsep(&input, ";")) != NULL) {
  //     char * token2 = token;
  //     input2 = strsep(&token2, ">");
  //     if (strcmp(token2,input2) != 0){
  //       int place = redirectOut(token2);
  //       execute(input2, args);
  //       redirectOutBack(place);
  //     }
  //     else{
  //       parse_args(token, args);
  //       execute(args[0], args);
  //     }
  //   }
  // }
}

  return 0;
}
