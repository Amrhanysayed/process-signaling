#pragma once
#include "cmpsh.h"

typedef struct {
    char *command;       // The command
    char **args;         // Array of arguments 
    int num_args;        // Number of arguments
    char *redirect_file; // File for output redirection
} Command;

Command parse_input(char *input);


