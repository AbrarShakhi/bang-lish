#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "ilish.h"

void show_prompt(int st) {
	size_t len_chars = sizeof(char) * 256 * 8;
	char *cwdbuffer = malloc(len_chars);
	if (!cwdbuffer) {
		perror("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	char *username = get_username();
	char *hostname = get_hostname();
	char *working_dir = get_current_working_dir();

	printf("[%d]%s@%s:%s %% ", st, username, hostname, working_dir);

	free(hostname);
	free(working_dir);
}

char *get_prompt() {
	size_t size = 256;
	char *str = (char *)malloc(size * sizeof(char));
	char c = 0;
	size_t i = 0;

	bool active = true;
	while (active) {
		if (i + 1 == size) {
			size *= 2;
			str = (char *)realloc(str, sizeof(char) * size);
		}

		c = getchar();
		switch (c) {
			case EOF:
				active = false;
				break;
			case 0:
				active = false;
				break;
			case '\\':
				i--;
				getchar();
				break;

			case '\n':
				active = false;
				break;

			default:
				str[i] = c;
				break;
		}

		if (active) i++;
	}

	str[i] = 0;
	return str;
}