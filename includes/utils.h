#pragma once

#include "parsers.h"

void free_ifnotnull_and_setnull(void *ptr);

void *malloc_with_err(size_t size, const char *err);
void *realloc_with_err(void *ptr, size_t size, const char *err);
