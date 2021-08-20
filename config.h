#pragma once

#define RUNLEVEL "2"

/*
 S - true single user mode usually drops you into a minimal root shell
 1 - Administrative mode, you get a standard login request before access
 2 - Multi-user without TCP/IP networking -- could use serial ports for other logins
 3 - Multi-user with TCP/IP networking and text 
 4 - To be determined by the system owner
 5 - Multi-User with TCP/IP networking and graphic console 
 6 - reboot
 0 - shutdown and power down
*/
