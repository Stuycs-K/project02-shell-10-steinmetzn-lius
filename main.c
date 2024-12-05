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
    while ((command = strsep(&input, ";")) != NULL) {

      char * command_right = command; //part of cmd after >
      char * command_left = strsep(&command_right, ">");
      if (command_right == NULL || strcmp(command_right, command_left) == 0){

        //remove leading and trailing spaces from command
        while (*command == ' ') command++;
        char * end = command + strlen(command) - 1;
        while (end > command && *end == ' ') end--;
        *(end + 1) = '\0';

        parse_args(command, args);
        execute(args[0], args);
      }
      else {

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
    }
  }

  return 0;
}