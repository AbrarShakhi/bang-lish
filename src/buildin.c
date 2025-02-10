#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "banglish.h"

int builtin_func_len() { return sizeof(builtin_str) / sizeof(char *); }

int banglish_cd(char *const argv[]) {
	if (argv[1]) {
		if (chdir(argv[1]) != 0) {
			fprintf(stderr, "banglish: no such directory\n");
			return -1;
		}
	} else {
		if (chdir(getenv("HOME")) != 0) {
			fprintf(stderr, "banglish: no such directory\n");
			return -1;
		}
	}
	return 0;
}

int banglish_exit(char *const argv[]) {
	if (argv[1]) {
		exit(atoi(argv[1]));
	} else {
		exit(0);
	}
	return -1;
}

int banglish_help(char *const argv[]) {
	printf("Help unavailable");
	return -1;
}