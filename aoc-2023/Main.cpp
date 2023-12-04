#include "Main.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Day4.h"

int main()
{
    std::vector<std::string> lines = {};
    std::ifstream infile("input4.txt");

    for (std::string line; std::getline(infile, line); )
    {
        lines.push_back(line);
    }

    Day4 d = Day4();
    std::cout << d.p2(lines) << "\n";
    return 0;
}