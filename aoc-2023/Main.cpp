#include "Main.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Day5.h"

int main()
{
    std::vector<std::string> lines = {};
    std::ifstream infile("input5.txt");

    for (std::string line; std::getline(infile, line); )
    {
        lines.push_back(line);
    }

    Day5 d = Day5();
    std::cout << d.p1(lines) << "\n";
    return 0;
}