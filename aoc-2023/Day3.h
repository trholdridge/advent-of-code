#pragma once
#include "Day.h"

#include <map>
#include <string>
#include <vector>

class Day3 :
    public Day
{
private:
    const std::vector<char> num = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    const std::vector<char> nonSymbol = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
    std::vector<std::string> input;
    std::vector<std::tuple<int, int>> adjacentSymbols(int row, int startCol, int endCol);
    bool hasSymbol(std::tuple<int, int> coord);
    int gearRatioSum(std::map<std::tuple<int, int>, std::vector<int>> gearMap);

public:
    llong p1(const std::vector<std::string>& input) override;
    llong p2(const std::vector<std::string>& input) override;
};