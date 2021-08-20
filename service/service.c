#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <sys/un.h>
#include <sys/socket.h>

#include "../util.h"
#include "../bool.h"
#include "../debug.h"
#include "protocol.h"
#include "service.h"

service_t *head = NULL;

char *find_property(char data[], char property[]) {
	int off = util_stristr(data, property);

	if (off != -1) {
		int end = util_stristr(data + off, "\n") - 1;
		return strndup(data + off, end);
	}
	else {
		return NULL;
	}
}

service_t *parse_service(char *file) {
	service_t *service = malloc(1 * sizeof(service_t));
	char *buff = read_file_content(file, NULL, -1);

	snprintf(service->file, PATH_MAX, "/etc/init.d/%s", file);
	service->name =  strdup(file);
	return service;
}

void read_service(char *path) {
	INFO("Preparing services.\n");
	chdir(path);

	struct dirent *file = NULL;
	DIR *dir = opendir(path);

	while ((file = readdir(dir))) {
		if (*file->d_name == '.') continue;

		service_t *service = parse_service(file->d_name);

		if (service) {
			add_service(service);
		}
		else {
			WARN("Failed to parse service: %s\n", file->d_name);
		}
	}

	closedir(dir);
}

void add_service(service_t *service) {
	if (!head) {
		head = service;
	}
	else {
		service->next = head;
		head = service;
	}
}

void modify_service(int fd, service_t *service, char *state) {
	pid_t pid = fork();

	if (pid != 0)
		return;

	char *run[] = {service->file, state, NULL};
	INFO("Starting service: %s\n", service->file);

	close(1);
	close(2);

	dup2(fd, 1);
	dup2(fd, 2);

	execvp(run[0], run);
}

service_t *find_service(char *name) {
	service_t *tmp = head;

	while (tmp) {
		if (!strcmp(tmp->name, name))
			return tmp;
		tmp = tmp->next;
	}

	return NULL;
}

void service_ctl(int fd, char *name, operation_t op) {
	service_t *service = find_service(name);

	if (!service) {
		sockprintf(fd, "Failed to find service: %s\n", name);
		return;
	}

	switch (op) {
		case START:
			modify_service(fd, service, "start");
			break;

		case STOP:
			modify_service(fd, service, "stop");
			break;

		case RESTART:
			modify_service(fd, service, "restart");
			break;

		case STATUS:
			modify_service(fd, service, "status");
			break;
	}
}

void read_operation(void) {
	int fd = socket(AF_UNIX, SOCK_STREAM, 0), client;

	struct sockaddr_un addr = {AF_UNIX, SERVER};
	unlink(SERVER);

	INFO("Starting service daemon\n");

	if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
		ERROR("Failed to bind for service manager.\n");
		return;
	}

	if (listen(fd, 1) == -1) {
		ERROR("Failed to listen for service manager.\n");
		return;
	}

	socklen_t len = sizeof(addr);
	csum_t csum = {0};

	while (TRUE) {
		if ((client = accept(fd, (struct sockaddr *)&addr, &len)) != -1) {
			int n = recv(client, &csum, sizeof(csum), MSG_NOSIGNAL);

			if (csum.name_len > 0) {
				char name[csum.name_len + 1];
				name[csum.name_len] = 0;
				recv(client, name, csum.name_len, MSG_NOSIGNAL);
				service_ctl(client, name, csum.op);
			}

			close(client);
		}
	}

	ERROR("Failed to init service system\n");
}
