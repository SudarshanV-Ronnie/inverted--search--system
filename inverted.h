#ifndef INVERTED_H
#define INVERTED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Status macros
#define SUCCESS 1
#define FAILURE 2
#define P_SUCCESS 3

// Global flags declared in main file
extern int update_flag;
extern int create_flag;


/* ---------- Sub Node Structure ---------- */
/* Stores file information for each word */

typedef struct sub_node
{
    int word_count;           // Number of times word appears in a file
    char *file_name;          // File name where word is present
    struct sub_node *next;    // Pointer to next sub node

} Sub_node;


/* ---------- Main Node Structure ---------- */
/* Stores the word and its file details */

typedef struct main_node
{
    char *word;               // Word stored in database
    int file_count;           // Number of files containing this word
    int word_length;          // Length of the word

    Sub_node *sub_link;       // Link to sub node list
    struct main_node *next;   // Pointer to next main node

} Main_node;


/* ---------- Hash Table Structure ---------- */

typedef struct hash_arr
{
    int index;                // Hash index
    Main_node *link;          // Pointer to main node list

} Hash_arr;


/* ---------- File Linked List Structure ---------- */

typedef struct node
{
    char *file_name;          // Name of input file
    struct node *next;        // Pointer to next file node

} Node;


/* ---------- Function Prototypes ---------- */

// Command line argument validation
int cla_validate(int argc, char *argv[], Node **head);

// Create file linked list
int create_file_list(Node **head, char *fname);

// Insert file name at last of list
int insert_last(Node **head, char *fname);

// Print file list
int print_list(Node *head);

// Display entire database
int display_database(Hash_arr *hash_table, int size);

// Create inverted search database
int create_database(Hash_arr *hash_table, Node *head);

// Create main node in hash table
int create_mainNode(Hash_arr *hash_table, int index, char *word, char *filename);

// Search word in database
int search_database(Hash_arr *hash_table, char *word);

// Save database to file
int save_database(Hash_arr *hash_table);

// Update database from saved file
int update_database(Hash_arr *hash_table);

// Check if file already indexed
int is_file_already_indexed(Hash_arr *hash_table, char *filename);

#endif