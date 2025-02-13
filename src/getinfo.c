#include <stdlib.h>
#include <unistd.h>

#include "banglish.h"

char *get_current_working_dir() {
	size_t size = 1024 * 8;
	char *buff = malloc_with_err(size + 1, NULL);
	if (getcwd(buff, size) != NULL) {
		return buff;
	} else {
		return calloc(1, 1);
	}
}

char *get_username() {
	char *buff = getenv("USER");
	if (buff) {
		return buff;
	} else {
		return "";
	}
}

char *get_hostname() {
	size_t size = 256 * 8;
	char *buff = malloc_with_err(size, NULL);
	if (gethostname(buff, size) == 0) {
		return buff;
	}
	return calloc(1, 1);
}

char *get_current_home_relative_working_dir() {
	char *full_path = get_current_working_dir();
	char *home = getenv("HOME");

	if (home) {
		size_t i = 0;
		while (home[i]) {
			if (full_path[i] == '\0' || home[i] != full_path[i]) {
				return full_path;
			}
			i++;
		}
		size_t str_size = 1024 * 8;
		char *relative_path = (char *)malloc_with_err(str_size + 1, NULL);
		size_t k = 0;
		relative_path[k] = '~';
		while (full_path[i]) {
			k++;
			relative_path[k] = full_path[i];
			i++;
		}
		free_ifnotnull_and_setnull(full_path);
		return relative_path;
	}

	return full_path;
}