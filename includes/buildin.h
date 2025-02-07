#ifndef BUILDIN_H
#define BUILDIN_H

int banglish_cd(char *const argv[]);
int banglish_exit(char *const argv[]);
int banglish_help(char *const argv[]);

static char *builtin_str[] = {"cd", "help", "exit"};

static int (*builtin_func[])(char *const argv[]) = {
    &banglish_cd, &banglish_help, &banglish_exit};

int builtin_func_len();

#endif