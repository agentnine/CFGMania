#include <stdio.h>
#include <string.h>
#include "Calculated.h"

int panjangKata;

int main(int argc, char *argv[])
{
    boolean valid;
    int idx;
    float res;

    if(argc >= 2) {
        char * v = "-v";
        char * v2 = "--version";
        char * h = "-h";
        if(strcmp(argv[1],h) == 0) {
            printf("usage: calc [arguments1] [arguments2] ... \n");
            printf("Arguments :\n");
            printf("-h \t\t\t\t Show help like this\n");
            printf("[strings1] .. [stringsN]\t String like '1+2' that will give you answer 3\n");
            printf("--version -v \t\t\t Show the version of program\n");
        } else if(strcmp(argv[1],v) == 0 || strcmp(argv[1],v2) == 0) {
            printf("Calculated 0.1 (2016 Nov 20)\n");
            printf("Made by Ray Andrew and Winarto\n");
            printf("This application made to completed the Theory of Formal Language and Automata\n");
            printf("Opensource at https://www.github.com/ironlota/Calculated\n");
            printf("Informatics Engineering Institute Technology of Bandung 2016\n");
        }
         else {
            for (int i = 1; i < argc; i++) {
                valid = true;
                res = 0;
                idx = 0;
                panjangKata = strlen(argv[i]);
                Calculate(argv[i], &idx, &res, &valid);
                if (valid)
                    printf("%.2f",res);
                else
                   printf("SINTAKS ERROR");

                printf("\n");
            }
        }
        return 0;
    } else {
        char s[50];
        valid = true;
        idx = 0;
        scanf("%s", s);
        panjangKata = strlen(s);
        Calculate(s, &idx, &res, &valid);
        if (valid)
            printf("%.2f",res);
        else
            printf("SINTAKS ERROR");

        return 0;
    }
}