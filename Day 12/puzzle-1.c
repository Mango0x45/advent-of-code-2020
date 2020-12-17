#include <stdio.h>
#include <string.h>

int str2int(char const * const str);

/**
 * Convert a string to an integer
 */
int str2int(char const * const str)
{
    register unsigned int ret = 0;
    /* i = 1 to skip the first character */
    for (int i = 1, len = strlen(str); i < len; i++) {
        if (str[i] == '\n')
            break;
        ret = ret * 10 + str[i] - '0';
    }

    return ret;
}

int main(void)
{
    FILE *fpt = fopen("input", "r");
    char cl[5];
    unsigned int const cl_size = sizeof(cl);
    int north = 0, east = 0;
    int direction = 0;

    while (fgets(cl, cl_size, fpt) != NULL) {
        switch (cl[0]) {
        case 'N':
            north += str2int(cl);
            break;

        case 'E':
            east += str2int(cl);
            break;

        case 'S':
            north -= str2int(cl);
            break;

        case 'W':
            east -= str2int(cl);
            break;

        case 'L':
            direction -= str2int(cl);
            goto WRAP;

        case 'R':
            direction += str2int(cl);

            /* 0 <= direction < 360 */
WRAP:       if (direction >= 360)
                direction -= 360;
            else if (direction < 0)
                direction += 360;
            break;

        case 'F':
            switch (direction) {
            case 0:
                east += str2int(cl);
                break;

            case 90:
                north -= str2int(cl);
                break;

            case 180:
                east -= str2int(cl);
                break;

            case 270:
                north += str2int(cl);
                break;
            }
            break;
        }
    }
    fclose(fpt);

    /* Absolute value */
    if (north < 0)
        north *= -1;
    if (east < 0)
        east *= -1;

    printf("%d\n", north + east);
    return 0;
}
