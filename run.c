#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "util.h"
#include "debug.h"

void run_scripts(char *directory, char *action) {
	struct dirent *file = NULL;
	DIR *dir = opendir(directory);

	while ((file = readdir(dir))) {
		if (RUNNABLE(file->d_name)) {
			DEBUG("Running %s/%s\n", directory, file->d_name);
			util_system("%s/%s %s", directory, file->d_name, action);
		}
	}

	closedir(dir);
}
