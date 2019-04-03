// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "dictionary.h"

//create node struct
typedef struct node
{
    char word[45 + 1];
    struct node *next;
}
node;

//create array of pointers
node *hashtable[26];

//implement the key to know what bucket to put word
int first_char (const char *word)
{
    return tolower(word[0]) - 'a';
}



// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // open dictionary
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }

    //set pointers to NULL
    for (int i = 0; i < 26; i++)
    {
        hashtable[i] = NULL;
    }


    while (fscanf(file, "%s", word) != EOF)
    {
        // allocate the pointer, but not the pointee
        int *new_node;

        //malloc space for node
        node *new_node = malloc(sizeof(node));


        if (!new_node)
        {
            unload();
            return false;
        }

        else
        {
            //copy word into node
            strcpy(new_node -> word, word);

            //get first character to know what bucket to put in
            int index = first_char(word);

            //insert into begining of linked list
            new_node -> next = hashtable[index];

            hashtable[index] = new_node;

        }
    }

    //close file
    fclose(file);

    //done :)
    return true;

}