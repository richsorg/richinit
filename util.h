#pragma once

#include "bool.h"

#define LEN(x) (sizeof(x) / sizeof(*x))
#define RUN(x) system(x)

/* utilities */
char *read_file_content(char *, char *, int);
void util_system(const char *, ...);
void reap_processes(void);
void spawn(char **);

/* shutdown utilities */
void wait_for_death(void);
void killall(int);
