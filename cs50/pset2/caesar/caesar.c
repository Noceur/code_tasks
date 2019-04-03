#include <stdio.h>
#include <cs50.h>
#include <string.h>


int main(int argc, string argv[])
{
    const int lower_low = 'a';
    const int lower_high = 'z';
    const int upper_low = 'A';
    const int upper_high = 'Z';

    if (argc != 2)
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
    else
    {
        string input = get_string("plaintext:  ");
        printf("ciphertext: ");
        for (int i = 0, n = strlen(input); i < n; i++)
        {
            if (input[i] >= lower_low && input[i] <= lower_high)
            {
                char result = (((input[i]+atoi(argv[1])-'a')%26)+'a');
                printf("%c", result);
            }
            else if (input[i] >= upper_low && input[i] <= upper_high)
            {
                char result = (((input[i]+atoi(argv[1])-'A')%26)+'A');
                printf("%c", result);
            }
            else
            {
                printf("%c", input[i]);
            }
        }
        printf("\n");
    }
}