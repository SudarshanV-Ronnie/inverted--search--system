#include "inverted.h"

// Function to search a word in the inverted search database
int search_database(Hash_arr *hash_table, char *word)
{
    int index;

    // Find hash index based on first character of word
    if (word[0] >= 'A' && word[0] <= 'Z')
        index = word[0] - 'A';
    else if (word[0] >= 'a' && word[0] <= 'z')
        index = word[0] - 'a';
    else if (isdigit(word[0]))
        index = 26;
    else
        index = 27;

    // Get main node list from calculated index
    Main_node *main_temp = hash_table[index].link;

    // Traverse main node list
    while (main_temp != NULL)
    {
        // Check if word matches
        if (strcmp(main_temp->word, word) == 0)
        {
            printf("-------------------------------------------------------------\n");
            printf("WORD FOUND:\n");

            printf("File count = %d\n", main_temp->file_count);

            Sub_node *sub_temp = main_temp->sub_link;

            // Traverse sub nodes to print file details
            while (sub_temp != NULL)
            {
                printf("File name: %s , Word count = %d\n",
                       sub_temp->file_name,
                       sub_temp->word_count);

                sub_temp = sub_temp->next;
            }

            printf("-------------------------------------------------------------\n");

            return SUCCESS;
        }

        // Move to next main node
        main_temp = main_temp->next;
    }

    return FAILURE;
}