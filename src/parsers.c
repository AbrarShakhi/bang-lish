#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "banglish.h"


static char *operators[] = {
    ";", "&", "|", "\n", "\r", "&&", "||", ">", "<", ">>", NULL,
};

char *delim = " \t\r\n";

int which_op(char *str) {
	for (size_t i = 0; operators[i]; i++) {
		if (strcmp(str, operators[i]) == 0) {
			return i;
		}
	}
	return -1;
}

char **parseargs(char *input) {
	size_t capacity = 8;
	char **outarr = (char **)malloc(sizeof(char *) * capacity);

	size_t i = 0;
	char *tok = strtok(input, delim);
	while (tok) {
		if (i + 1 == capacity) {
			capacity *= 2;
			outarr = (char **)realloc(outarr, capacity * sizeof(char **));
		}

		outarr[i] = tok;
		i++;
		tok = strtok(NULL, delim);
	}
	outarr[i] = tok;
	return outarr;
}
