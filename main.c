#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include "shell.h"

int main() {
  while (1){
    char * args[50];
    char line[250];
    printf("~/ $");
    fgets(line, sizeof(line), stdin);
    parse_args( line, args );
    execute(args[0], args);
  }
  return 0;
}
