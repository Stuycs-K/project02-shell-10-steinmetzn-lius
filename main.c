#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

int main() {
  while (1){
    print_prompt();
    char * args[50];
    char line[250];
    char * command;
    if (fgets(line, sizeof(line), stdin) == NULL) {
      exit(1); // ctrl d
    }
    char * input = line;
    char * input3 = input;
    while ((command = strsep(&input, ";")) != NULL) {
      char * command_right = command;
      char * token3 = command;
      char * command_left = strsep(&command_right, ">");
      input3 = strsep(&token3, "<");
      if (command_right == NULL && token3 == NULL || strcmp(command_right, command_left) == 0){ //check if token contained >

        //remove leading and trailing spaces from command
        while (*command == ' ') command++;
        char * end = command + strlen(command) - 1;
        while (end > command && *end == ' ') end--;
        *(end + 1) = '\0';

        parse_args(command, args);
        execute(args[0], args);
      }
      else{
        if (token3 == NULL){
          //remove leading spaces from right part of command and trailing spaces from left part of command
          while (*command_right == ' ') command_right++;
          char * end = command_left + strlen(command_left) - 1;
          while (end > command_left && *end == ' ') end--;
          *(end + 1) = '\0';

          sscanf(command_right, " %s", command_right);
          int place = redirectOut(command_right);
          parse_args(command_left, args);
          execute(args[0], args);
          redirectOutBack(place);
        }
        else{
          sscanf(token3, " %s", token3);
          redirectIn(input3, token3);
          parse_args(input3, args);
          execute(args[0], args);
        }
      }
    }
  }

  return 0;
}
