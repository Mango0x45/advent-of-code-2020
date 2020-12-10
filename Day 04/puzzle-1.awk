#!/usr/bin/env -S awk -f puzzle-1.awk input

# Blank lines
/^$/ {
    valid = 1
    for (i in fields)
        if (fields[i] == "") valid = 0

    if (valid == 1)
        count++

    fields["byr"] = ""
    fields["iyr"] = ""
    fields["eyr"] = ""
    fields["hgt"] = ""
    fields["hcl"] = ""
    fields["ecl"] = ""
    fields["pid"] = ""
}

# Non-blank lines
!/^$/ {
    for (i = 1; i <= NF; i++) {
        split($i, data, ":")
        fields[data[1]] = data[2]
    }
}

END {
    print count
}
