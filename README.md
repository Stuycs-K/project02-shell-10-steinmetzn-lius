[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Tfg6waJb)
# Systems Project2 - MyShell

**Group Name:** Seg fault counter: INT_MAX
<br>
**Group Members:** Naomi Steinmetz, Sophie Liu
<hr>

**Shell Features:**
- reading user input
- execute commands
- command separation with semicolons
- printing cwd path
- exiting w/ "exit" and ctrl d
- redirection w/ > and <
- handling one pipe

**Failed Shell Features:**
- using popen for pipes
- redirection with more than one pipe at a time

**Bugs:**
- if doing ./shell.out < lines.txt and lines.txt contains a pipe, the commands will execute once, then there will be fork fail: Resource temporarily unavailable, and temp is not removed

**Function Headers:**
```
void print_prompt();
void change_dir(char * path);
void parse_args(char * line, char ** arg_ary);
void execute(char * args[], int input_redirect, int output_redirect, char * input_file, char * output_file);
void handle_pipe(char * command, char * side);
```

