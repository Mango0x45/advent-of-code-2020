#!/bin/awk -f

# The ugliest script so far!
# NOTE: FOR THIS TO WORK, YOU MUST ADD A NEWLINE AT THE END OF THE INPUT FILE

BEGIN {
    eyecolor[1] = "amb"
    eyecolor[2] = "blu"
    eyecolor[3] = "brn"
    eyecolor[4] = "gry"
    eyecolor[5] = "grn"
    eyecolor[6] = "hzl"
    eyecolor[7] = "oth"
}

# Blank lines
/^$/ {
    valid = 1

    if (!(fields["byr"] >= 1920 && fields["byr"] <= 2002)) {
        valid = 0
    } else if (!(fields["iyr"] >= 2010 && fields["iyr"] <= 2020)) {
        valid = 0
    } else if (!(fields["eyr"] >= 2020 && fields["eyr"] <= 2030)) {
        valid = 0
    } else if (length(fields["pid"]) != 9) {
        valid = 0
    } else {
        # Test eyecolor
        valid = 0
        for (i in eyecolor) {
            if (fields["ecl"] == eyecolor[i]) { valid = 1 }
        }

        # Test height
        split(fields["hgt"], height, "[^0-9]")
        unit = substr(fields["hgt"], length(fields["hgt"] - length(height[1])) + 1)
        if (unit == "cm") {
            if (!(height[1] >= 150 && height[1] <= 193)) {
                valid = 0
            }
        } else if (unit == "in") {
            if (!(height[1] >= 59 && height[1] <= 76)) {
                valid = 0
            }
        } else { valid = 0 }

        # Test haircolor
        if (length(fields["hcl"]) == 7) {
            hair = match(fields["hcl"], "[0-9a-f]{6}")
            if (hair == 0) { valid = 0 }
            else {
                hash = substr(fields["hcl"], 1, 1)
                if (hash != "#") { valid = 0 }
            }
        } else { valid = 0 }
    }

    if (valid == 1) { count++ }

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
