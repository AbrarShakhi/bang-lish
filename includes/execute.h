#pragma once

#include <stdbool.h>

#include "parsers.h"

bool exec_buildin(char **args, int *status);
bool exec_new_proc(char **args, int *status);
void execute_cmds(char **args, int *status);
