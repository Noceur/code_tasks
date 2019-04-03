#include <stdio.h>
#include <stdlib.h>

void double_test(int *test){
    *test *= 2;
}

int main(int argc, char *argv[]){
    int a = 10;
    double_test(&a);
    printf("%i", a);
    return 0;
}