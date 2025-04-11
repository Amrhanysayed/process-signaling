#include "builtins.h"

void Exit()
{
    exit(0);
}

void Cd(Command *cmd)
{
    if(cmd->num_args<2){
        fprintf(stderr, "cd: missing argument\n");
        return;
    }
    /// 0 for success, -1 for failure
    if(chdir(cmd->args[1]) != 0) {
        fprintf(stderr, "cd: %s: No such file or directory\n", cmd->args[1]);
        return;
    }

}

void Pwd()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        fprintf(stderr, " error in pwd\n");
    }
}

void Paths(Command *cmd)
{
 
    /// remove the current paths 
    for(int i = 0; i < num_paths; i++) {
        free(paths[i]);
        paths[i] = NULL;
    }

    num_paths = 0;
    // no arguments --> clear 
    if(cmd->num_args ==1) {
        return;
    }
    int new_paths = cmd->num_args - 1;

    if (new_paths > MAX_PATHS) {
        fprintf(stderr, "An error has occurred!\n");
        return;
    }

    for (int i=0;i<new_paths;i++){
        paths[i]= strdup(cmd->args[i+1]);
        if(paths[i] == NULL) {
            fprintf(stderr, "An error has occurred!\n");
            for (int j = 0; j < i; j++) {
                free(paths[j]);
            }
            num_paths = 0;
            paths[0] = NULL;
            return;
        }
        /// global increment
        num_paths++;

    }

}
