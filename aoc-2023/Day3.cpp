#include "Day3.h"

#include <algorithm>
#include <iostream>
#include <tuple>

llong Day3::p1(const std::vector<std::string>& input)
{
    this->input = input;
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
                if (startCol >= 0 && adjacentSymbols(row, startCol, col).size() > 0)
                {
                    sum += std::stoi(input[row].substr(startCol, col - startCol));
                }
                startCol = -1;
            }
        }
    }
    return sum;
}

llong Day3::p2(const std::vector<std::string>& input)
{
    this->input = input;
    std::map<std::tuple<int, int>, std::vector<int>> gearMap;
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
                if (startCol >= 0 && adjacentSymbols(row, startCol, col).size() > 0)
                {
                    int num = std::stoi(input[row].substr(startCol, col - startCol));
                    std::vector<std::tuple<int, int>> syms = adjacentSymbols(row, startCol, col);
                    std::for_each(syms.begin(), syms.end(),
                        [this, &gearMap, num](std::tuple<int, int> coord)
                        {
                            if (this->input[std::get<0>(coord)][std::get<1>(coord)] == '*')
                            {
                                if (gearMap.find(coord) == gearMap.end())
                                {
                                    gearMap[coord] = std::vector<int>({ num });
                                }
                                else
                                {
                                    gearMap[coord].push_back(num);
                                }
                            }
                        });
                }
                startCol = -1;
            }
        }
    }
    return gearRatioSum(gearMap);
}

std::vector<std::tuple<int, int>> Day3::adjacentSymbols(int row, int startCol, int endCol)
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

    std::vector<std::tuple<int, int>> adjacentSym;
    std::copy_if(adjacent.begin(), adjacent.end(), std::back_inserter(adjacentSym),
        [this](std::tuple<int, int> coord)
        {
            return hasSymbol(coord);
        });
    return adjacentSym;
}

bool Day3::hasSymbol(std::tuple<int, int> coord)
{
    return std::find(nonSymbol.begin(), nonSymbol.end(),
        this->input[std::get<0>(coord)][std::get<1>(coord)]) == nonSymbol.end();
}

int Day3::gearRatioSum(std::map<std::tuple<int, int>, std::vector<int>> gearMap)
{
    int sum = 0;
    for (const auto& [gear, adjacentNums] : gearMap)
    {
        if (adjacentNums.size() == 2)
        {
            sum += adjacentNums[0] * adjacentNums[1];
        }
    }
    return sum;
}
