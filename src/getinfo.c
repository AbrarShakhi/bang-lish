#include <unistd.h>

#include "getinfo.h"

char *get_this_dir(char *cwd, size_t len) {
  if (getcwd(cwd, len) != NULL) {
    return cwd;
  } else {
    return "getcwd() error";
  }
}

