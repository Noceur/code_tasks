#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

const int ALPHABET_SIZE = 26;
const int CASE = 'a';

//https://github.com/raju249/CS50/blob/master/pset5/pset5/dictionary.c
//https://www.youtube.com/watch?v=_vSJOl4LiEU

typedef struct Node
{
    char name;
    struct Node *parent_;
    struct Node *children_[ALPHABET_SIZE];
    int occurences_;
}Node;

void InsertNode(Node *trieTree, char *word)
{
    printf("Address: %p\n", &trieTree);
    Node *currentNode = trieTree;

    while (*word != '\0')
    {
        *word = tolower(*word);
        Node *child = currentNode->children_[*word-CASE];
        if (child==NULL)
        {
            child = calloc(0, sizeof(Node));
            child->name = *word;
            //child->children_ = {NULL};
            //child->parent_ = NULL;
            //memset(&child, 0, sizeof(child));
            //child->name = *word;

            child->parent_ = currentNode;
        }

        currentNode = child;
        printf("letter-'%c': %i\n", *word, *word-CASE);
        word++;
    }
    currentNode->occurences_++;
    return;
}


int main(int argc, char *argv[])
{
    if(argc!=0)
    {
        Node root;
        memset(&root, 0, sizeof(root));
        root.occurences_ = 0;
        char *test = "test";
        //printf("%i\n", root.occurences_);
        //InsertNode(&root, "Hello");
        printf("Address: %p\n", &root);
        InsertNode(&root, argv[1]);
        InsertNode(&root, test);

        int i = 0;
        //printf("%i\n", ALPHABET_SIZE);
        //for(int i = 0; i<ALPHABET_SIZE; i++)
        while(ALPHABET_SIZE>i)
        {
            printf("%c\n", root.name);
            //printf("%c\n", argv[1][i]);
            /*if(root.children_[argv[1][i]] != NULL)
            {
                printf("bork\n");
            }*/
            i++;
        }
    }
}























/*int main(int argc, char *argv[])
{
    struct Node test2;
    test2.occurences_ = 0;
    printf("%i wubwubwub\n", test2.occurences_);
    //argv[0] = "a";
    if(argc != 0)
    {
        printf("%s\n", argv[1]);
        int test = atoi(argv[1]);
        printf("%d\n", test);
        printf("ASCII value of %c = %i\n", argv[1][0], argv[1][0]-CASE);
        //char result = atoi(argv[1]);
        //printf("%i", CASE-argv[0][0]);
        //printf("%i", atoi(argv[0][0]));
        printf("case to number%i\n", (atoi(argv[1]))-CASE);
    }

    InsertNode(&test2, argv[1]);
}*/