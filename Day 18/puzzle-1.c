#define  _GNU_SOURCE
#include <ctype.h>
#include <stdio.h>
#include <sys/types.h>

unsigned long long parse_number(void);
unsigned long long parse_digit(void);
unsigned long long parse_eqn(void);
void remove_spaces(char *str);

char *g_current;

/*
 * Convert the current number from a string to an int
 */
unsigned long long parse_number(void)
{
    register unsigned long long number = 0;
    while (isdigit(*g_current))
        number = number * 10 + *g_current++ - '0';

    return number;
}

/*
 * Parse the current digit pointed to by `g_current`
 */
unsigned long long parse_digit(void)
{
    if (isdigit(*g_current))
        return parse_number();

    /* If not a digit, it's a parenthesis */
    g_current++;
    register unsigned long long result = parse_eqn();
    g_current++;
    return result;
}

/*
 * Parse and compute an equation
 */
unsigned long long parse_eqn(void)
{
    register unsigned long long result = parse_digit();

    while (*g_current == '+' || *g_current == '*') {
        g_current++;

        if (*(g_current - 1) == '+')
            result += parse_digit();
        else
            result *= parse_digit();
    }

    return result;
}

/*
 * Remove the spaces from user input
 */
void remove_spaces(char *str)
{
    char const *c = str;
    do {
        while (*c == ' ')
            c++;
    } while ((*str++ = *c++));
}

int main(void)
{
    FILE *fpt = fopen("input", "r");
    char *line;
    size_t len;
    ssize_t read;

    unsigned long long acc = 0;
    while ((read = getline(&line, &len, fpt)) != -1) {
        remove_spaces(line);
        g_current = line;
        acc += parse_eqn();
    }

    printf("%llu\n", acc);
    return 0;
}
