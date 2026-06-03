#include "inverted.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Flags to track database status
int update_flag = 0;
int create_flag = 0;

int main(int argc, char *argv[])
{
    Node *file_head = NULL;   // Head pointer for file list

    // Check if files are provided
    if (argc <= 1)
    {
        printf("Please provide input files\n");
        return 0;
    }

    if (argc > 2)
    {
        int status = cla_validate(argc, argv, &file_head);

        if (status == FAILURE)
        {
            printf("Validation failed\n");
            return 1;
        }
        else if (status == P_SUCCESS)
        {
            printf("Some files validation failed\n");
        }

        printf("File nodes --> ");
        print_list(file_head);
    }

    int choice;
    int table_size = 28;

    // Hash table
    Hash_arr hash_table[table_size];

    // Initialize hash table
    for (int i = 0; i < table_size; i++)
    {
        hash_table[i].index = i;
        hash_table[i].link = NULL;
    }

    // Menu driven loop
    do
    {
        printf("\n---- MENU ----\n");
        printf("1. Create database\n");
        printf("2. Display database\n");
        printf("3. Search database\n");
        printf("4. Save database\n");
        printf("5. Update database\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:

            if (create_database(hash_table, file_head) == SUCCESS)
                printf("Database created successfully\n");
            else
                printf("Database creation failed\n");

            break;

        case 2:

            display_database(hash_table, table_size);
            break;

        case 3:
        {
            char search_word[100];

            printf("Enter the word: ");
            scanf("%99s", search_word);

            if (search_database(hash_table, search_word) == FAILURE)
                printf("Word not found\n");

            break;
        }

        case 4:

            if (save_database(hash_table) == FAILURE)
                printf("Saving database FAILED\n");

            break;

        case 5:

            if (update_database(hash_table) == FAILURE)
                printf("Update database FAILED\n");

            break;

        case 6:

            exit(0);

        default:

            printf("Invalid choice\n");
        }

    } while (choice != 6);

    return 0;
}