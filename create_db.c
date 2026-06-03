#include "inverted.h"

/* Check if a file is already present in the database */
int is_file_already_indexed(Hash_arr *hash_table, char *filename)
{
    // Traverse every hash index
    for (int i = 0; i < 28; i++)
    {
        Main_node *mtemp = hash_table[i].link;

        // Traverse main node list
        while (mtemp != NULL)
        {
            Sub_node *stemp = mtemp->sub_link;

            // Traverse sub node list
            while (stemp != NULL)
            {
                // If filename matches return success
                if (strcmp(stemp->file_name, filename) == 0)
                    return SUCCESS;

                stemp = stemp->next;
            }

            mtemp = mtemp->next;
        }
    }

    return FAILURE;
}


/* Create the inverted search database */
int create_database(Hash_arr *hash_table, Node *file_head)
{
    if (file_head == NULL)
    {
        printf("No files are available from command line to create database\n");
        return FAILURE;
    }

    int new_file_flag = 0;

    // Traverse file list
    while (file_head != NULL)
    {
        // Skip if file already indexed
        if (is_file_already_indexed(hash_table, file_head->file_name) == SUCCESS)
        {
            file_head = file_head->next;
            continue;
        }

        FILE *fp = fopen(file_head->file_name, "r");

        if (fp == NULL)
            return FAILURE;

        char word[100];

        // Read words from file
        while (fscanf(fp, "%s", word) == 1)
        {
            int index;

            // Decide hash index based on first character
            if (word[0] >= 'A' && word[0] <= 'Z')
                index = word[0] - 'A';
            else if (word[0] >= 'a' && word[0] <= 'z')
                index = word[0] - 'a';
            else if (isdigit(word[0]))
                index = 26;
            else
                index = 27;

            // Create or update main node
            if (create_mainNode(hash_table, index, word, file_head->file_name) == FAILURE)
            {
                fclose(fp);
                return FAILURE;
            }
        }

        fclose(fp);

        new_file_flag = 1;

        file_head = file_head->next;
    }

    if (new_file_flag == 0)
    {
        printf("No new files found to add into database\n");
        return SUCCESS;
    }

    create_flag = 1;

    return SUCCESS;
}


/* Create main node or update existing node */
int create_mainNode(Hash_arr *hash_table, int index, char *word, char *filename)
{
    // If hash index empty create new main node
    if (hash_table[index].link == NULL)
    {
        Main_node *new_main = malloc(sizeof(Main_node));

        if (new_main == NULL)
            return FAILURE;

        new_main->word = malloc(strlen(word) + 1);

        if (new_main->word == NULL)
        {
            free(new_main);
            return FAILURE;
        }

        strcpy(new_main->word, word);

        new_main->file_count = 1;
        new_main->word_length = strlen(word);
        new_main->next = NULL;

        // Create sub node
        Sub_node *new_sub = malloc(sizeof(Sub_node));

        if (new_sub == NULL)
        {
            free(new_main->word);
            free(new_main);
            return FAILURE;
        }

        new_sub->file_name = malloc(strlen(filename) + 1);

        if (new_sub->file_name == NULL)
        {
            free(new_sub);
            free(new_main->word);
            free(new_main);
            return FAILURE;
        }

        strcpy(new_sub->file_name, filename);

        new_sub->word_count = 1;
        new_sub->next = NULL;

        new_main->sub_link = new_sub;

        hash_table[index].link = new_main;

        return SUCCESS;
    }

    // Traverse main node list
    Main_node *mtemp = hash_table[index].link;
    Main_node *prev = NULL;

    while (mtemp != NULL)
    {
        // If word already exists
        if (strcmp(mtemp->word, word) == 0)
        {
            Sub_node *stemp = mtemp->sub_link;

            // Check if file already present
            while (stemp != NULL)
            {
                if (strcmp(stemp->file_name, filename) == 0)
                {
                    stemp->word_count++;
                    return SUCCESS;
                }

                stemp = stemp->next;
            }

            // Create new sub node for new file
            Sub_node *new_sub = malloc(sizeof(Sub_node));

            if (new_sub == NULL)
                return FAILURE;

            new_sub->file_name = malloc(strlen(filename) + 1);

            if (new_sub->file_name == NULL)
            {
                free(new_sub);
                return FAILURE;
            }

            strcpy(new_sub->file_name, filename);

            new_sub->word_count = 1;

            new_sub->next = mtemp->sub_link;

            mtemp->sub_link = new_sub;

            mtemp->file_count++;

            return SUCCESS;
        }

        prev = mtemp;

        mtemp = mtemp->next;
    }

    // Word not present create new main node
    Main_node *new_main = malloc(sizeof(Main_node));

    if (new_main == NULL)
        return FAILURE;

    new_main->word = malloc(strlen(word) + 1);

    if (new_main->word == NULL)
    {
        free(new_main);
        return FAILURE;
    }

    strcpy(new_main->word, word);

    new_main->file_count = 1;
    new_main->word_length = strlen(word);
    new_main->next = NULL;

    // Create first sub node
    Sub_node *new_sub = malloc(sizeof(Sub_node));

    if (new_sub == NULL)
    {
        free(new_main->word);
        free(new_main);
        return FAILURE;
    }

    new_sub->file_name = malloc(strlen(filename) + 1);

    if (new_sub->file_name == NULL)
    {
        free(new_sub);
        free(new_main->word);
        free(new_main);
        return FAILURE;
    }

    strcpy(new_sub->file_name, filename);

    new_sub->word_count = 1;
    new_sub->next = NULL;

    new_main->sub_link = new_sub;

    prev->next = new_main;

    return SUCCESS;
}