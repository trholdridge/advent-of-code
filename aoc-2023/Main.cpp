#include "Main.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Day3.h"

int main()
{
    std::vector<std::string> lines = {};
    std::ifstream infile("input3.txt");

    for (std::string line; std::getline(infile, line); )
    {
        lines.push_back(line);
    }

    Day3 d = Day3();
    std::cout << d.p2(lines) << "\n";
    return 0;
}