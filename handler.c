#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>

#include <sys/wait.h>
#include <linux/reboot.h>
#include <sys/reboot.h>

#include "util.h"
#include "handler.h"

void run_reboot(void) {
	/*
	puts("Going for a reboot");
	killall(SIGTERM);
	wait_for_death();
	killall(SIGKILL);

	system("umount -a -r");

    reboot(RB_AUTOBOOT);
    */
    sync();
    reboot(RB_AUTOBOOT);
}

void run_shutdown(void) {
	/*
	puts("Going for a shutdown");

	killall(SIGTERM);
	wait_for_death();
	killall(SIGKILL);
	*/

	sync();
	reboot(LINUX_REBOOT_CMD_POWER_OFF);
}

void run_halt(void) {
	sync();
	reboot(LINUX_REBOOT_CMD_POWER_OFF);
}
