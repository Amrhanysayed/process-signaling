#include "cmpsh.h"
#include "parser.h"
#include "builtins.h"
#include "execute.h"
#include "noninteractive.h"

char *paths[MAX_PATHS] = {NULL};
int num_paths = 0;

pid_t current_pid = 0; /// global child process id

void signal_handler(int sig)
{
    if (current_pid > 0)
    {
        kill(current_pid, sig); 
    }
}

int main(int argc, char *argv[])
{
    char input[1024];
    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_handler);


    if (argc > 1)
    {
        NotInteractive(argv[1]);
        return 0;
    }    

    /// interactive mode
    while (1)
    {
        printf("cmpsh> ");
        fflush(stdout);
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break;
        }

        input[strcspn(input, "\n")] = 0; // Remove newline
        Command cmd = parse_input(input);

        if (cmd.command)
        {
            if (strcmp(cmd.command, "exit") == 0)
            {
                Exit();
            }
            else if (strcmp(cmd.command, "cd") == 0)
            {
                Cd(&cmd);
            }
            else if (strcmp(cmd.command, "pwd") == 0)
            {
                Pwd();
            }
            else if (strcmp(cmd.command, "paths") == 0)
            {
                Paths(&cmd);
                printf("Paths (%d): ", num_paths);
                for (int i = 0; i < num_paths; i++)
                {
                    printf("%s ", paths[i]);
                }
                printf("\n");
            }
            else
            {
                Execute(&cmd);
            }
        }
        else
        {
            fprintf(stderr, "Error: No command entered\n");
        }

        // Print parsed results
        if (cmd.command)
        {
            printf("Command: %s, Args: %d\n", cmd.command, cmd.num_args);
        }
        else
        {
            printf("No command\n");
        }
    }
    return 0;
}