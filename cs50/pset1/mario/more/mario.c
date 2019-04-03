#include <stdio.h>
#include <cs50.h>

int validate_input(int input)
{
    if(input<0 || input>23){
        return false;
    }
    else{
        return true;
    }
}

int pyramid(int input)
{
    int height = input-1;

    for(int i = 0; i<height+1; i++){
        printf("%.*s", height-(i), "                        ");
        printf("%.*s", i+1, "#############################");
        printf("  %.*s\n", i+1, "#############################");
    }
    return 0;
}

int main(void)
{
    bool exit = false;

    while(exit == false){
        int input = get_int("Height: ");
        if(validate_input(input)){
            printf("%i is a valid input\n", input);
            pyramid(input);
            exit = true;
        }
    }
}