#include "inverted.h"

int save_database(Hash_arr *table)
{
    char file_name[100];

    printf("Enter the filename: ");
    scanf("%s", file_name);

    /* check file extension */
    if (strstr(file_name, ".txt") == NULL)
    {
        printf("Invalid file type\n");
        return FAILURE;
    }

    FILE *fp = fopen(file_name, "w");
    if (fp == NULL)
    {
        printf("File cannot be created\n");
        return FAILURE;
    }

    /* write magic string */
    fprintf(fp, "**\n");

    for (int i = 0; i < 28; i++)
    {
        Main_node *main_temp = table[i].link;

        while (main_temp != NULL)
        {
            fprintf(fp, "#%d;%s;%d;",
                    table[i].index,
                    main_temp->word,
                    main_temp->file_count);

            Sub_node *sub_temp = main_temp->sub_link;

            while (sub_temp != NULL)
            {
                fprintf(fp, "%s;%d;",
                        sub_temp->file_name,
                        sub_temp->word_count);

                sub_temp = sub_temp->next;
            }

            fprintf(fp, "#\n");

            main_temp = main_temp->next;
        }
    }

    fclose(fp);

    printf("Database saved successfully\n");

    return SUCCESS;
}