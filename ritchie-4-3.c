#include "calcstk.h"

/* Input line definition and operations */
#define LINE_BUF_SIZE 32 /* This should be enough to handle floating
    point numbers with up to 15 integer digits, a decimal point and 
    up to 15 fractional digits */
char line[LINE_BUF_SIZE]; /* Input line buffer */
int get_line(); /* Read input line*/
void skip_line(); /* Skip excessively long input lines */
int is_operator(); /* Check if an input line is an operator one */
double atolf(); /* Convert string to double */

int main()
{
    int line_len; /* Input line length */
    double operand; /* Used in operand order-sensitive operations */

    printf("reverse polish calculator\n");

    calcstk_t* stack = init();
    clear(stack);

    while(1) {
        print(stack);
        line_len = get_line();

        /* Check if line exceeds LINE_BUF_SIZE */
        if (line_len == LINE_BUF_SIZE) {
            printf("err: input line is too long\n");
            skip_line();
        }

        /* If an operator line is detected, try to perform its 
            operation, otherwise convert its value to double and 
            push it */
        if (is_operator()) {
            if ((line[0] == '+' || line[0] == '-' || line[0] == '*' || line[0] == '/') && stack->sp < 2)
                printf("err: not enough operands\n");
            else {
                switch (line[0]) {
                    case '+':
                        push(stack, pop(stack) + pop(stack));
                        break;
                    case '-':
                        operand = pop(stack);
                        push(stack, pop(stack) - operand);
                        break;
                    case '*':
                        push(stack, pop(stack) * pop(stack));
                        break;
                    case '/':
                        operand = pop(stack);
                        push(stack, pop(stack) / operand);
                        break;
                    case 'a': /* Average */
                        if(!avg(stack))
                            printf("err: stack is empty\n");
                        break;
                    case 'c': /* Clear stack */
                        clear(stack);
                        break;
                    case 'p': /* Pick */
                        if (!pick(stack))
                            printf("err: invalid pick index\n");
                        break;
                    case 'd': /* Delete */
                        del(stack);
                        break;
                    case 's': /* Sum */
                        if(!sum(stack))
                            printf("err: stack is empty\n");
                        break;
                    case 'q': /* Quit */
                        return 0;
                        break;
                    default:
                        break;
                }
            }
        } else if (!push(stack, atolf(line)))
            printf("err: stack is full\n");
    }

    return 0;
}

/* Convert string to floating point number */
double atolf()
{
    int i, j;
    double d, p;
    
    /* See if there's a decimal point */
    for (i = 0; line[i] != '.' && line[i] != '\0'; ++i);

    d = 0.0;
    if (line[i] == '.' || line[i] == '\0') {
        /* Convert the integer part first */
        p = 1.0;
        for (j = i - 1; j >= 0; --j) {
            d += p * (line[j] - 48);
            p *= 10;
        }

        /* Then convert the decimal part, if there is one */
        if (line[i] == '.') {
            p = 0.1;
            for (j = i + 1; line[j] != '\0'; ++j) {
                d += p * (line[j] - 48);
                p /= 10;
            }
        }
    }

    return d;
}

void skip_line()
{
    char c;

    while((c = getchar()) != '\n');
}

int get_line()
{
    char c;
    int i;

    i = 0;
    while ((c = getchar()) != '\n' && i < LINE_BUF_SIZE - 1) {
        line[i++] = c;
    }
    line[i++] = '\0';

    return i;
}

int is_operator()
{
    char c;

    c = line[0];
    return c == '+' || c == '-' || c == '*' || c == '/' || c == 'a' || c == 'c' || c == 'p' || c == 'd' || c == 's' ||c == 'q';
}

