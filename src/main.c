#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "boolean.h"
#include "getinfo.h"


char *getprompt() {
  size_t size = 256;
  char *str = (char *)malloc(size * sizeof(char));
  char c = 0;
  size_t i = 0;

  size_t len_chars = sizeof(char) * 1024 * 8;
  char *cwd = malloc(len_chars);
  printf("%s@%s:%s $ ", getenv("USER"), getenv("HOST"),
         get_this_dir(cwd, len_chars));

  free(cwd);
  cwd = NULL;

  boolean active = true;
  while (active) {
    if (i + 1 == size) {
      size *= 2;
      str = (char *)realloc(str, sizeof(char) * size);
    }

    c = getchar();
    switch (c) {
    case EOF:
      active = false;
      break;
    case 0:
      active = false;
      break;
    case '\\':
      i--;
      getchar();
      break;

    case '\n':
      active = false;
      break;

    default:
      str[i] = c;
      break;
    }

    if (active)
      i++;
  }

  str[i] = 0;
  return str;
}

char **split_prompt(char *input) {
  char *delim = " ";
  size_t size = 8;
  char **outarr = (char **)malloc(sizeof(char *) * size);

  size_t i = 0;
  char *tok = strtok(input, delim);
  while (tok) {
    if (i + 1 == size) {
      size *= 2;
      outarr = (char **)realloc(outarr, size * sizeof(char **));
    }

    outarr[i] = tok;
    i++;
    tok = strtok(NULL, delim);
  }
  outarr[i] = tok;
  return outarr;
}

int main() {
  char *input;
  pid_t pid;
  char **inarg;

  while (true) {
    input = getprompt();
    fflush(stdin);
    inarg = split_prompt(input);

    if (!strcmp(inarg[0], "exit")) {
      exit(0);
    } else if (!strcmp(inarg[0], "cd")) {
      chdir(inarg[1]);
    } else {
      if (pid = fork()) {
        wait(NULL);
      } else {
        if (execvp(inarg[0], inarg) == -1) {
          fprintf(stderr, "Command '%s' not found.\n", inarg[0]);
          break;
        }
      }
    }

    free(inarg);
    inarg = NULL;
    free(input);
    input = NULL;
  }
}
