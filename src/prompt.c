#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "banglish.h"

char getch_noecho() {
	struct termios old, current;

	tcgetattr(STDIN_FILENO, &old);
	current = old;

	current.c_lflag |= (~ICANON | ~ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &current);

	char ch = 0;
	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &old);
	return ch;
}

void show_prompt(int status) {
	char *username = get_username();
	char *hostname = get_hostname();
	char *working_dir = get_current_home_relative_working_dir();

	printf(BANGLISH_RESET_COLOR);
	printf("[");
	printf(BANGLISH_FG_RED_COLOR);
	printf("%d", status);
	printf(BANGLISH_RESET_COLOR);
	printf("] ");

	printf(BANGLISH_FG_GREEN_COLOR);
	printf("%s", username);

	printf(BANGLISH_RESET_COLOR);
	printf("@");

	printf(BANGLISH_FG_BLUE_COLOR);
	printf("%s", hostname);

	printf(BANGLISH_RESET_COLOR);
	printf(": ");

	printf(BANGLISH_FG_YELLOW_COLOR);
	printf("%s", working_dir);

	printf(BANGLISH_RESET_COLOR);
	printf(" %% ");

	free_ifnotnull_and_setnull(hostname);
	free_ifnotnull_and_setnull(working_dir);
}

char *get_prompt() {
	size_t size = 256;
	char *str = (char *)malloc_with_err(size * sizeof(char), NULL);
	char c = 0;
	size_t i = 0;

	bool active = true;
	while (active) {
		if (i + 1 == size) {
			size *= 2;
			str = realloc_with_err(str, sizeof(char) * size, NULL);
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

		if (active)
			i++;
	}

	str[i] = 0;
	str = realloc_with_err(str, i + 1 * sizeof(char *), NULL);
	return str;
}