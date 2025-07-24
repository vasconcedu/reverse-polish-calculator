#include "calcstk.h"

calcstk_t* init() {
    calcstk_t* stack;

    stack = (calcstk_t*) malloc(sizeof(calcstk_t));
    stack->sp = 0;
    return stack;
}

int push(calcstk_t* stack, double number)
{
    if (stack->sp < STACK_BUF_SIZE) {
        stack->stk[stack->sp++] = number;
        return stack->sp;
    }
    return 0;
}

double pop(calcstk_t* stack)
{
    if (stack->sp > 0)
        return stack->stk[--stack->sp];
    else
        return 0.0; 
}

void clear(calcstk_t* stack)
{
    stack->sp = 0;
}

void del(calcstk_t* stack)
{
    pop(stack);
}

int pick(calcstk_t* stack)
{
    int p;

    p = stack->stk[stack->sp - 1];
    if (p >= 0 && p < stack->sp) {
        pop(stack);
        push(stack, stack->stk[p]);
        return 1;
    } else
        return 0;
}

void print(calcstk_t* stack)
{
    int i;
     
    printf("stk (sp:%d): ", stack->sp);
    for (i = 0; i < stack->sp; ++i) {
        printf("%d:%lf ", i, stack->stk[i]);
    }
    printf("\n");
}

int avg(calcstk_t* stack)
{
    if (stack->sp == 0)
        return 0;

    int i;
    double s, n;

    s = 0.0;
    n = stack->sp;
    for (i = stack->sp - 1; i >= 0; --i)
        s += pop(stack);
    push(stack, s/n);
    return 1;
}

int sum(calcstk_t* stack)
{
    if (stack->sp == 0)
        return 0;

    int i;
    double s, n;

    s = 0.0;
    n = stack->sp;
    for (i = stack->sp - 1; i >= 0; --i)
        s += pop(stack);
    push(stack, s);
    return 1;
}

int no_pop_avg(calcstk_t* stack)
{
    if (stack->sp == 0)
        return 0;

    int i;
    double s;

    s = 0.0;
    for (i = stack->sp - 1; i >= 0; --i)
        s += stack->stk[i];
   
    push(stack, s/stack->sp);
    return 1;
}

int std(calcstk_t* stack)
{
    if (!no_pop_avg(stack))
        return 0;

    int i;
    double s;
    
    s = 0.0;
    for (i = 0; i < stack->sp - 1; ++i) /* The average is at stack->stk[stack->sp - 1]  */
        s += pow(stack->stk[i] - stack->stk[stack->sp - 1], 2);

    push(stack, sqrt(s/(stack->sp - 1))); /* Population std */
    push(stack, sqrt(s/((stack->sp - 2) - 1))); /* Sample std */

    return 1;
}

