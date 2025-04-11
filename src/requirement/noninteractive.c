#include "noninteractive.h"

void NotInteractive(const char *filename)
{
    FILE *input_file = fopen(filename, "r");
    if (input_file == NULL)
    {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        exit(1);
    }

    char input[1024];
    while (fgets(input, sizeof(input), input_file) != NULL)
    {
        input[strcspn(input, "\n")] = 0; 
        Command cmd = parse_input(input);

        if (cmd.command)
        {
            if (strcmp(cmd.command, "exit") == 0)
            {
                fclose(input_file);
                Exit();
            }
            else if (strcmp(cmd.command, "cd") == 0)
            {
                Cd(&cmd);
            }
            else if (strcmp(cmd.command, "pwd") == 0)
            {
                Pwd(&cmd);
            }
            else if (strcmp(cmd.command, "paths") == 0)
            {
                Paths(&cmd);
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

    }

    
    fclose(input_file);
    exit(0); 
}