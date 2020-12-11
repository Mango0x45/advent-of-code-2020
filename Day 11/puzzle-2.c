#include <stdbool.h>
#include <stdio.h>

#define ROWCNT 98
#define ROWLEN 98
#define IS_SEAT(a, b)   if (rows[a][b] == '.') continue
#define IS_OCC(a, b)    if (rows[a][b] == '#') adjecent++

bool changed;
char rows[ROWCNT][ROWLEN + 1];
char temp[ROWCNT][ROWLEN + 1];

void check_seat(const int i, const int j);

/**
 * Check and update a seat at the given index
 */
void check_seat(const int i, const int j)
{
    if (rows[i][j] == '.')
        return;

    int adjecent = 0;
    
    /* Up */
    for (int h = i - 1; h >= 0; h--) {
        IS_SEAT(h, j);
        IS_OCC(h, j);
        break;
    }
    /* Down */
    for (int h = i + 1; h < ROWCNT; h++) {
        IS_SEAT(h, j);
        IS_OCC(h, j);
        break;
    }
    /* Left */
    for (int h = j - 1; h >= 0; h--) {
        IS_SEAT(i, h);
        IS_OCC(i, h);
        break;
    }
    /* Right */
    for (int h = j + 1; h < ROWLEN; h++) {
        IS_SEAT(i, h);
        IS_OCC(i, h);
        break;
    }
    /* Up-Left */
    for (int h = i - 1, k = j - 1; h >= 0 && k >= 0; h--, k--) {
        IS_SEAT(h, k);
        IS_OCC(h, k);
        break;
    }
    /* Up-Right */
    for (int h = i - 1, k = j + 1; h >= 0 && k < ROWLEN; h--, k++) {
        IS_SEAT(h, k);
        IS_OCC(h, k);
        break;
    }
    /* Down-Left */
    for (int h = i + 1, k = j - 1; h < ROWCNT && k >= 0; h++, k--) {
        IS_SEAT(h, k);
        IS_OCC(h, k);
        break;
    }
    /* Down-Right */
    for (int h = i + 1, k = j + 1; h < ROWCNT && k < ROWLEN; h++, k++) {
        IS_SEAT(h, k);
        IS_OCC(h, k);
        break;
    }
    
    /* Edit seats as needed */
    if (rows[i][j] == 'L' && adjecent == 0) {
        temp[i][j] = '#';
        changed = true;
    } else if (rows[i][j] == '#' && adjecent >= 5) {
        temp[i][j] = 'L';
        changed = true;
    } else
        temp[i][j] = rows[i][j];
}

int main(void)
{
    /* Initialize the temp array to be all floor */
    int i, j;
    for (i = 0; i < ROWCNT; i++)
        for (j = 0; j < ROWLEN; j++)
            temp[i][j] = '.';


    FILE *fpt = fopen("input", "r");
    char c;

    /* Read in seats */
    i = j = 0;
    while ((c = fgetc(fpt)) != EOF) {
        if (c == '\n') {
            i = 0;
            j++;
        } else
            rows[j][i++] = c;
    }

    /* Update the seats until they don't change anymore */
    do {
        changed = false;
        for (i = 0; i < ROWCNT; i++)
            for (j = 0; j < ROWLEN; j++)
                check_seat(i, j);

        for (i = 0; i < ROWCNT; i++)
            for (j = 0; j < ROWLEN; j++)
                rows[i][j] = temp[i][j];
    } while (changed == true);

    /* Calculate filled seats */
    int count = 0;
    for (i = 0; i < ROWCNT; i++)
        for (j = 0; j < ROWLEN; j++)
            if (rows[i][j] == '#')
                count++;

    printf("%d\n", count);
    return 0;
}