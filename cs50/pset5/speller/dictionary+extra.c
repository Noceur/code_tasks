// Implements a dictionary's functionality

#include <stdbool.h>
#include "dictionary.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define UNUSED(x) (void)(x)

const int ABC_SIZE = 26;
const int CASE = 'a';
int n_words = 0;

typedef struct Node{
    char name_;
    bool complete_;
    struct Node *parent_;
    struct Node *child_[ABC_SIZE];
}Node;

Node *root;

Node *create_zero_node()
{
    Node *ptr = malloc(sizeof(Node));
    memset(ptr, '\0', sizeof(Node));
    /*ptr->name_ = '\0';
    ptr->complete_ = false;
    ptr->parent_ = NULL;
    for(int i = 0; i >= ABC_SIZE; i++)
    {
        ptr->child_[i] = NULL;
    }*/
    return ptr;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    Node *currentNode = root;
    int index;
    for(int i = 0; word[i] != '\0'; i++)
    {
        index = tolower(word[i])-CASE;
        if(index >= 0 && index <= 25)
        {
            currentNode = currentNode->child_[index];
            //printf(("%c"), currentNode->name_);
        }
    }
    if(currentNode->complete_ == true)
    {
        return true;
    }
    else
    {
        return false;
    }

}



// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    root = create_zero_node();
    Node *currentNode = root;
    FILE *dict_fp = fopen(dictionary, "r");
    //int line = 0;

    if(dict_fp == NULL)
    {
        printf("Failed to load dictionary!");
        return false;
    }

    char x = fgetc(dict_fp);
    while(x != EOF)
    {
        if(x != '\n')
        {
            int index = tolower(x)-CASE;
            if(index >= 0 && index <= 25)
            {
                if(currentNode->child_[index] == NULL)
                {
                    currentNode->child_[index] = create_zero_node();
                    currentNode->child_[index]->parent_ = currentNode;
                    currentNode = currentNode->child_[index];
                    currentNode->name_ = x;
                }
                else
                {
                    currentNode = currentNode->child_[index];
                }
            //printf("%c", currentNode->name_);
            //printf("%i", index);
            }

        }
        else
        {
            n_words++;
            currentNode->complete_ = true;
            currentNode = root;
            //printf("\n");
            //printf("%i - ", line);
            //line++;
        }
        x = fgetc(dict_fp);
    }

    fclose(dict_fp);
    //printf("%i\n", n_words);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return n_words;
}

void rec_unloader(Node *currentNode)
{
    for (int i = 0; i < 26; i++)
    {
        if(currentNode->child_[i] != NULL)
        {
            rec_unloader(currentNode->child_[i]);
        }
    }
    free(currentNode);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if(!root)
    {
        return false;
    }
    rec_unloader(root);
    return true;
}