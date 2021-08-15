#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/stat.h>

#include "bool.h"
#include "util.h"
#include "debug.h"

BOOL util_mem_exists(char *haystack, char *needle) {
	char *ptr = needle;

	while (*haystack) {
		if (*haystack++ == *needle) {
			if (!(*++needle))
				return TRUE;
		}
		else
			needle = ptr;
	}

	return FALSE;
}

char *read_file_content(char *file, char *ptr, int len) {
	int fd = open(file, O_RDONLY);

	struct stat st = {0};
	fstat(fd, &st);

	char *buffer = malloc(st.st_size * sizeof(char));

	if (ptr == NULL)
		read(fd, buffer, st.st_size);
	else {
		read(fd, ptr, len);
		buffer = ptr;
	}

	close(fd);

	return buffer;
}

void util_system(const char *fmt, ...) {
	char *buffer;

	va_list args;

	va_start(args, fmt);

	vasprintf(&buffer, fmt, args);

	va_end(args);

	DEBUG("%s\n", buffer);
	system(buffer);
	free(buffer);
}
