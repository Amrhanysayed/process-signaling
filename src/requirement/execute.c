#include "execute.h"

void Execute(Command *cmd)
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "Fork failed\n");
        return;
    }
    if (pid == 0)
    {
        // child

        if (cmd->redirect_file)
        {
            int fd = open(cmd->redirect_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                fprintf(stderr, "An error has occurred!\n");
                exit(1);
            }

            if (dup2(fd, STDOUT_FILENO) < 0)
            {
                fprintf(stderr, "An error has occurred!\n");
                close(fd);
                exit(1);
            }
            close(fd);
        }

        if (num_paths == 0)
        {
            execvp(cmd->command, cmd->args);
            fprintf(stderr, "An error has occurred!\n");
            exit(1);
        }

        /// search in the paths
        char exec_path[1024];
        for (int i = 0; i < num_paths; i++)
        {
            snprintf(exec_path, sizeof(exec_path), "%s/%s", paths[i], cmd->command);
            execvp(exec_path, cmd->args);
        }

        fprintf(stderr, "An error in external commands \n");
        exit(1);
    }
    else
    {
        // parent
        current_pid = pid;
        int status;
        waitpid(pid, &status, 0);
        current_pid = 0;
    }
}