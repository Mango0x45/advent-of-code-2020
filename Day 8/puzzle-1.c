#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct instructions {
    char opp;
    int val;
} INST;

/* Function prototypes */
int str2int(const char *str);
bool repeati(const int lines[], const int i);

/**
 * Convert a string to an integer
 */
int str2int(const char *str)
{
    int ret = 0;
    for (int i = 0, len = strlen(str); i < len; i++) {
        if (str[i] == '-' || str[i] == '+' || str[i] == '\n')
            continue;
        ret = ret * 10 + str[i] - '0';
    }

    if (str[0] == '-')
        ret *= -1;

    return ret;
}

/**
 * Check if the given instruction has been
 * executed already
 */
bool repeati(const int lines[], const int i)
{
    for (int j = 0; j < 653; j++)
        if (lines[j] == i)
            return true;
    return false;
}

int main(void)
{
    FILE *fpt = fopen("input", "r");
    INST circuit[653];

    /* Current line */
    char cl[10];
    int cl_size = sizeof(cl);

    /* Load the entire circuit */
    int i = 0;
    while (fgets(cl, cl_size, fpt) != NULL) {
        INST operation;
        operation.opp = cl[0];

        char *val;
        val = strtok(cl, " ");
        val = strtok(NULL, " ");
        operation.val = str2int(val);

        circuit[i++] = operation;
    }

    int acc = 0;
    int l = i = 0;
    int lines[653] = {0};

    /* Execute the circuit */
    while (repeati(lines, i + 1) == false) {
        switch (circuit[i].opp) {
        case 'j':
            i += circuit[i].val;
            break;

        case 'a':
            acc += circuit[i].val; __attribute__ ((fallthrough));

        default:
            lines[l++] = i++;
            break;
        }
    }

    printf("%d\n", acc);

    fclose(fpt);
    return 0;
}
