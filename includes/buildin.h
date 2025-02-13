#pragma once

int banglish_cd(char *const argv[]);
int banglish_exit(char *const argv[]);
int banglish_help(char *const argv[]);
int banglish_exec(char *const argv[]);

static char *builtin_str[] = {"cd", "exit", "help", "exec"};

static int (*builtin_func[])(char *const argv[]) = {
    &banglish_cd, &banglish_exit, &banglish_help, &banglish_exec};

int builtin_func_len();
