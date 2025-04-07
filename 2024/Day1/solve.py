#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# @Time    : 2025/04/07 6:18 PM
# @Author  : Jinn
# @File    : solve.py
# @Software: Visual Studio Code
# @Description: Solution for Advent of Code 2024 Day 1: Historian Hysteria
# @Link    : https://adventofcode.com/2024/day/1

with open("input", "r") as f:
    lines = f.readlines()

left = []
right = []


for line in lines:
    # Skip the line if it is empty or only whitespace
    if not line.strip():
        continue
    l, r = map(int, line.split())
    left.append(l)
    right.append(r)

left.sort()
right.sort()

# print(list(zip(left, right)))
total1 = 0
total2 = 0
count = 0


for l, r in zip(left, right):
    # print(f"{l} {r}")
    distance = abs(l - r)
    total1 += distance

    count = l * right.count(l)
    total2 += count

print("Total distance:", total1) # Part 1
print("Total count:", total2)    # Part 2
