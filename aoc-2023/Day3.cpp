#include "Day3.h"

#include <algorithm>
#include <iostream>
#include <tuple>

int Day3::p1(std::vector<std::string> in)
{
    this->input = in;
    int sum = 0;
    for (int row = 0; row < this->input.size(); row++)
    {
        int startCol = -1;
        for (int col = 0; col < this->input[row].size(); col++)
        {
            bool digit = std::find(num.begin(), num.end(), this->input[row][col]) != num.end();
            if (digit && startCol < 0)
            {
                startCol = col;
            }
            else if (!digit || col + 1 == this->input[row].size())
            {
                col = digit ? col + 1 : col;
                if (startCol >= 0 && hasAdjacentSymbol(row, startCol, col))
                {
                    sum += std::stoi(input[row].substr(startCol, col - startCol));
                }
                startCol = -1;
            }
        }
    }
    return sum;
}

int Day3::p2(std::vector<std::string> input)
{
    return 0;
}

bool Day3::hasAdjacentSymbol(int row, int startCol, int endCol)
{
    std::vector<std::tuple<int, int>> adjacent;
    if (row > 0)
    {
        for (int col = startCol; col < endCol; col++)
        {
            adjacent.push_back({ row - 1, col });
        }
        if (startCol > 0)
        {
            adjacent.push_back({ row - 1, startCol - 1 });
        }
        if (endCol < input[0].size())
        {
            adjacent.push_back({ row - 1, endCol });
        }
    }
    if (row < input.size() - 1)
    {
        for (int col = startCol; col < endCol; col++)
        {
            adjacent.push_back({ row + 1, col });
        }
        if (startCol > 0)
        {
            adjacent.push_back({ row + 1, startCol - 1 });
        }
        if (endCol < input[0].size())
        {
            adjacent.push_back({ row + 1, endCol });
        }
    }
    if (startCol > 0)
    {
        adjacent.push_back({ row, startCol - 1 });
    }
    if (endCol < input[0].size())
    {
        adjacent.push_back({ row, endCol });
    }
    return hasSymbol(adjacent);
}

bool Day3::hasSymbol(std::vector<std::tuple<int, int>> coords)
{
    return std::any_of(coords.begin(), coords.end(),
        [this](std::tuple<int, int> coord)
        {
            return std::find(nonSymbol.begin(), nonSymbol.end(),
                this->input[std::get<0>(coord)][std::get<1>(coord)]) == nonSymbol.end();
        });
}
