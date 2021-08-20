#pragma once

#include <sys/stat.h>
#include "bool.h"

#define START_TTY(x) spawn((char *[]){"/sbin/agetty", "--noclear", "tty"x"", NULL});

#define RUNNABLE(str) ((*str) != '.' && strcmp(str, "README"))
#define LEN(x) (sizeof(x) / sizeof(*x))
#define RUN(x) system(x)
//define EXISTS(x) (stat(x, &(stat){0}) == 0)


/* utilities */
char *read_file_content(char *, char *, int);
int util_stristr(char *, char *);

void sockprintf(int, const char *, ...);
void util_system(const char *, ...);
void reap_processes(void);
void run_scripts(char *, char *);
void spawn(char **);

/* shutdown utilities */
void wait_for_death(void);
void killall(int);
