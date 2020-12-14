#!/usr/bin/env python3
def bitmask(mask: str, num: int) -> int:
    binary = bin(num)[2:]
    binary = "0" * (36 - len(binary)) + binary
    res = ""

    for i in range(len(binary)):
        if binary[i] == "1" and mask[i] == "0":
            res += "0"
        elif binary[i] == "0" and mask[i] == "1":
            res += "1"
        else:
            res += binary[i]

    return int(res, 2)


with open("input", "r") as f:
    lines = f.read().splitlines()

mem = {}
mask = ""
for line in lines:
    line = line.split(" ")
    if line[0] == "mask":
        mask = line[2]
    else:
        mem[line[0][4:-1]] = bitmask(mask, int(line[2]))

acc = 0
for val in mem:
    acc += mem[val]

print(acc)
