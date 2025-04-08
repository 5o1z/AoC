#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# @Time    : 2025/04/07 7:35 PM
# @Author  : K.
# @File    : solve.py
# @Software: Visual Studio Code
# @Description: Solution for Advent of Code 2024 Day 2: Red-Nosed Reports
# @Link    : https://adventofcode.com/2024/day/2

def safe(report):
    if len(report) < 2:
        return True

    # Determine direction (increasing or decreasing)
    diff = report[1] - report[0]

    # Equal adjacent values not allowed
    if diff == 0:
        return False

    # Check if first difference is in range
    if abs(diff) > 3:
        return False

    is_increasing = diff > 0

    # Check each adjacent pair
    for i in range(1, len(report) - 1):
        current_diff = report[i+1] - report[i]

        # Check range (1-3)
        if abs(current_diff) < 1 or abs(current_diff) > 3:
            return False

        # Check consistency in direction
        if (is_increasing and current_diff <= 0) or (not is_increasing and current_diff >= 0):
            return False

    return True

def can_be_safe_with_removal(report):
    if len(report) <= 2:  # Too short after removal
        return False

    # Try removing each element and check if resulting report is safe
    for i in range(len(report)):
        modified_report = report[:i] + report[i+1:]
        # print(f"Modified report: {modified_report}")
        if safe(modified_report):
            return True

    return False

arr = []
with open("input.txt", "r") as f:
    for line in f:
        numbers = [int(x) for x in line.split()]
        arr.append(numbers)

safe_count = 0
safe_with_removal_count = 0

for i, report in enumerate(arr):
    is_safe = safe(report)

    if is_safe:
        safe_count += 1
        safe_with_removal_count += 1  # Already safe reports also count for part 2
    elif can_be_safe_with_removal(report):
        safe_with_removal_count += 1


print(f"Part 1: {safe_count}")
print(f"Part 2: {safe_with_removal_count}")
