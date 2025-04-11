
#include "parser.h"

Command parse_input(char *input)
{
    Command cmd={0};

    char *temp_args[10] = {0}; 
    int arg_count = 0;

    char *I_copy = strdup(input);
    if (I_copy == NULL) {
        return cmd ;
    }
    char *token = strtok(I_copy, " ");
    while (token && arg_count < 10) {

        if(strcmp(token, ">") == 0) {
            token = strtok(NULL, " ");
            if (token == NULL) {
                fprintf(stderr, "Error: No file specified for output redirection\n");
                free(I_copy);
                return cmd;
            }
            cmd.redirect_file = strdup(token);
            token = NULL; 
            break;
        }


        temp_args[arg_count] = strdup(token);
        arg_count++;
        token = strtok(NULL, " ");
    }


    if(token!=NULL){
        fprintf(stderr, "Error: Too many arguments\n");
        free(I_copy);
        for(int i = 0; i < arg_count; i++) {
            free(temp_args[i]);
        }
        return cmd;
    }


    if(arg_count>0){
        cmd.command = temp_args[0];
        cmd.num_args = arg_count;
        cmd.args = malloc((arg_count + 1) * sizeof(char *)*2);
        for(int i = 0; i < arg_count; i++) {
            cmd.args[i] = temp_args[i];
        }
        cmd.args[arg_count] = NULL;
    }
    free(I_copy);
    return cmd;


    
}

