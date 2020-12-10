#!/usr/bin/env -S awk -f puzzle-2.awk input

BEGIN {
    for (i = 1; i <= 5; i++)
        slope[i] = 1
}

{
    len = split($0, obs, "")

    right = 1
    for (i = 1; i < 5; i++) {
        if (slope[i] > len)
            slope[i] -= len

        if (obs[slope[i]] == "#")
            count[i]++

        slope[i] += right
        right += 2
    }

    # Specific code for slope 5
    if (NR % 2 == 1) {
        if (slope[5] > len)
            slope[5] -= len

        if (obs[slope[5]++] == "#")
            count[5]++
    }
}

END {
    print count[1] * count[2] * count[3] * count[4] * count[5]
}
