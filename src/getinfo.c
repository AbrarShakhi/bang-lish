#include <stdlib.h>
#include <unistd.h>

#include "banglish.h"

char *get_current_working_dir() {
	size_t size = 1024 * 8;
	char *buff = malloc(size);
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
	char *buff = malloc(size);
	if (gethostname(buff, size) == 0) {
		return buff;
	}
	return calloc(1, 1);
}