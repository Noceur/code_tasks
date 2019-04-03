#include <stdio.h>
#include <stdlib.h>

int myfunction(char* fileName, FILE** readFile) /* pointer pointer to allow pointer to be changed */
{
    if(( *readFile = fopen(fileName,"r")) == NULL)
    {
        return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    FILE* openReadFile; /* This needs to be a pointer. */
    int size;
    if(myfunction(argv[1], &openReadFile) != 0) /* allow address to be updated */
    {
        printf("\n %s : ERROR opening file. \n", __FUNCTION__);
    }
    fseek(openReadFile, 0, SEEK_END);
    size = ftell(openReadFile);
    printf("\n%i\n", size);
}