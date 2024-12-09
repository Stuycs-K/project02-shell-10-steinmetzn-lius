#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

#define MAX_INPUT_SIZE 250
#define MAX_ARGS 100

void handle_pipe(char * command, char * side) {
  int input_redirect = 0, output_redirect = 0;
  char *input_file = NULL, *output_file = NULL;
  
  // remove leading spaces
  while (*command == ' ') command++;

  char *command_copy = strdup(command);
  char *args[MAX_ARGS];
  int arg_count = 0;

  if (strcmp(side, "left") == 0) {
    char *input_redirect_pos = strchr(command_copy, '<');
    if (input_redirect_pos != NULL) {
      input_redirect = 1;
      *input_redirect_pos = '\0';
      input_file = strtok(input_redirect_pos + 1, " \t");
    }
    output_redirect = 1;
    output_file = "temp";

    // remove trailing spaces
    char * end = command_copy + strlen(command_copy) - 1;
    while (end > command_copy && *end == ' ') {
        *end = '\0';
        end--;
    }

    parse_args(command_copy, args);
    execute(args, input_redirect, output_redirect, input_file, output_file);
  }
  else {
    char *output_redirect_pos = strchr(command_copy, '>');
    if (output_redirect_pos != NULL) {
      output_redirect = 1;
      *output_redirect_pos = '\0';
      output_file = strtok(output_redirect_pos + 1, " \t");
    }
    input_redirect = 1;
    input_file = "temp";

    // remove trailing spaces
    char * end = command_copy + strlen(command_copy) - 1;
    while (end > command_copy && *end == ' ') {
        *end = '\0';
        end--;
    }

    parse_args(command_copy, args);
    execute(args, input_redirect, output_redirect, input_file, output_file);
  }
}

int main() {
  while (1){
    print_prompt();
    char line[MAX_INPUT_SIZE];
    if (fgets(line, sizeof(line), stdin) == NULL) {
        printf("\n");
        break; //ctrl d exit
    }

    // strips newline character if present
    line[strcspn(line, "\n")] = '\0';

    char * input = line;
    char *commands[MAX_ARGS];
    char * command;
    int command_count = 0;
    
    // split input by semicolons
    while ((command = strsep(&input, ";")) != NULL) {
        commands[command_count++] = command;
    }
    
    for (int i = 0; i < command_count; i++) {
        // pipe
        if (strchr(commands[i], '|')) {
          char *cmd1 = strsep(&commands[i], "|");
          handle_pipe(cmd1, "left");
          handle_pipe(commands[i], "right");
        }
        else {

        // preparing to handle redirection
        int input_redirect = 0, output_redirect = 0;
        char *input_file = NULL, *output_file = NULL;
        
        // remove leading spaces
        while (*commands[i] == ' ') commands[i]++;

        char *command_copy = strdup(commands[i]);
        char *args[MAX_ARGS];

        // check for redirection symbols
        char *input_redirect_pos = strchr(command_copy, '<');
        char *output_redirect_pos = strchr(command_copy, '>');
        
        if (input_redirect_pos != NULL || output_redirect_pos != NULL) {
          if (input_redirect_pos != NULL) {
            input_redirect = 1;
            *input_redirect_pos = '\0';
            input_file = strtok(input_redirect_pos + 1, " \t");
        }
            
        if (output_redirect_pos != NULL) {
            output_redirect = 1;
            *output_redirect_pos = '\0';
            output_file = strtok(output_redirect_pos + 1, " \t");
          }
        }
        // remove trailing spaces
        char * end = command_copy + strlen(command_copy) - 1;
        while (end > command_copy && *end == ' ') {
            *end = '\0';
            end--;
        }


        parse_args(command_copy, args);
        execute(args, input_redirect, output_redirect, input_file, output_file);
        }
    }
    
  }

  return 0;
}