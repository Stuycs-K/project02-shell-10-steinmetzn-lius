#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include "shell.h"

#define MAX_PATH_LEN 1024
#define BUFFER_SIZE 1024


int err(){
  printf("errno %d\n",errno);
  printf("%s\n",strerror(errno));
  exit(1);
}


// prints current working directory. shortens home directory to ~. returns nothing
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

// changes directory to given path. returns nothing
void change_dir(char *path) {
  if (chdir(path) != 0) {
    perror("cd error");
  }
}

//takes in command from user and separates its arguments; input is line, which is put it into array arg_ary; no return
void parse_args(char * line, char ** arg_ary){
  char * token;
  int i = 0;

  while (line) {
    token = strsep(&line, " ");
    arg_ary[i] = token;
    i++;
  }
  arg_ary[i] = NULL;
}

//fork and execvp; args[] is arguments from input; redirect stdout if output_redirect 1; redirect stdin if input_redirect 1; no return
void execute(char * args[], int input_redirect, int output_redirect, char *input_file, char *output_file){

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
    exit(1);
  }

  pid_t p;
  p = fork();
  if (p < 0) {
    perror("fork fail");
    exit(1);
  } else if (p == 0) {

    // handle input redirection
    if (input_redirect) {
      int input_fd = open(input_file, O_RDONLY);
      if (input_fd == -1) {
        perror("Error opening input file");
        exit(1);
      }
      fflush(stdin);
      dup2(input_fd, STDIN_FILENO);
      close(input_fd);
    }

    // handle output redirection
    if (output_redirect) {
      int output_fd = open(output_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
      if (output_fd == -1) {
        perror("Error opening output file");
        exit(1);
      }
      fflush(stdout);
      dup2(output_fd, STDOUT_FILENO);
      close(output_fd);
    }

    execvp(args[0], args);

  } else {
    int status;
    int child;
    WIFEXITED(status);
    child = wait(&status);
  }
}
