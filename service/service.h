#pragma once

#include <limits.h>
#include <signal.h>
#include "../bool.h"

#define SERVER "/tmp/rich.socket"

#define USER_DIR "/etc/richinit/services/user"
#define SYSTEM_DIR "/etc/richinit/services/system"							

struct service_t {
	char file[PATH_MAX], *name;
	struct service_t *next;
} typedef service_t;

#define CHECK_SERVICE(service) 	\
	(service->file && 			\
	service->name &&)

#define TERMPROC(pid)					\
	if (pid) {							\
		kill(pid, SIGTERM);				\
		waitpid(pid, NULL, WNOHANG);	\
		kill(pid, SIGKILL);				\
	} 		

service_t *find_service(char *);

void add_service(service_t *);
void start_service(int, service_t *);

void read_operation(void);
void read_services(void);
