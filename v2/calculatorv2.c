#include "calculatorv2.h"
#include <stdio.h>
/*
S -> T1 | S+T1 | S-T2 Expression
T1 -> P1 | T1*P1 | T1/P1 Term
T2 -> P2 | T2+P2 | T2/P2 Term
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
  return (token == '.') || (token == '(') || (token == ')') || (token == '+') || (token == '-') ||(token == '*') ||(token == '/') || (token == '^');
}

boolean isOperation(char token) {
  return (token == '+') || (token == '-') ||(token == '*') ||(token == '/') || (token == '^')|| (token == '(');
}

void Expression(char *token, int *idx, double complex *result, boolean *valid)
/*Ekspression akan menjalankan variabel non terminal "S -> T1 | S+T1 | S-T2 Expression"
  yang mengelola apakah program memiliki ekspresi + dan/atau - */
{
  //KAMUS LOKAL
  double complex temp = 0+0*I;

  //ALGORITMA
  if (*idx < panjangKata){
    Term(token, idx, result,valid);
    if (*valid){
      while ((token[*idx] == '+' || token[*idx] == '-') && *valid){
        *valid = false;
        if (token[*idx] == '+'){
          //Percabangan ini akan menjakankan program saat menemukan ekspresi +
          (*idx)++;
          if (token[*idx] != '-'){
            Term(token,idx,&temp,valid);
            if (*valid){
              *result += temp;
              temp = 0+0*I;
              *valid = true;
            }
          }
        } else if (token[*idx] == '-'){
          //Percabangan ini akan menjakankan program saat menemukan ekspresi -
          (*idx)++;
          if (token[*idx] != '-'){
            Term(token,idx,&temp,valid);
            if (*valid){
              *result -= temp;
              temp = 0+0*I;
              *valid = true;
            }
          }
        }
      }
      if (isSymbol(token[*idx]) || isNumber(token[*idx])){
        *valid = false;
      }
    }
  } else {
    return;
  }
}

void Term(char* token, int* idx, double complex* result, boolean *valid)
/*Ekspression akan menjalankan variabel non terminal "T1 -> P1 | T1*P1 | T1/P1 Term" atau
  "T2 -> P2 | T2+P2 | T2/P2 Term" yang mengelola apakah program memiliki ekspresi * dan/atau / */
{
  //KAMUS LOKAL
  double complex temp = 0+0*I;
    
  //ALGORITMA
  Power(token,idx,result,valid);
  if (*valid){
    while ((token[*idx] == '*' || token[*idx] == '/') && *valid){
      *valid = false;
      if (token[*idx] == '*'){
        //Percabangan ini akan menjakankan program saat menemukan ekspresi *
        (*idx)++;
        if (token[*idx] != '-'){
          Power(token,idx,&temp,valid);
          if (*valid){
            (*result) *= temp;
            temp = 0+0*I;
            *valid = true;
          }
        }
      } else if (token[*idx] == '/'){
        //Percabangan ini akan menjakankan program saat menemukan ekspresi /
        (*idx)++;
        if (token[*idx] != '-'){
          Power(token,idx,&temp,valid);
          if (*valid){
            (*result) /= temp;
            temp = 0+0*I;
            *valid = true;
          }
        }
      }
    }
  }
}

void Power(char* token, int* idx, double complex* result, boolean *valid)
/*Ekspression akan menjalankan variabel non terminal "P1 -> F1 | F1^P2 Power" atau
  "P2 -> F2 | F2^P2 Power" yang mengelola apakah program memiliki ekspresi ^ */
{
  //KAMUS LOKAL
  double complex temp = 0+0*I;
    
  //ALGORTIMA
  *valid = false;
  Item(token, idx, result, valid);
  if(*valid) {
    if(token[*idx] == '^'){
      (*idx)++;
      *valid = false;
      if (token[*idx] != '-'){
        Power(token,idx,&temp,valid);
        if ((cimag(*result) == -0) || (cimag(temp) == -0)){
          //printf("Ya\n");
        }
        if (cimag(*result) == -0){
          (*result) = creal(*result)+0*I;
        }
        if (cimag(temp) == -0){
          temp = creal(temp)+0*I;
        }
        if ((cimag(*result) == -0) || (cimag(temp) == -0)){
          //printf("Ya\n");
        }
        //printf("%.2f%+.2fi pow %.2f%+.2fi = ", creal(*result), cimag(*result), creal(temp), cimag(temp));
        (*result) = pow((*result),(temp));  
      }
    }
  }
}

void Item(char* token,int* idx, double complex* result, boolean *valid)
/*Ekspression akan menjalankan variabel non terminal "F1 -> (S) | -P1 | A Item"
  "F2 -> (S) | (-P2) | A Item" yang mengelola apakah program memiliki ekspresi - dan/atau () */
{
  //KAMUS LOKAL
  double complex temp = 0+0*I;
  double complex x = 1+0*I;

  //ALGORITMA
  if(token[*idx] == '('){
    //Percabangan ini akan menjakankan program saat menemukan ekspresi ()
    (*idx)++;
    Expression(token,idx,result,valid);
    *valid = false;
    if ((token[*idx] == ')') && (token[*idx-1] != '(')){
      (*idx)++;
      *valid = true;
      if (token[*idx] == 'i'){
        (*result) = (*result)*(0+1*I);
        (*idx)++;
      }
    }
  } else{  
    if (token[*idx] == '-'){
      //Percabangan ini akan menjakankan program saat menemukan ekspresi -
      *valid = false;
      if (token[*idx-1] != '-'){
        (*idx)++;
        x = -1+0*I;
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
      temp = 0+0*I;
      *valid = true;
    }
    if (token[*idx] == 'i'){
      *valid = false;
      if ((isOperation(token[*idx-1]) || (*idx == 0)) && (token[*idx+1] != 'i')){
        (*result) = (0+1*I);
        *valid = true;
      }else if (isNumber(token[*idx-1])){
        (*result) = (*result)*(0+1*I);
        *valid = true;
      }
      (*idx)++;
    }
  }
}

void Number(char* token,int* idx, double complex* result)
/*Melakukan parsing untuk mendapat angka bilangan bulat sebelum koma jika bilangan adalah bilangan desimal*/
{
  //ALGORTMA
  if (!isNumber(token[*idx]))
    return;
  else{
    *result = ((*result)*(10+0*I))+((double)token[*idx]-(double)'0');
    (*idx)++;
    Number(token,idx,result);
  }
}

void doubleNumber(char* token,int* idx, double complex* result)
/*Melakukan parsing untuk mendapat angka bilangan bulat setelah koma jika bilangan adalah bilangan desimal*/
{
  //KAMUS LOKAL
  double complex n;
  int id = *idx;

  //ALGORITMA
  Number(token, &id, &n);
  while(isNumber(token[*idx]))
  {
    n /= 10+0*I;
    (*idx)++;
  }
  *result = n;
  n = 0+0*I;
}
