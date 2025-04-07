// @Time : 2025/04/07 7:35 PM
// @Author : Jinn
// @File : solve.py
// @Software : Visual Studio Code
// @Description : Solution for Advent of Code 2024 Day 2: Red-Nosed Reports
// Link : https://adventofcode.com/2024/day/2

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_REPORT_SIZE 1000
#define MAX_LINE_LENGTH 10000
#define FILENAME "input.txt"

// Check if a report is safe based on the safety rules
bool is_safe(int *report, int size)
{
    if (size < 2)
    {
        return true;
    }

    // Determine direction (increasing or decreasing)
    int diff = report[1] - report[0];

    // Equal adjacent values not allowed
    if (diff == 0)
    {
        return false;
    }

    // Check if first difference is in range
    if (abs(diff) > 3)
    {
        return false;
    }

    bool is_increasing = diff > 0;

    // Check each adjacent pair
    for (int i = 1; i < size - 1; i++)
    {
        int current_diff = report[i + 1] - report[i];

        // Check range (1-3)
        if (abs(current_diff) < 1 || abs(current_diff) > 3)
        {
            return false;
        }

        // Check consistency in direction
        if ((is_increasing && current_diff <= 0) || (!is_increasing && current_diff >= 0))
        {
            return false;
        }
    }

    return true;
}

// Check if a report can be made safe by removing one element
bool can_be_safe_with_removal(int *report, int size)
{
    if (size <= 2)
    {
        return false; // Too short after removal
    }

    // Create a temporary array to store the modified report
    int *temp = (int *)malloc((size - 1) * sizeof(int));
    if (temp == NULL)
    {
        printf("Memory allocation failed\n");
        return false;
    }

    bool result = false;

    // Try removing each element and check if resulting report is safe
    for (int i = 0; i < size; i++)
    {
        int j = 0;
        for (int k = 0; k < size; k++)
        {
            if (k != i)
            {
                temp[j++] = report[k];
            }
        }
        if (is_safe(temp, size - 1))
        {
            result = true;
            break;
        }
    }

    free(temp);
    return result;
}

int main()
{
    FILE *file = fopen(FILENAME, "r");
    int safe_count = 0;
    int safe_with_removal_count = 0;
    int report_count = 0;

    char *line = (char *)malloc(MAX_LINE_LENGTH * sizeof(char));

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
    {
        int *report = (int *)malloc(MAX_REPORT_SIZE * sizeof(int));
        int size = 0;
        char *token = strtok(line, " \t\n");

        // Parse the numbers from the line
        while (token != NULL && size < MAX_REPORT_SIZE)
        {
            report[size++] = atoi(token);
            token = strtok(NULL, " \t\n");
        }

        bool is_report_safe = is_safe(report, size);

        if (is_report_safe)
        {
            safe_count++;
            safe_with_removal_count++; // Already safe reports also count for part 2
        }
        else if (can_be_safe_with_removal(report, size))
        {
            safe_with_removal_count++;
        }

        free(report);
    }

    free(line);
    fclose(file);

    printf("Part 1: %d\n", safe_count);
    printf("Part 2: %d\n", safe_with_removal_count);

    return 0;
}
