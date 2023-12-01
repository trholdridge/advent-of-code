#include "Main.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Day1.h"

int main()
{
    std::vector<std::string> lines = {};
    std::ifstream infile("input1.txt");

    for (std::string line; std::getline(infile, line); )
    {
        lines.push_back(line);
    }

    Day1 d = Day1();
    std::cout << d.p2(lines) << "\n";
    return 0;
}