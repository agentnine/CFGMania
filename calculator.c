#include "calculator.h"
#include <math.h>
#include <stdio.h>
/*
S -> T1 | S+T1 | S-T2 Expression
T1 -> P1 | T1*P1 | T1/P1 Term
T2 -> P2 | T2+P2 | T2/P2
P1 -> F1 | F1^P2 Power
P2 -> F2 | F2^P2 Power
F1 -> (S) | -P1 | A Item
F2 -> (S) | (-P2) | A Item
A -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A.A | AA number
*/

boolean isNumber(char token) {
    return (token >= '0') && (token <='9');
}

boolean isSymbol(char token) {
    return (token == '.') || (token == '(') || (token == ')') || (token == '+') || (token == '-') ||(token == '*') ||(token == '/');
}

void Expression(char *token, int *idx, double *result, boolean *valid) {
    // KAMUS LOKAL
    double temp;

    //ALGORITMA
    //printf("Awal Expression %d %.2f %d\n", *valid, *result, *idx);
    if (*idx < panjangKata){
        Term(token, idx, result,valid);
        if (*valid){
            while ((token[*idx] == '+' || token[*idx] == '-') && *valid){
                *valid = false;
                if (token[*idx] == '+'){
                    (*idx)++;
                    if (token[*idx] != '-'){
                        Term(token,idx,&temp,valid);
                        if (*valid){
                            *result += temp;
                            temp = 0;
                            *valid = true;
                        }
                    }
                } else if (token[*idx] == '-'){
                    (*idx)++;
                    if (token[*idx] != '-'){
                        Term(token,idx,&temp,valid);
                        if (*valid){
                            *result -= temp;
                            temp = 0;
                            *valid = true;
                        }
                    }
                }
                //printf("Expression %d %.2f %d\n", *valid, *result, *idx);
            }
            //printf("%c %d", token[*idx], isSymbol(token[*idx]));
            if (isSymbol(token[*idx]) || isNumber(token[*idx])){
                ///printf(" CEK ");
                *valid = false;
            }
            //printf(" %d\n", *valid);
        }
    } else {
        return;
    }
    //printf("Akhir Expression %d %.2f %d\n", *valid, *result, *idx);
}

void Term(char* token, int* idx, double* result, boolean *valid) {
    //KAMUS LOKAL
    double temp;
    
    //ALGORITMA
    //printf(" Awal Term %d %.2f %d\n", *valid, *result, *idx);
    Power(token,idx,result,valid);
    //Item(token,idx,result,valid);
    if (*valid){
        while ((token[*idx] == '*' || token[*idx] == '/') && *valid){
            *valid = false;
            //if ((*idx)+1 == panjangKata){
            //  *valid = false;
            //} else{
                if (token[*idx] == '*'){
                    (*idx)++;
                    if (token[*idx] != '-'){
                        Power(token,idx,&temp,valid);
                        if (*valid){
                            (*result) *= temp;
                            temp = 0;
                            *valid = true;
                        }
                    }
                } else if (token[*idx] == '/'){
                    (*idx)++;
                    if (token[*idx] != '-'){
                        Power(token,idx,&temp,valid);
                        if (*valid){
                            (*result) /= temp;
                            temp = 0;
                            *valid = true;
                        }
                    }
                }
                //printf(" Term %d %.2f %d\n", *valid, *result, *idx);
            //}
        }
    }
    //printf(" Akhir Term %d %.2f %d\n", *valid, *result, *idx);
}

void Power(char* token, int* idx, double* result, boolean *valid)
{
    //KAMUS LOKAL
    double temp = 0;
     //ALGORTIMA
    //printf("  Awal Power %d %.2f %d\n", *valid, *result, *idx);
    *valid = false;
    Item(token, idx, result, valid);
    if(*valid) {
        if(token[*idx] == '^') {
            (*idx)++;
            //printf("%.2f\n", *result);
            *valid = false;
            if (token[*idx] != '-'){
                Power(token,idx,&temp,valid);
                (*result) = pow((*result),temp);
                //printf("  Power %d %.2f %d\n", *valid, *result, *idx);
            }
        }
    }
    //printf("  Akhir Power %d %.2f %d\n", *valid, *result, *idx);
}

void Item(char* token,int* idx, double* result, boolean *valid)
{
    //KAMUS LOKAL
    double temp = 0;
    int x = 1;

    //ALGORITMA
    //printf("   Awal Item %d %.2f %d\n", *valid, *result, *idx);
    if(token[*idx] == '('){
        (*idx)++;
        Expression(token,idx,result,valid);
        *valid = false;
        if (token[*idx] == ')'){
            (*idx)++;
            *valid = true;
        }
        //else print error
    } else{  
        if (token[*idx] == '-'){
            *valid = false;
            if (token[*idx-1] != '-'){
                (*idx)++;
                x = -1;
                Power(token,idx,result,valid);
                if (*valid){
                    *result *= x;
                    *valid = true;
                }
            }
        }
        if (isNumber(token[*idx])){
            Number(token,idx,result);
            if (token[*idx] == '.'){
                (*idx)++;
                doubleNumber(token,idx,&temp);
            }
            *result = ((*result)+temp);
            temp = 0;
            *valid = true;
        }
    }
    //printf("   Akhir Item %d %.2f %d\n", *valid, *result, *idx);
    if (isSymbol(token[*idx] || isNumber(token[*idx]))){
        *valid = false;
    }
}

//-2^2 = -4 || -(2^2) != (-2)^2
//-2*4 = -8 || -(2*4) == (-2)*4

// 3-((4*5)6)

void Number(char* token,int* idx, double* result)
{
    if (!isNumber(token[*idx]))
        return;
    else
    {
        *result = ((*result)*10)+((double)token[*idx]-(double)'0');
        (*idx)++;
        Number(token,idx,result);
    }
}

void doubleNumber(char* token,int* idx, double* result)
{
    //KAMUS LOKAL
    double n;
    int id = *idx;

    //ALGORITMA
    Number(token, &id, &n);
    while(isNumber(token[*idx]))
    {
        n /= 10;
        (*idx)++;
    }
    *result = n;
    n = 0;
}