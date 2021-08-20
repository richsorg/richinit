#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include "bool.h"
#include "debug.h"
#include "handler.h"

void reap_processes(void) {
	while (TRUE) {
		for (int i = 0; i < 10; i++)
			waitpid(-1, NULL, WNOHANG);
		waitpid(-1, 0, 0);
	}
}

// fork and exec is very normal for starting processes
void spawn(char **args) {
	pid_t pid = fork();

	if (pid == -1) {
		ERROR("Failed to fork for spawn\n");
		return;
	}

	else if (pid == 0) {
		setsid();
		execvp(args[0], args);
		_exit(1);
	}
}
