#include "calculator.h"
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

void Calculate(char *st, int *idx, double *result, boolean *valid) {
    // KAMUS LOKAL
    double temp;

    //ALGORITMA
    //printf("Awal Calculate %d %.2f %d\n", *valid, *result, *idx);
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
                //printf("Calculate %d %.2f %d\n", *valid, *result, *idx);
            }
            //printf("%c %d", st[*idx], isSymbol(st[*idx]));
            if (isSymbol(st[*idx]) || isNumber(st[*idx])){
                ///printf(" CEK ");
                *valid = false;
            }
            //printf(" %d\n", *valid);
        }
    } else {
        return;
    }
    //printf("Akhir Calculate %d %.2f %d\n", *valid, *result, *idx);
}

void TimesDiv(char* st, int* idx, double* result, boolean *valid) {
    //KAMUS LOKAL
    double temp;
    
    //ALGORITMA
    //printf(" Awal TimesDiv %d %.2f %d\n", *valid, *result, *idx);
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
                //printf(" TimesDiv %d %.2f %d\n", *valid, *result, *idx);
            //}
        }
    }
    //printf(" Akhir TimesDiv %d %.2f %d\n", *valid, *result, *idx);
}

void power(char* st, int* idx, double* result, boolean *valid)
{
    //KAMUS LOKAL
    double temp = 0;
     //ALGORTIMA
    //printf("  Awal Power %d %.2f %d\n", *valid, *result, *idx);
    *valid = false;
    Sign(st, idx, result, valid);
    if(*valid) {
        if(st[*idx] == '^') {
            (*idx)++;
            //printf("%.2f\n", *result);
            *valid = false;
            if (st[*idx] != '-'){
                power(st,idx,&temp,valid);
                (*result) = pow((*result),temp);
                //printf("  Power %d %.2f %d\n", *valid, *result, *idx);
            }
        }
    }
    //printf("  Akhir Power %d %.2f %d\n", *valid, *result, *idx);
}

void Sign(char* st,int* idx, double* result, boolean *valid)
{
    //KAMUS LOKAL
    double temp = 0;
    int x = 1;

    //ALGORITMA
    //printf("   Awal Sign %d %.2f %d\n", *valid, *result, *idx);
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
            *valid = false;
            if (st[*idx-1] != '-'){
                (*idx)++;
                x = -1;
                power(st,idx,result,valid);
                if (*valid){
                    *result *= x;
                    *valid = true;
                }
            }
        }
        if (isNumber(st[*idx])){
            Number(st,idx,result);
            if (st[*idx] == '.'){
                (*idx)++;
                doubleNumber(st,idx,&temp);
            }
            *result = ((*result)+temp);
            temp = 0;
            *valid = true;
        }
    }
    //printf("   Akhir Sign %d %.2f %d\n", *valid, *result, *idx);
    if (isSymbol(st[*idx] || isNumber(st[*idx]))){
        *valid = false;
    }
}

//-2^2 = -4 || -(2^2) != (-2)^2
//-2*4 = -8 || -(2*4) == (-2)*4

// 3-((4*5)6)

void Number(char* st,int* idx, double* result)
{
    if (!isNumber(st[*idx]))
        return;
    else
    {
        *result = ((*result)*10)+((double)st[*idx]-(double)'0');
        (*idx)++;
        Number(st,idx,result);
    }
}

void doubleNumber(char* st,int* idx, double* result)
{
    //KAMUS LOKAL
    double n;
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