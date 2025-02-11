#ifndef PARSERS_H
#define PARSERS_H

#include <stdbool.h>

struct statement {
	char **cmdarg;
	bool is_operator;
	bool need_freeing;
};

char **split_prompt(char *input);
struct statement *parseargs(char *input);

#endif  // !PARSERS_H