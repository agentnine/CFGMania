#include <stdio.h>
#include <string.h>
#include <math.h>
#include "calculatorv1.h"

int panjangKata;

int main(int argc, char *argv[])
{
    boolean valid;
    int idx;
    double res;
    char s[50];

    // ALGORTIMA
    printf(" ██████╗ █████╗ ██╗      ██████╗██╗   ██╗███╗   ███╗ █████╗ ███╗   ██╗██╗ █████╗ \n");
    printf("██╔════╝██╔══██╗██║     ██╔════╝██║   ██║████╗ ████║██╔══██╗████╗  ██║██║██╔══██╗\n");
    printf("██║     ███████║██║     ██║     ██║   ██║██╔████╔██║███████║██╔██╗ ██║██║███████║\n");
    printf("██║     ██╔══██║██║     ██║     ██║   ██║██║╚██╔╝██║██╔══██║██║╚██╗██║██║██╔══██║\n");
    printf("╚██████╗██║  ██║███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║██║  ██║██║ ╚████║██║██║  ██║\n");
    printf(" ╚═════╝╚═╝  ╚═╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝\n");
    printf("                                                            v.1 clasic calculator\n");                                                                                                                                                                                          
    printf("                                         IF 2220 TEORI BAHASA FORMAL DAN AUTOMATA\n");                                                                                                                                                                                          
    printf("Enter an expression : \n");
    scanf("%s", s);
    while (strcmp(s,"exit") != 0){
        valid = false;
        idx = 0;
        res = 0+0*I;
        panjangKata = strlen(s);
        Expression(s, &idx, &res, &valid);
        if (valid){
            if (isnan(res) || isinf(res)){
                printf("MATH ERROR");
            }
            else{
                printf("%.2f", res);
            }
        }else{
            printf("SINTAKS ERROR");
        }
        printf("\n");
        printf("Enter an expression : \n");
        scanf("%s", s);
    }
    printf("CREDIT : \n");
    printf("Abda Shaffan Diva 13517021\n");
    printf("Juniardi Akbar 13517075\n");
    printf("Faiz Muhammad Muflich 13517093\n");

    return 0;
}