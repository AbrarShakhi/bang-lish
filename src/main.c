#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "ilish.h"

int main() {
	int status = 0;
	while (true) {
		show_prompt(status);
		char *user_input = get_prompt();
		fflush(stdin);

		char **input_split_args = split_prompt(user_input);

		if (!strcmp(input_split_args[0], "exit")) {
			if (input_split_args[1]) {
				exit(atoi(input_split_args[1]));
			} else {
				exit(0);
			}
		} else if (!strcmp(input_split_args[0], "cd")) {
			chdir(input_split_args[1]);
		} else {
			pid_t pid = fork();

			if (pid == 0) {
				if (execvp(input_split_args[0], input_split_args) == -1) {
					fprintf(stderr, "Command '%s' not found.\n",
					        input_split_args[0]);
					exit(EXIT_FAILURE);
				}
			} else if (pid > 0) {
				waitpid(pid, &status, 0);
			} else {
				perror("Process creation failed\n");
				exit(EXIT_FAILURE);
			}
		}

		free(input_split_args);
		free(user_input);
	}
}
