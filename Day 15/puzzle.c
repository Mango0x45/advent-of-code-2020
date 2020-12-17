#include <stdio.h>

#ifdef BUFSIZ
#   undef BUFSIZ
#endif
#ifndef PART2
#   define BUFSIZ 2020
#else
#   define BUFSIZ 30000000
#endif

int main(void)
{
    /* Given starting numbers */
    static unsigned int nums[BUFSIZ] = {0};
    nums[6] = 1;
    nums[19] = 2;
    nums[0] = 3;
    nums[5] = 4;
    nums[7] = 5;
    nums[13] = 6;

    unsigned int temp, lnum = 1;
    for (int i = 8; i <= BUFSIZ; i++) {
        temp = lnum;
        if (nums[lnum] == 0)
            lnum = 0;
        else
            lnum = i - 1 - nums[lnum];

        nums[temp] = i - 1;
    }

    printf("%u\n", lnum);
    return 0;
}