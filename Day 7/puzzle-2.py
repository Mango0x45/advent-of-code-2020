#!/usr/bin/env python3


# Recursively find the number of sub-bags in a bag
def total_bags(innerbags: list) -> int:
    if innerbags[0]["name"] == "no other":
        return 0

    sum = 0
    for bag in innerbags:
        sum += bag["count"] + bag["count"] * total_bags(bdict[bag["name"]])
    return sum


with open("input", "r") as f:
    lines = f.readlines()

bdict = {}
for baginfo in lines:
    data = baginfo.split(" bags contain")

    # { bag_name: [{ count: n, name: bag_name_ }, ...] }
    bdict[data[0]] = []
    for b in data[1].split(","):
        bdict[data[0]].append(
            {
                "count": int(b.replace("no", "0").split(" ")[1]),
                "name": " ".join(b.split(" ")[-3:][:2]),
            }
        )

print(total_bags(bdict["shiny gold"]))
