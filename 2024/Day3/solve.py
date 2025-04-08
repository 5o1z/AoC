#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# @Time    : 2025/04/08 9:35 PM
# @Author  : K.
# @File    : solve.py
# @Software: Visual Studio Code
# @Description: Solution for Advent of Code 2024 Day 3: Mull It Over
# @Link    : https://adventofcode.com/2024/day/3

import re

with open("input.txt", "r") as f:
    lines = f.read()

part1 = 0
part2 = 0
enabled = True

for a, b, do, dont in re.findall(r"mul\((\d{1,3}),(\d{1,3})\)|(do\(\))|(don't\(\))", lines):
    if do or dont:
        enabled = bool(do)
        # print(f"Enabled: {enabled}")
    else:
        part1 += int(a) * int(b)
        part2 += int(a) * int(b) * enabled

print("Part 1:", part1)
print("Part 2:", part2)
