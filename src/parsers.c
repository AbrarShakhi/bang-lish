#include <stdlib.h>
#include <string.h>

#include "ilish.h"

char **split_prompt(char *input) {
	char *delim = " \t\n";
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