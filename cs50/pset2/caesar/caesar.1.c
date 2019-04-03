#include <stdio.h>
#include <cs50.h>
#include <string.h>

const int lower_low = 'a';
const int lower_high = 'z';
const int upper_low = 'A';
const int upper_high = 'Z';

//Check if all input is either between a-z or A-Z
//Start encrypting

int check_input(string input)
{
    printf("test%s\n", input);
    return true;
}

int main(int argc, string argv[])
{
    if (check_input(argv[]) != true)
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }
}