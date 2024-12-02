#include "Main.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Day9.h"

int main()
{
    std::vector<std::string> lines = {};
    std::ifstream infile("input9.txt");

    for (std::string line; std::getline(infile, line); )
    {
        lines.push_back(line);
    }

    Day9 d = Day9();
    std::cout << d.p2(lines) << "\n";
    return 0;
}