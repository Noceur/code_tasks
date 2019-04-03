#include <stdio.h>
#include <cs50.h>
#include <string.h>

int check_input(string input[])
{
    printf("%s\n", input[1]);
    /*for (int i=0; i<strlen(input[1]);i++)
    {
        printf("%s\n", input[i]);
    }*/
    return 0;
}

int main(int argc, string argv[])
{
    printf("%i\n", argc);
    check_input(argv);
    printf("%s\n", argv[1]);
}