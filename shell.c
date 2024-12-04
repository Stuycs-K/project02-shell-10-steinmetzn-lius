#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_PATH_LEN 1024

// prints current working directory. shortens home directory to ~
void print_prompt() {
  char dir[MAX_PATH_LEN];
  char *home = getenv("HOME");

  if (getcwd(dir, sizeof(dir)) != NULL) {
    if (home != NULL && strncmp(dir, home, strlen(home)) == 0) {
      printf("~%s", dir + strlen(home));
    }
    else {
      printf("%s", dir);
    }
  }
  else {
    perror("could not get cwd");
  }

  fflush(stdout);
  printf(" $ ");
}

// changes directory to given path
void change_dir(char *path) {
  if (chdir(path) != 0) {
    perror("cd error");
  }
}

//takes in command from user and separates its arguments; input is line, which is put it into array arg_ary; no return
void parse_args(char * line, char ** arg_ary){
  char * token;
  int i = 0;

  // strips newline character if present
  line[strcspn(line, "\n")] = '\0';

  while (line) {
    token = strsep(&line, " ");
    arg_ary[i] = token;
    i++;
  }
  arg_ary[i] = NULL;
}

//fork and execvp; first[] is arg[0] and args[] is arguments from input; returns 1 when done
void execute(char first[], char * args[]){

  // handling "cd" command
  if (strcmp(args[0], "cd") == 0) {
    if (args[1] != NULL) {
      change_dir(args[1]);
    }
    else {
      change_dir(getenv("HOME"));
    }
    return;
  }
  
  // handling "exit" command
  else if (strcmp(args[0], "exit") == 0) {
    kill(getpid(), 3);
  }

  pid_t p;
  p = fork();
  if (p < 0) {
    perror("fork fail");
    exit(1);
  } else if (p == 0) {
    execvp(first, args);
  } else {
    int status;
    int child;
    WIFEXITED(status);
    child = wait(&status);
  }
}
