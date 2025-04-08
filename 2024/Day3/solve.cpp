//@Time : 2025/04/08 9:35 PM
//@Author : K.
//@File : solve.cpp
//@Software : Visual Studio Code
//@Description : Solution for Advent of Code 2024 Day 3 : Mull It Over
//@Link : https://adventofcode.com/2024/day/3

#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main()
{
    ifstream file("input.txt");
    if (!file.is_open())
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string lines((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    // cout << "Lines: " << lines << endl;
    file.close();

    int part1 = 0;
    int part2 = 0;
    bool enabled = true;

    regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\)|(do\(\))|(don't\(\)))");

    sregex_iterator iter(lines.begin(), lines.end(), pattern);
    sregex_iterator end;

    while (iter != end)
    {
        smatch match = *iter;

        if (match[3].matched)
        {
            // do()
            enabled = true;
        }
        else if (match[4].matched)
        {
            // don't()
            enabled = false;
        }
        else if (match[1].matched && match[2].matched)
        {
            // mul(x,y)
            int a = stoi(match[1]);
            int b = stoi(match[2]);

            part1 += a * b;
            part2 += a * b * enabled;
        }

        ++iter;
    }

    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;

    return 0;
}
