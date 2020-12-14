#!/usr/bin/env python3
def bitmask(mask: str, num: int) -> tuple[int, ...]:
    binary = bin(num)[2:]
    binary = binary.zfill(36)
    res = ""

    for i in range(len(binary)):
        if mask[i] == "0":
            res += binary[i]
        else:
            res += mask[i]

    n = res.count("X")
    combos = tuple(bin(i)[2:].zfill(n) for i in range(2 << n - 1))

    acc = []
    for combo in combos:
        temp = res
        for i in range(n):
            temp = temp.replace("X", combo[i], 1)
        acc.append(temp)

    return tuple(int(x, 2) for x in acc)


with open("input", "r") as f:
    lines = f.read().splitlines()

mem = {}
mask = ""
for line in lines:
    line = line.split(" ")
    if line[0] == "mask":
        mask = line[2]
    else:
        address = line[0][4:-1]
        addresses = bitmask(mask, int(address))
        for a in addresses:
            mem[a] = int(line[2])

acc = 0
for val in mem:
    acc += mem[val]

print(acc)
