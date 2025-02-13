#include <stdio.h>
#include <stdlib.h>

#include "banglish.h"


void free_ifnotnull_and_setnull(void *ptr) {
	if (ptr) {
		free(ptr);
		ptr = NULL;
	}
}

void *malloc_with_err(size_t size, const char *err) {
	void *ptr = malloc(size);
	if (!ptr) {
		if (err) {
			perror(err);
		} else {
			perror("Not Enough Memory. (aborting)");
		}
		exit(EXIT_FAILURE);
	}
	return ptr;
}

void *realloc_with_err(void *ptr, size_t size, const char *err) {
	void *newptr = realloc(ptr, size);
	if (!newptr) {
		free_ifnotnull_and_setnull(ptr);
		if (err) {
			perror(err);
		} else {
			perror("Not Enough Memory. (aborting)");
		}
		exit(EXIT_FAILURE);
	}
	return newptr;
}
