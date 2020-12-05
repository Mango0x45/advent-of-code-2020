#include <math.h>
#include <stdio.h>

/**
 * Parse the input file `input` and print out
 * all of the seat IDs which can be piped into
 * both awk scripts
 */
int main(void)
{
    FILE *fpt = fopen("input", "r");
    if (fpt == NULL) {
        perror("Error: Unable to open file 'input'");
        return 1;
    }

    /* +2 for \n and \0 */
    char bpass[12];

    while (fgets(bpass, 12, fpt) != NULL) {
        /* Seat Row */
        int lower_r = 0;
        int upper_r = 127;
        for (int i = 0; i < 7; i++) {
            if (bpass[i] == 'F')
                upper_r = (upper_r + lower_r) / 2;
            else
                lower_r = round((upper_r + lower_r) / 2);
        }

        /* Seat Column */
        int lower_c = 0;
        int upper_c = 7;
        for (int i = 7; i < 10; i++) {
            if (bpass[i] == 'L')
                upper_c = (upper_c + lower_c) / 2;
            else
                lower_c = round((upper_c + lower_c) / 2);
        }

        /* `<< 3` is a multiplication by 8 */
        int seat_id = upper_r << 3 + upper_c;
        printf("%d\n", seat_id);
    }

    return 0;
}
