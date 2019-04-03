#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

void close_file(FILE **f){
    fclose(*f);
    if(*f == NULL){
        printf("File closed.\n");
    }
}

int open_file(char *name, FILE **f, char *mode){
    *f = fopen(name, mode);
    if (*f == NULL){
        printf("Usage: ./recover image\n");
        return 1;
    }
    return 0;
}

int write_to_file(uint8_t buffer[512], int size, FILE **f){
    fwrite(buffer, 1, size, *f);
    return 0;
}

bool check_for_jpeg(uint8_t buffer[512]){
    if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] <= 0xf0 && buffer[3] >= 0xe0)){
        return true;
    }
    else{
        return false;
    }
}

void create_filename(char fn[255], int fncounter){
    char hold[255];
    strcpy(fn, "./");
    sprintf(hold, "%03i.jpg", fncounter);
    strcat(fn, hold);
    printf("%s\n", fn);
}


int main(int argc, char *argv[]){
    FILE *f;
    FILE *i;
    uint8_t buffer[512];
    int fncounter = 1;
    char fn[255];
    bool start_writing = false;

    if(open_file(argv[1], &f, "r") == 0){

        while (fread(buffer, sizeof(buffer), 1, f) == 1){

            if(check_for_jpeg(buffer) == true){
                if(start_writing == true){
                    close_file(&i);
                    fncounter++;
                }
                start_writing = true;
                create_filename(fn, fncounter);
                open_file(fn, &i, "w");


            }
            if(start_writing == true){
                write_to_file(buffer,sizeof(buffer), &i);
            }

        }
    }
    else{
        return 1;
    }
    return 0;
}