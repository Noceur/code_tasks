#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *f;
    FILE *i;
    int size;
    uint8_t buffer[512];
    char iname[2048];
    char iname2[2048];
    int icounter = 1;
    char x[64]="./test/\0";

    uint8_t counter = 0;
    uint8_t counter2 = 0;
    bool start_writing = false;
    char *filename;

    if((f = fopen(argv[1], "r")) != NULL){

        while (fread(buffer, sizeof(buffer), 1, f) == 1){

            if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] <= 0xf0 && buffer[3] >= 0xe0)){
                if(start_writing == true){
                    fclose(i);
                    icounter++;
                }


                start_writing = true;
                char fn[255];
                char hold[255];
                strcpy(fn, "./test/");
                sprintf(hold, "%03i.jpg", icounter);
                strcat(fn, hold);
                //sprintf(iname, strcat("%03i.jpg\0", "./test/\0"), icounter);
                printf("%s\n", fn);
                i = fopen(fn, "w");

            }
            if(start_writing == true){
                fwrite(buffer, 1, sizeof(buffer), i);
            }

        }
    }
    return 0;
}