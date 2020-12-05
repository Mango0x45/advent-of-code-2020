#!/bin/awk -f

# Run with `./seatids | ./puzzle-1.awk`

$0 > max {
    max = $0
}

END {
    print max
}