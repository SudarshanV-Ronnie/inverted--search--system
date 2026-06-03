#include "inverted.h"

// Function to rebuild database from saved file
int update_database(Hash_arr *hash_table)
{
    // If database already created or updated, do not allow update again
    if (create_flag == 1 || update_flag == 1)
    {
        printf("Database already created. Update not allowed\n");
        return FAILURE;
    }

    char filename[100];

    printf("Enter the filename: ");
    scanf("%s", filename);

    // Check file extension
    if (strstr(filename, ".txt") == NULL)
    {
        printf("Invalid file type\n");
        return FAILURE;
    }

    // Open saved database file
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("File not found\n");
        return FAILURE;
    }

    char line[1000];

    // Read magic string
    fgets(line, sizeof(line), fp);

    // Remove newline character
    line[strcspn(line, "\n")] = '\0';

    // Check magic string validity
    if (strcmp(line, "**") != 0)
    {
        printf("Invalid database file\n");
        fclose(fp);
        return FAILURE;
    }

    // Read each database entry line
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // Remove newline
        line[strcspn(line, "\n")] = '\0';

        // Skip empty lines
        if (strlen(line) == 0)
            continue;

        // Remove starting '#'
        char *token = strtok(line + 1, ";");

        // Get hash index
        int index = atoi(token);

        // Get word
        token = strtok(NULL, ";");
        char word[100];
        strcpy(word, token);

        // Get number of files
        token = strtok(NULL, ";");
        int file_count = atoi(token);

        // Create main node
        Main_node *new_main = malloc(sizeof(Main_node));

        new_main->word = malloc(strlen(word) + 1);
        strcpy(new_main->word, word);

        new_main->file_count = file_count;
        new_main->word_length = strlen(word);
        new_main->sub_link = NULL;
        new_main->next = NULL;

        Sub_node *prev = NULL;

        // Read file name and word count pairs
        while ((token = strtok(NULL, ";")) != NULL)
        {
            if (strcmp(token, "#") == 0)
                break;

            char fname[100];
            strcpy(fname, token);

            token = strtok(NULL, ";");
            int wcount = atoi(token);

            // Create sub node
            Sub_node *new_sub = malloc(sizeof(Sub_node));

            new_sub->file_name = malloc(strlen(fname) + 1);
            strcpy(new_sub->file_name, fname);

            new_sub->word_count = wcount;
            new_sub->next = NULL;

            // Attach sub node to main node
            if (new_main->sub_link == NULL)
                new_main->sub_link = new_sub;
            else
                prev->next = new_sub;

            prev = new_sub;
        }

        // Insert main node into hash table
        new_main->next = hash_table[index].link;
        hash_table[index].link = new_main;
    }

    fclose(fp);

    // Mark database as updated
    update_flag = 1;

    printf("Database updated successfully\n");

    return SUCCESS;
}