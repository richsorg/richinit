#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <dirent.h>
#include <fcntl.h>

// will rewrite this aids soon
void wait_for_death(void) {
	struct dirent *file = NULL;

	for (int i = 0; i < 20; i++) {
		DIR *dir = opendir("/proc/");

		while ((file = readdir(dir))) {
			if (*file->d_name >= '0' && *file->d_name <= '9') {
				if (atoi(file->d_name) > 0) {
					closedir(dir);
					dir = NULL;
					break;
				}
			}
		}

		if (dir) {
			closedir(dir);
			puts("All processes died.");
			return;
		}

		sleep(2);
	}
}

void killall(int signal) {
	struct dirent *file = NULL;
	DIR *dir = opendir("/proc/");

	while ((file = readdir(dir))) {
		if (*file->d_name >= '0' && *file->d_name <= '9') {
			pid_t pid = atoi(file->d_name);

			if (pid > 2)
				kill(pid, signal);
		}
	}

	closedir(dir);
}
