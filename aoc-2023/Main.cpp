#include "Main.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Day6.h"

int main()
{
    std::vector<std::string> lines = {};
    std::ifstream infile("input6.txt");

    for (std::string line; std::getline(infile, line); )
    {
        lines.push_back(line);
    }

    Day6 d = Day6();
    std::cout << d.p1(lines) << "\n";
    return 0;
}