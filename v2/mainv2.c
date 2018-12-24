#include <stdio.h>
#include <string.h>
#include <math.h>
#include "calculatorv2.h"

int panjangKata;

int main()
{
    boolean valid;
    int idx;
    double complex res;
    char s[50];

    // ALGORTIMA
    printf(" ██████╗ █████╗ ██╗      ██████╗██╗   ██╗███╗   ███╗ █████╗ ███╗   ██╗██╗ █████╗ \n");
    printf("██╔════╝██╔══██╗██║     ██╔════╝██║   ██║████╗ ████║██╔══██╗████╗  ██║██║██╔══██╗\n");
    printf("██║     ███████║██║     ██║     ██║   ██║██╔████╔██║███████║██╔██╗ ██║██║███████║\n");
    printf("██║     ██╔══██║██║     ██║     ██║   ██║██║╚██╔╝██║██╔══██║██║╚██╗██║██║██╔══██║\n");
    printf("╚██████╗██║  ██║███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║██║  ██║██║ ╚████║██║██║  ██║\n");
    printf(" ╚═════╝╚═╝  ╚═╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝\n");
    printf("                                                          v.2 with complex number\n");                                                                                                                                                                                          
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
            if (isnan(creal(res)) || isinf(creal(res)) || isnan(cimag(res)) || isinf(cimag(res))){
                printf("MATH ERROR");
            }
            else{
                if (cimag(res)<=0.001 && cimag(res)>=-0.001){
                    printf("%.2f", creal(res));
                }else if (creal(res)<=0.001 && creal(res)>=-0.001){
                    printf("%.2fi", cimag(res));
                }else{
                    printf("%.2f%+.2fi", creal(res), cimag(res));
                }
            }
        }else{
            printf("SINTAKS ERROR");
        }
        printf("\n");
        printf("Enter an expression : \n");
        scanf("%s", s);
    }
    printf("\nCREDIT : \n");
    printf("Abda Shaffan Diva 13517021\n");
    printf("Juniardi Akbar 13517075\n");
    printf("Faiz Muhammad Muflich 13517093\n");

    return 0;
}