// @Time : 2025/04/07 6:18 PM
// @Author : K.
// @File : solve.c
// @Software : Visual Studio Code
// @Description : Solution for Advent of Code 2024 Day 1 : Historian Hysteria
// @Link : https://adventofcode.com/2024/day/1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILENAME "input.txt"
#define MAX_LINES 1000

// Check if a string contains only whitespace.
int is_blank(const char *str)
{
    while (*str)
    {
        if (!isspace((unsigned char)*str))
            return 0;
        str++;
    }
    return 1;
}

// Comparison function for qsort.
int compare_int(const void *a, const void *b)
{
    return (*(const int *)a - *(const int *)b);
}

int main(void)
{
    FILE *f = fopen(FILENAME, "r");
    if (!f)
    {
        perror("Error opening file");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int left[MAX_LINES];
    int right[MAX_LINES];
    size_t count = 0;

    while ((read = getline(&line, &len, f)) != -1)
    {
        // Skip blank lines.
        if (is_blank(line))
            continue;

        int l, r;
        // Parse the line for two integers.
        if (sscanf(line, "%d %d", &l, &r) == 2)
        {
            if (count < MAX_LINES)
            {
                left[count] = l;
                right[count] = r;
                count++;
            }
            else
            {
                fprintf(stderr, "Reached maximum number of lines (%d).\n", MAX_LINES);
                break;
            }
        }
        else
        {
            fprintf(stderr, "Skipping improperly formatted line: %s", line);
        }
    }

    free(line);
    fclose(f);

    qsort(left, count, sizeof(int), compare_int);
    qsort(right, count, sizeof(int), compare_int);

    long long total1 = 0, total2 = 0;
    for (size_t i = 0; i < count; i++)
    {
        total1 += abs(left[i] - right[i]);

        int freq = 0;
        for (size_t j = 0; j < count; j++)
        {
            if (right[j] == left[i])
                freq++;
        }
        total2 += (long long)left[i] * freq;
    }

    printf("Total distance: %lld\n", total1);
    printf("Total freq: %lld\n", total2);

    return 0;
}
