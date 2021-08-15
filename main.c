#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <linux/reboot.h>
#include <sys/reboot.h>

#include "bool.h"
#include "util.h"

#include "getty.h"
#include "mount.h"
#include "handler.h"

void set_hostname(void) {
	char hostname[HOST_NAME_MAX] = {0};
	read_file_content("/etc/hostname", hostname, HOST_NAME_MAX);

	int fd = open("/proc/sys/kernel/hostname", O_WRONLY | O_CREAT, 0644);

	if (fd == -1) {
		ERROR("Failed to read hostname\n");
		return;
	}

	INFO("Setting hostname %s\n", hostname);
	write(fd, hostname, strlen(hostname));
	close(fd);
}

void run_startup(void) {
	pid_t pid = getpid();

	if (pid != 1) {
		ERROR("Please run as PID-1\n");
		return;
	}

	REMOUNT("/");
	MOUNT_FS();

	RUN("swapon -a");
	set_hostname();

	spawn((char *[]){"/sbin/getty", "--noclear", "tty0", NULL});
	reap_processes();
}

int main(int argc, char **args) {
	if (argc > 1) {
		switch(*args[1]) {
			case '6':
				run_reboot();
				break;

			case '0':
				run_halt();
				break;

			default:
				printf("Unhandled event: %s\n", args[1]);
				break;
		}
	}
	else {
		run_startup();
	}

	return 0;
}
