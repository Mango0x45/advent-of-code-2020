#include <stdio.h>

#ifdef BUFSIZ
#   undef BUFSIZ
#endif
#define BUFSIZ 200

int main(void)
{
    FILE *input = fopen("input", "r");

    int nums[BUFSIZ];
    for (int i = 0; i < BUFSIZ; i++)
        fscanf(input, "%d", &nums[i]);

    fclose(input);

    /* Inefficient, but small sample size so it's fine */
    for (int i = 0; i < BUFSIZ - 1; i++)
        for (int j = i + 1; j < BUFSIZ; j++)
            if (nums[i] + nums[j] == 2020) {
                printf("%d\n", nums[i] * nums[j]);
                return 0;
            }

    return 1;
}
