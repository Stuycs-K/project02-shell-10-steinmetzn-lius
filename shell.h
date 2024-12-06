#ifndef SHELL_H
#define SHELL_H

int err();
void print_prompt();
void change_dir(char * path);
void parse_args(char * line, char ** arg_ary);
void execute(char first[], char * args[]);
int redirectOut(char * newOut);
void redirectOutBack(int backup_stdout);
void redirectIn(char * command, char * newIn);
//void redirectInBack(int backup_stdin);

#endif
