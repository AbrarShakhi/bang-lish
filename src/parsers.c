#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "banglish.h"

char **split_prompt(char *input) {
	char *delim = " \t\r\n";
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

struct statement *parseargs(char *input) {
	char **splited = split_prompt(input);

	size_t capacity = 2;
	size_t i = 0;
	struct statement *stat =
	    (struct statement *)malloc(sizeof(struct statement) * capacity);


	return stat;
}