#!/usr/bin/env python3
with open("input", "r") as f:
    data = f.readlines()

i = 0
valid = []
while data[i] != "\n":
    ranges = data[i].split(": ")[1].split(" or ")
    for _range in ranges:
        bounds = tuple(map(int, _range.split("-")))
        for j in range(bounds[0], bounds[1] + 1):
            valid.append(j)
    i += 1

# Skip to nearby tickets
i += 5
acc = 0

for j in range(i, len(data)):
    fields = tuple(map(int, data[j].split(",")))
    for field in fields:
        if field not in valid:
            acc += field


print(acc)
