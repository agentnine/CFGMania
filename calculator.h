#ifndef _CALCULATED_h
#define _CALCULATED_h

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "boolean.h"

/*
S -> T | S+T | S-T calculate
T -> F | T*F | T/F timesdiv
F -> (S) | -A | A | A.A | -A.A sign
A -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | AA number
*/
extern int panjangKata;

boolean isNumber(char st);
boolean isSymbol(char st);
void Calculate(char* st, int*idx, double * result, boolean *valid);
void TimesDiv(char* st,int* idx, double* result,boolean *valid);
void Sign(char* st,int* idx, double* result,boolean *valid);
void power(char* st, int* idx, double* result, boolean *valid);
void Number(char* st,int* idx, double* result);
void doubleNumber(char* st,int* idx, double* result);

#endif