#include "Calculated.h"

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

void Calculate(char* st, int*idx, float * result, boolean *valid) {
    if (*idx < panjangKata)
    {
        float temp;
        TimesDiv(st, idx, result,valid);
        while (st[*idx] == '+' || st[*idx] == '-')
        {
            if (st[*idx] == '+')
            {
                (*idx)++;
                TimesDiv(st,idx,&temp,valid);
                *result += temp;
                temp = 0;
            } else if (st[*idx] == '-')
            {
                (*idx)++;
                TimesDiv(st,idx,&temp,valid);
                *result -= temp;
                temp = 0;
            }
        }
    } else {
        return;
    }
}

void TimesDiv(char* st,int* idx, float* result, boolean *valid) {
    float temp;
    Sign(st,idx,result,valid);
    while (st[*idx] == '*' || st[*idx] == '/')
    {
        if (st[*idx] == '*')
        {
            (*idx)++;
            Sign(st,idx,&temp,valid);
            (*result) *= temp;
            temp = 0;
        } else if (st[*idx] == '/')
        {
            (*idx)++;
            Sign(st,idx,&temp,valid);
            (*result) /= temp;
            temp = 0;
        }
    }
}

void Sign(char* st,int* idx, float* result, boolean *valid) {
    float temp = 0;
    int x = 1;
    if(st[*idx] == '(') {
        (*idx)++;
        Calculate(st,idx,result,valid);
        if (st[*idx] == ')')
            (*idx)++;
        //else print error
    } else {
        if (st[*idx] == '-')
        {
            (*idx)++;
            x = -1;
        }
        if (isNumber(st[*idx]))
        {
            Number(st,idx,result);
            if (st[*idx] == '.')
            {
                (*idx)++;
                FloatNumber(st,idx,&temp);
            }
            *result = ((*result)+temp)*x;
            temp = 0;
        }
        else
        {
            *valid = false;
        }
    }
}

void Number(char* st,int* idx, float* result) {
    if (!isNumber(st[*idx]))
        return;
    else
    {
        *result = ((*result)*10)+((float)st[*idx]-(float)'0');
        (*idx)++;
        Number(st,idx,result);
    }
}

void FloatNumber(char* st,int* idx, float* result) {
    float n;
    int id = *idx;
    Number(st, &id, &n);
    while(isNumber(st[*idx]))
    {
        n /= 10;
        (*idx)++;
    }
    *result = n;
    n = 0;
}