#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

const int lower_low = 'a';
const int lower_high = 'z';
const int upper_low = 'A';
const int upper_high = 'Z';

//Check if all input is either between a-z or A-Z
//Start encrypting

int check_input(string input)
{
    for (int i = 0,n = strlen(input); i < n; i++)
    {
        if ((input[i] >= lower_low && input[i] <= lower_high) || (input[i] >= upper_low && input[i] <= upper_high))
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }
    else if (check_input(argv[1]) != true)
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }
    else
    {
        string input = get_string("plaintext:  ");
        printf("ciphertext: ");
        int counter = 0;

        for (int i = 0, n = strlen(input); i < n; i++)
        {
            int current = counter%strlen(argv[1]);



            if (input[i] >= lower_low && input[i] <= lower_high)
            {
                int lower = tolower(argv[1][current]);
                char result = (((input[i]+(lower-'a')-'a')%26)+'a');
                printf("%c", result);
                counter++;
            }
            else if (input[i] >= upper_low && input[i] <= upper_high)
            {
                int lower = tolower(argv[1][current]);
                char result = (((input[i]+(lower-'a')-'A')%26)+'A');
                printf("%c", result);
                counter++;
            }
            else
            {
                printf("%c", input[i]);
            }
        }
        printf("\n");
    }
}