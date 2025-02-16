#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "banglish.h"

int builtin_func_len() { return sizeof(builtin_str) / sizeof(char *); }

int banglish_cd(char *const argv[]) {
	char *target = argv[1];
	if (!target) {
		target = getenv("HOME");
	}
	if (chdir(target) != 0) {
		fprintf(stderr, "banglish: no such directory\n");
		return -1;
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

int banglish_exec(char *const argv[]) {
	argv++;
	if (execvp(argv[0], argv) == -1) {
		fprintf(stderr, "Command '%s' not found.\n", argv[0]);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}