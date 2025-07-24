#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

#ifndef CALCSTK_H
#define CALCSTK_H

#define STACK_BUF_SIZE 32

typedef struct {
    int sp;
    double stk[STACK_BUF_SIZE];
} calcstk_t;

calcstk_t* init();
int push(calcstk_t* stack, double number);
double pop(calcstk_t* stack);
void clear(calcstk_t* stack);
void del(calcstk_t* stack);
int pick(calcstk_t* stack);
void print(calcstk_t* stack);
int avg(calcstk_t* stack);
int sum(calcstk_t* stack);
int no_pop_avg(calcstk_t* stack);
int std(calcstk_t* stack);

#endif

