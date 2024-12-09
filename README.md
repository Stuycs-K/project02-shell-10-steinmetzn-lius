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

**Function Headers:**
```
void print_prompt();
void change_dir(char * path);
void parse_args(char * line, char ** arg_ary);
void execute(char first[], char * args[]);
int redirectOut(char * newOut);
void redirectOutBack(int backup_stdout);
int redirectIn(char * newIn);
void redirectInBack(int backup_stdin);
void handle_pipe(char * command, char * side);
```

