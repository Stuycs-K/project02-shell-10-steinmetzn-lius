#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

#define MAX_INPUT_SIZE 250
#define MAX_ARGS 100

// pipe handling, call once for each side. if side is left, redirect stdout to a temp file. if side is right, redirect the temp file to stdin. returns nothinng
void handle_pipe(char * command, char * side) {
  char *args[MAX_ARGS];
  
  // preparing for redirection
  int input_redirect = 0, output_redirect = 0;
  char *input_file = NULL, *output_file = NULL;
  
  // remove leading spaces
  while (*command == ' ') command++;

  if (strcmp(side, "left") == 0) {
    char *input_redirect_pos = strchr(command, '<');
    if (input_redirect_pos != NULL) {
      input_redirect = 1;
      *input_redirect_pos = '\0';
      input_file = strtok(input_redirect_pos + 1, " \t");
    }
    output_redirect = 1;
    output_file = "temp";

    // remove trailing spaces
    char * end = command + strlen(command) - 1;
    while (end > command && *end == ' ') {
        *end = '\0';
        end--;
    }

    parse_args(command, args);
    execute(args, input_redirect, output_redirect, input_file, output_file);
  }
  // side == "right"
  else {
    char *output_redirect_pos = strchr(command, '>');
    if (output_redirect_pos != NULL) {
      output_redirect = 1;
      *output_redirect_pos = '\0';
      output_file = strtok(output_redirect_pos + 1, " \t");
    }
    input_redirect = 1;
    input_file = "temp";

    // remove trailing spaces
    char * end = command + strlen(command) - 1;
    while (end > command && *end == ' ') {
        *end = '\0';
        end--;
    }

    parse_args(command, args);
    execute(args, input_redirect, output_redirect, input_file, output_file);
    remove("temp");
  }
}

int main() {
  while (1){
    print_prompt();
    char line[MAX_INPUT_SIZE];
    if (fgets(line, sizeof(line), stdin) == NULL) {
        printf("\n");
        break; //ctrl-d exit
    }

    // strips newline character if present
    line[strcspn(line, "\n")] = '\0';

    char * input = line;
    char * command;
    
    // split input by semicolons
    while ((command = strsep(&input, ";")) != NULL) {
      // pipe
      if (strchr(command, '|')) {
        char *cmd1 = strsep(&command, "|");
        handle_pipe(cmd1, "left");
        handle_pipe(command, "right");
      }
      else {
        char *args[MAX_ARGS];

        // preparing to handle redirection
        int input_redirect = 0, output_redirect = 0;
        char *input_file = NULL, *output_file = NULL;
        
        // remove leading spaces
        while (*command == ' ') command++;

        // check for redirection symbols
        char *input_redirect_pos = strchr(command, '<');
        char *output_redirect_pos = strchr(command, '>');
        
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
        char * end = command + strlen(command) - 1;
        while (end > command && *end == ' ') {
            *end = '\0';
            end--;
        }

        parse_args(command, args);
        execute(args, input_redirect, output_redirect, input_file, output_file);
      }
    }
  }

  return 0;
}