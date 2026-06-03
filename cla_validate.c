#include "inverted.h"

// Function to validate input files
int cla_validate(int argc, char *argv[], Node **head)
{
    int i;

    for(i = 1; i < argc; i++)
    {
        // check extension
        if(strstr(argv[i], ".txt") == NULL)
        {
            printf("%s is not a txt file\n", argv[i]);
            continue;
        }

        FILE *fp = fopen(argv[i], "r");

        if(fp == NULL)
        {
            printf("%s file not found\n", argv[i]);
            continue;
        }

        fseek(fp, 0, SEEK_END);

        if(ftell(fp) == 0)
        {
            printf("%s file is empty\n", argv[i]);
            fclose(fp);
            continue;
        }

        fclose(fp);

        // add file to file list
        create_file_list(head, argv[i]);
    }

    return SUCCESS;
}