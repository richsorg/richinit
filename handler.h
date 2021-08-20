#pragma once
#include <signal.h>

#define REBOOT() 						 \
	run_scripts("/etc/rc6.d", "stop");   \
    sync();								 \
    reboot(RB_AUTOBOOT);

#define POWEROFF()						 \
    run_scripts("/etc/rc0.d", "stop");   \
	sync();								 \
	reboot(LINUX_REBOOT_CMD_POWER_OFF);
