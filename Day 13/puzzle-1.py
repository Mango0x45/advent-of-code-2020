#!/usr/bin/env python3
with open("input", "r") as f:
    time = int(f.readline())
    ids = [int(x) for x in f.readline().replace(",x", "").split(",")]

ids.sort()
min = -1
x = 0
for bus in ids:
    res = (time + ids[0]) % bus
    if res < ids[0] and res > min:
        min = res
        x = bus

for i in range(time, time + ids[0]):
    if i % x == 0:
        print((i - time) * x)
        break
