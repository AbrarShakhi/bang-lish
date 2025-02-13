#include <signal.h>
#include <stdbool.h>
#include <stdio.h>

#include "banglish.h"


void handle_sigint() {}

int main(int argc, char const *argv[]) {
	signal(SIGINT, handle_sigint);

	int status = 0;
	while (true) {
		show_prompt(status);
		char *user_input = get_prompt();
		fflush(stdin);

		char **statements = parseargs(user_input);
		execute_cmds(statements, &status);

		free_ifnotnull_and_setnull(statements);
		free_ifnotnull_and_setnull(user_input);
	}
}
