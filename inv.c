#include "inverted.h"

/* Function to insert file name at the end of linked list */
int insert_last(Node **head, char *fname)
{
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
        return FAILURE;

    /* allocate memory for file name */
    int len = strlen(fname);
    new_node->file_name = malloc(len + 1);

    if (new_node->file_name == NULL)
    {
        free(new_node);
        return FAILURE;
    }

    strcpy(new_node->file_name, fname);

    /* next pointer initially NULL */
    new_node->next = NULL;

    /* if list empty */
    if (*head == NULL)
    {
        *head = new_node;
        return SUCCESS;
    }

    /* move to last node */
    Node *temp = *head;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    /* attach new node */
    temp->next = new_node;

    return SUCCESS;
}


/* Function to print file list */
int print_list(Node *head)
{
    if (head == NULL)
        return FAILURE;

    Node *temp = head;

    while (temp != NULL)
    {
        printf("%s ", temp->file_name);
        temp = temp->next;
    }

    printf("\n");

    return SUCCESS;
}