#ifndef _calculator_h
#define _calculator_h

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include "boolean.h"

/*
S -> T | S+T | S-T Expression
T -> F | T*F | T/F Term
F -> (S) | -A | A | A.A | -A.A sign
A -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | AA number
*/
extern int panjangKata;

boolean isNumber(char token);
boolean isSymbol(char token);
boolean isOperation(char token);
void Expression(char *token, int *idx, double *result, boolean *valid);
void Term(char *token, int *idx, double *result, boolean *valid);
void Item(char *token, int *idx, double *result, boolean *valid);
void Power(char *token, int *idx, double *result, boolean *valid);
void Number(char *token,int *idx, double *result);
void doubleNumber(char *token, int *idx, double *result);

#endif