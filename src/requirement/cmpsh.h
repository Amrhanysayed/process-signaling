#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

#define MAX_PATHS 10
extern char *paths[MAX_PATHS];

extern int num_paths;

extern pid_t current_pid; /// for child process id 