#include <stdio.h>
#include <string.h>

int str2int(const char *str);

struct coords {
    int north;
    int east;
};

/**
 * Convert a string to an integer
 */
int str2int(const char *str)
{
    int ret = 0;
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
    char cl[6];
    int cl_size = sizeof(cl);
    struct coords waypoint = {1, 10};
    struct coords ship = {0, 0};

    while (fgets(cl, cl_size, fpt) != NULL) {
        switch (cl[0]) {
        case 'N':
            waypoint.north += str2int(cl);
            break;

        case 'E':
            waypoint.east += str2int(cl);
            break;

        case 'S':
            waypoint.north -= str2int(cl);
            break;

        case 'W':
            waypoint.east -= str2int(cl);
            break;

        case 'F': ;
            int val = str2int(cl);
            ship.north += val * waypoint.north;
            ship.east += val * waypoint.east;
            break;

        /* Left and right */
        default: ;
            int direction = str2int(cl);

            /* (x, y) -> (-x, -y) */
            if (direction == 180) {
                waypoint.north *= -1;
                waypoint.east *= -1;
                break;
            } 

            /* 0 <= direction < 360 */
            if (cl[0] == 'R')
                direction = direction * -1 + 360;

            int temp = waypoint.east;
            /* (x, y) -> (-y, x) */
            if (direction == 90) {
                waypoint.east = waypoint.north * -1;
                waypoint.north = temp;
            /* (x, y) -> (y, -x) */
            } else {
                waypoint.east = waypoint.north;
                waypoint.north = temp * -1;
            }
            break;
        }
    }
    fclose(fpt);

    /* Absolute value */
    if (ship.north < 0)
        ship.north *= -1;
    if (ship.east < 0)
        ship.east *= -1;

    printf("%d\n", ship.north + ship.east);
    return 0;
}