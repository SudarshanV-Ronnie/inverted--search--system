#include "inverted.h"

// Function to create file list from validated files
int create_file_list(Node **head, char *fname)
{
    // Insert filename at end of linked list
    if (insert_last(head, fname) == FAILURE)
    {
        printf("Insert operation failed\n");
        return FAILURE;
    }

    return SUCCESS;
}