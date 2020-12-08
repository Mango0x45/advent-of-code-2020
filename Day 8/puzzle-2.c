#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define LINECOUNT 653

typedef struct instructions {
    char opp;
    int val;
} INST;

/* Function prototypes */
int str2int(const char *str);
bool repeati(const int lines[], const int rip);
int run_circuit(INST circuit[]);

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
bool repeati(const int lines[], const int rip)
{
    for (int i = 0; i < LINECOUNT; i++)
        if (lines[i] == rip)
            return true;
    return false;
}

/**
 * Run the given circuit
 */
int run_circuit(INST circuit[])
{
    int i = 0;
    int acc = 0;
    int rip = 0;
    int lines[LINECOUNT] = {0};

    /* Execute the circuit */
    while (true) {
        lines[i] = rip;

        switch (circuit[rip].opp) {
        case 'j':
            rip += circuit[rip].val;
            if (rip >= LINECOUNT)
                return acc;
            break;

        case 'a':
            acc += circuit[rip].val;
            __attribute__ ((fallthrough));

        case 'n':
            rip++;
            break;
        }
        i++;

        if (repeati(lines, rip) == true)
            break;
    }

    return -1;
}

int main(void)
{
    FILE *fpt = fopen("input", "r");
    INST circuit[LINECOUNT];

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
    fclose(fpt);

    /* Run circuit until it completes successfully */
    int result = -1;
    int count = 1;
    int prev_count = count;
    while (result == -1 && count < LINECOUNT) {
        for (i = 0; i < LINECOUNT; i++) {
            if (circuit[i].opp == 'j' || circuit[i].opp == 'n')
                count--;

            /* Swap jmp and nop */
            if (count == 0) {
                if (circuit[i].opp == 'j')
                    circuit[i].opp = 'n';
                else
                    circuit[i].opp = 'j';
                break;
            }
        }

        count = ++prev_count;
        result = run_circuit(circuit);

        /* Return to original array */
        if (circuit[i].opp == 'j')
            circuit[i].opp = 'n';
        else
            circuit[i].opp = 'j';
    }

    printf("%d\n", result);
    return 0;
}
