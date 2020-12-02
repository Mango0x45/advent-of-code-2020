#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *input = fopen("input", "r");

    if (input == NULL) {
        perror("Error: Unable to open file 'input'");
        exit(EXIT_FAILURE);
    }

    int nums[200];

    for (int i = 0; i < 200; i++)
        fscanf(input, "%d", &nums[i]);

    fclose(input);

    /* Inefficient, but small sample size so it's fine */
    int result;
    for (int i = 0; i < 199; i++)
        for (int j = i + 1; j < 200; j++)
            if (nums[i] + nums[j] == 2020) {
                printf("%d\n", nums[i] * nums[j]);
                return EXIT_SUCCESS;
            }

    return EXIT_FAILURE;
}