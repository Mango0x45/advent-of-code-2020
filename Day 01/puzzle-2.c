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
    for (int i = 0; i < BUFSIZ - 2; i++)
        for (int j = i + 1; j < BUFSIZ - 1; j++)
            for (int k = j + 1; k < BUFSIZ; k++)
                if (nums[i] + nums[j] + nums[k] == 2020) {
                    printf("%d\n", nums[i] * nums[j] * nums[k]);
                    return 0;
                }

    return 1;
}
