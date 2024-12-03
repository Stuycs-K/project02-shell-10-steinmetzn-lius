#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include "shell.h"

//takes in command from user and separates its arguments; input is line, which is put it into array arg_ary; no return
void parse_args( char * line, char ** arg_ary ){ 
  char * token;
  int i = 0;
  while (line){
    token = strsep(&line, " ");
    arg_ary[i] = token;
    i++;
  }
  arg_ary[i] = NULL;
}

//fork and execvp; first[] is arg[0] and args[] is arguments from input; returns 1 when done
void execute(char first[], char * args[]){
  pid_t p;
  p = fork();
  if(p<0){
    perror("fork fail");
    exit(1);
  } else if ( p == 0){
    execvp(first, args);
  }else{
    int status;
    int child;
    WIFEXITED(status);
    child = wait(&status);
  }
}