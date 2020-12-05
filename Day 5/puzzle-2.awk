#!/bin/awk -f

# Run with `./seatids | ./puzzle-2.awk`

{
    ids[NR] = $0
}

END {
    n = asort(ids)
    for (i = 1; i <= n; i++)
        if ((i + 35) != ids[i]) {
            print i + 35
            # Break out, because the first missing
            # occurance will affect all the other IDs
            break
        }
}