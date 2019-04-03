#include <stdio.h>
#include <stdbool.h>


typedef struct{
    char name;
}letter;


void test(char a)
{
    printf("Address: %p\n", &a);
    a = 'c';
    printf("%c\n", a);
    return;
}

void test2(letter *a)
{
    printf("Address: %p\n", &a);
    a->name = 'c';
    printf("%c\n", a->name);
    return;
}

void load(const char *dictionary)
{
    FILE *dict_fp = fopen(dictionary, "r");
    if(dict_fp == NULL)
    {
        printf("Failed to load dictionary!");
    }
    printf("x\n");
}

int main()
{
    letter c;
    printf("Address: %p\n", &c);
    c.name = 'a';
    test2(&c);
    printf("%c\n", c.name);


    char a = 'b';
    printf("Address: %p\n", &a);
    test(a);
    printf("%c\n", a);


    load("dictionaries/large");

}
