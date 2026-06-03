#include "inverted.h"

// Function to display entire inverted search database
int display_database(Hash_arr *hash_table, int size)
{
    // Check if table is valid
    if (hash_table == NULL || size == 0)
        return FAILURE;

    printf("--------------------------------------------------------------------------------\n");
    printf("%-10s %-15s %-10s %-20s %-10s\n", "Index", "Word", "F_count", "F_name", "W_count");
    printf("--------------------------------------------------------------------------------\n");

    // Traverse each hash index
    for (int i = 0; i < size; i++)
    {
        if (hash_table[i].link == NULL)
            continue;

        Main_node *main_temp = hash_table[i].link;

        // Traverse main node list
        while (main_temp != NULL)
        {
            printf("%-10d %-15s %-10d ",
                   hash_table[i].index,
                   main_temp->word,
                   main_temp->file_count);

            Sub_node *sub_temp = main_temp->sub_link;

            // Traverse sub node list
            while (sub_temp != NULL)
            {
                printf("%-20s %-10d",
                       sub_temp->file_name,
                       sub_temp->word_count);

                sub_temp = sub_temp->next;

                // Print alignment for multiple files
                if (sub_temp)
                    printf("\n%-10s %-15s %-10s ", "", "", "");
            }

            main_temp = main_temp->next;

            printf("\n");
        }
    }

    printf("--------------------------------------------------------------------------------\n");

    return SUCCESS;
}