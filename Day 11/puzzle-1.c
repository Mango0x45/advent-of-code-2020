#include <stdbool.h>
#include <stdio.h>

#define ROWCNT 98
#define ROWLEN 98

bool changed;
char rows[ROWCNT][ROWLEN + 1];
char temp[ROWCNT][ROWLEN + 1];

void check_seat(int const i, int const j);

/**
 * Check and update a seat at the given index
 */
void check_seat(int const i, int const j)
{
    if (rows[i][j] == '.')
        return;

    /* Count adjecent seats */
    int adjecent = 0;
    for (int h = i - 1; h <= i + 1; h++) {
        if (h < 0 || h > ROWCNT - 1)
            continue;
        for (int k = j - 1; k <= j + 1; k++) {
            if (k < 0 || k > ROWCNT - 1 || (h == i && k == j))
                continue;
            if (rows[h][k] == '#')
                adjecent++;
        }
    }
    
    /* Edit seats as needed */
    if (rows[i][j] == 'L' && adjecent == 0) {
        temp[i][j] = '#';
        changed = true;
    } else if (rows[i][j] == '#' && adjecent >= 4) {
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