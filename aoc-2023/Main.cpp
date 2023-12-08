#include "Main.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Day8.h"

int main()
{
    std::vector<std::string> lines = {};
    std::ifstream infile("input8.txt");

    for (std::string line; std::getline(infile, line); )
    {
        lines.push_back(line);
    }

    Day8 d = Day8();
    std::cout << d.p2(lines) << "\n";
    return 0;
}