#ifndef SHELL_H
#define SHELL_H

void print_prompt();
void change_dir(char * path);
void parse_args(char * line, char ** arg_ary);
void execute(char * args[], int input_redirect, int output_redirect, char *input_file, char *output_file);

#endif
