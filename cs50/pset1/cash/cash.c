#include <stdio.h>
#include <cs50.h>
#include <math.h>

int validate_input(float input)
{
    if(input<0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int validate_sub(float input, float coin)
{
    if((input-coin)>=0)
    {
        return true;
    }

    else
    {
        return false;
    }
}

int convert_to_cents(float input)
{
    int output = (int)round(input*100);
    return output;
}

int return_coins(int input)
{
    const int quarter = 25;
    const int dime = 10;
    const int nickel = 5;
    const int penny = 1;

    int coin_count = 0;

    while(input != 0)
    {
        if(validate_sub(input, quarter))
        {
            input -= quarter;
            coin_count++;
            continue;
        }
        if(validate_sub(input, dime))
        {
            input -= dime;
            coin_count++;
            continue;
        }
        if(validate_sub(input, nickel))
        {
            input -= nickel;
            coin_count++;
            continue;
        }
        if(validate_sub(input, penny))
        {
            input -= penny;
            coin_count++;
            continue;
        }
    }
    return coin_count;
}

int main(void)
{
    bool exit = false;

    while(exit == false)
    {
        float input = get_float("Change owed: ");
        if(validate_input(input))
        {
            printf("%i coins.\n", return_coins(convert_to_cents(input)));
            exit = true;
        }

    }
}

