#!/usr/bin/env -S awk -f puzzle-1.awk input

{
    split($1, bounds, "-")
    char = substr($2, 1, 1)
    freq = gsub(char, "&") - 1

    if (freq >= bounds[1] && freq <= bounds[2])
        count++
}

END {
    print count
}
