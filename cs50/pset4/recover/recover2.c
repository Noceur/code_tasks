#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

void close_file(FILE **f){
    fclose(*f);
    if(*f == NULL){
        printf("File closed.\n");
    }
}

int open_file(char *name, FILE **f, char *mode){
    *f = fopen(name, mode);
    if (f == NULL){
        printf("empty");
        return 1;
    }
    return 0;
}

int write_file(){
    return 0;
}

int check_bytes(){
    return 0;
}

int main(int argc, char *argv[]){
    FILE* f;
    int size;
    uint8_t buffer[512];
    uint8_t counter = 0;
    uint8_t counter2 = 0;
    bool start_writing = false;

    if(open_file(argv[1], &f, "r") == 0){
        printf("opened successfully\n");

        fseek(f, 0, SEEK_END);
        size = ftell(f);
        printf("Size: %i\n", size);
        fseek(f, 0, SEEK_SET);






        while (fread(buffer, sizeof(buffer), 1, f) == 1){
        //fread(buffer, 1, sizeof(buffer), f);
        //printf("%x%x%x\n", buffer, buffer[1], buffer[20]);
            counter2++;
            printf("%i", counter2);
            //fseek(f, 1, SEEK_SET);
            //fread(buffer, sizeof(buffer), 1, f);
            //printf("%x%x\n", buffer[0], buffer[1]);
            //printf("%p\n", &buffer+counter);
            //counter++;
            //printf("%i\n", counter);
            //printf("%x%x\n", buffer[0], buffer[1]);
            if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] <= 0xf0 && buffer[3] >= 0xe0)){
                start_writing = true;
                counter++;
                printf("FOUND EM! - %i\n", counter);

                //printf("%p\n", &buffer+counter);
                //volatile unsigned int *p = (volatile unsigned int *)&buffer+counter;
                //printf("%x\n", *p);
                //uint8_t *ptr;
                //ptr = &buffer+counter;
                //printf("%p\n", &ptr);

            }
            if(start_writing == true){
                //TODO write to file
            }
            //printf("%x ", *buffer);
            //printf("\n%x%x%x%x\n", buffer[0], buffer[1], buffer[2], buffer[3]);

        }
        //printf("\n%x%x%x%x\n", buffer[0], buffer[1], buffer[2], buffer[3]);
    }
    return 0;
}