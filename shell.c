#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"

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
