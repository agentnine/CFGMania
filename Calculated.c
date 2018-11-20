#include "Calculated.h"
#include <math.h>
#include <stdio.h>
/*
S -> T | S+T | S-T calculate
T -> F | T*F | T/F timesdiv
F -> (S) | -A | A | A.A | -A.A sign
A -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | AA number
*/

boolean isNumber(char st) {
    return (st >= '0') && (st <='9');
}

boolean isSymbol(char st) {
    return (st == '.') || (st == '(') || (st == ')') || (st == '+') || (st == '-') ||(st == '*') ||(st == '/');
}

void Calculate(char *st, int *idx, float *result, boolean *valid) {
    // KAMUS LOKAL
    float temp;

    //ALGORITMA
    printf("Awal Calculate %d %.2f %d\n", *valid, *result, *idx);
    if (*idx < panjangKata){
        TimesDiv(st, idx, result,valid);
        if (*valid){
            while ((st[*idx] == '+' || st[*idx] == '-') && *valid){
                *valid = false;
                if (st[*idx] == '+'){
                    (*idx)++;
                    if (st[*idx] != '-'){
                        TimesDiv(st,idx,&temp,valid);
                        if (*valid){
                            *result += temp;
                            temp = 0;
                            *valid = true;
                        }
                    }
                } else if (st[*idx] == '-'){
                    (*idx)++;
                    if (st[*idx] != '-'){
                        TimesDiv(st,idx,&temp,valid);
                        if (*valid){
                            *result -= temp;
                            temp = 0;
                            *valid = true;
                        }
                    }
                }
                printf("Calculate %d %.2f %d\n", *valid, *result, *idx);
            }
            if (isSymbol(st[*idx])){
                *valid = false;
            }
        }
    } else {
        return;
    }
    printf("Akhir Calculate %d %.2f %d\n", *valid, *result, *idx);
}

void TimesDiv(char* st, int* idx, float* result, boolean *valid) {
    //KAMUS LOKAL
    float temp;
    
    //ALGORITMA
    printf(" Awal TimesDiv %d %.2f %d\n", *valid, *result, *idx);
    power(st,idx,result,valid);
    //Sign(st,idx,result,valid);
    if (*valid){
        while ((st[*idx] == '*' || st[*idx] == '/') && *valid){
            *valid = false;
            //if ((*idx)+1 == panjangKata){
            //  *valid = false;
            //} else{
                if (st[*idx] == '*'){
                    (*idx)++;
                    if (st[*idx] != '-'){
                        power(st,idx,&temp,valid);
                        if (*valid){
                            (*result) *= temp;
                            temp = 0;
                            *valid = true;
                        }
                    }
                } else if (st[*idx] == '/'){
                    (*idx)++;
                    if (st[*idx] != '-'){
                        power(st,idx,&temp,valid);
                        if (*valid){
                            (*result) /= temp;
                            temp = 0;
                            *valid = true;
                        }
                    }
                }
                printf(" TimesDiv %d %.2f %d\n", *valid, *result, *idx);
            //}
        }
    }
    printf(" Akhir TimesDiv %d %.2f %d\n", *valid, *result, *idx);
}

void power(char* st, int* idx, float* result, boolean *valid)
{
    //KAMUS LOKAL
    float temp = 0;
     //ALGORTIMA
    printf("  Awal Power %d %.2f %d\n", *valid, *result, *idx);
    *valid = false;
    Sign(st, idx, result, valid);
    if(*valid) {
        if(st[*idx] == '^') {
            (*idx)++;
            *valid = false;
            if (st[*idx] != '-'){
                power(st,idx,&temp,valid);
                (*result) = pow((*result),temp);
                printf("  Power %d %.2f %d\n", *valid, *result, *idx);
            }
        }
    }
    printf("  Akhir Power %d %.2f %d\n", *valid, *result, *idx);
}

void Sign(char* st,int* idx, float* result, boolean *valid)
{
    //KAMUS LOKAL
    float temp = 0;
    int x = 1;

    //ALGORITMA
    printf("   Awal Sign %d %.2f %d\n", *valid, *result, *idx);
    if(st[*idx] == '('){
        (*idx)++;
        Calculate(st,idx,result,valid);
        *valid = false;
        if (st[*idx] == ')'){
            (*idx)++;
            *valid = true;
        }
        //else print error
    } else{
        if (st[*idx] == '-'){
            (*idx)++;
            x = -1;
        }
        if (isNumber(st[*idx])){
            Number(st,idx,result);
            if (st[*idx] == '.'){
                (*idx)++;
                FloatNumber(st,idx,&temp);
            }
            *result = ((*result)+temp)*x;
            temp = 0;
            *valid = true;
        } else if (st[*idx] == '('){
            (*idx)++;
            Calculate(st,idx,result,valid);
            if (st[*idx] == ')'){
                *result = (*result)*x;
                temp = 0;
                (*idx)++;
                *valid = true;
            }
            //else print error                
        }
    }
    printf("   Akhir Sign %d %.2f %d\n", *valid, *result, *idx);
}



// 3-((4*5)6)

void Number(char* st,int* idx, float* result)
{
    if (!isNumber(st[*idx]))
        return;
    else
    {
        *result = ((*result)*10)+((float)st[*idx]-(float)'0');
        (*idx)++;
        Number(st,idx,result);
    }
}

void FloatNumber(char* st,int* idx, float* result)
{
    //KAMUS LOKAL
    float n;
    int id = *idx;

    //ALGORITMA
    Number(st, &id, &n);
    while(isNumber(st[*idx]))
    {
        n /= 10;
        (*idx)++;
    }
    *result = n;
    n = 0;
}