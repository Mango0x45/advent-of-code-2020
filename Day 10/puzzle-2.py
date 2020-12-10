#!/usr/bin/env python3
from typing import List


def combos(i: int) -> int:
    if i == len(adaptors) - 1:
        return 1
    if i in counts:
        return counts[i]

    ans = 0
    for j in range(i + 1, len(adaptors)):
        if adaptors[j] - adaptors[i] <= 3:
            ans += combos(j)

    counts[i] = ans
    return ans


with open("input", "r") as f:
    adaptors = list(map(int, f.readlines()))

adaptors.append(0)
adaptors.sort()
adaptors.append(max(adaptors) + 3)

counts = {}
print(combos(0))
