#include "Main.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Day7.h"

int main()
{
    std::vector<std::string> lines = {};
    std::ifstream infile("input7.txt");

    for (std::string line; std::getline(infile, line); )
    {
        lines.push_back(line);
    }

    Day7 d = Day7();
    std::cout << d.p1(lines) << "\n";
    return 0;
}