#ifndef SHELL_H
#define SHELL_H

void print_prompt();
void change_dir(char * path);
void parse_args(char * line, char ** arg_ary);
void execute(char first[], char * args[]);
int redirectOut(char * newOut);
void redirectOutBack(int backup_stdout);
void handle_pipe(char * cmd1, char * cmd2);

#endif
