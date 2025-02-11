#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "banglish.h"

bool exec_buildin(char **args, int *status) {
	for (size_t i = 0; i < builtin_func_len(); i++) {
		if (strcmp(args[0], builtin_str[i]) == 0) {
			*status = (*builtin_func[i])(args);
			return true;
		}
	}
	return false;
}

bool exec_new_proc(char **args, int *status) {
	pid_t pid = fork();

	if (pid == 0) {
		if (execvp(args[0], args) == -1) {
			fprintf(stderr, "Command '%s' not found.\n", args[0]);
			exit(EXIT_FAILURE);
		}
	} else if (pid > 0) {
		waitpid(pid, status, 0);
	} else {
		perror("Process creation failed\n");
		exit(EXIT_FAILURE);
	}

	return true;
}

void execute(char **args, int *status) {
	if (!args[0]) {
		return;
	}
	if (exec_buildin(args, status)) {
		return;
	}
	if (exec_new_proc(args, status)) {
		return;
	}
}

void handle_sigint() {}

int main(int argc, char const *argv[]) {
	signal(SIGINT, handle_sigint);

	int status = 0;
	while (true) {
		show_prompt(status);
		char *user_input = get_prompt();
		fflush(stdin);

		char **input_split_args = split_prompt(user_input);

		execute(input_split_args, &status);

		free(input_split_args);
		free(user_input);
	}
}
