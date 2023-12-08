#pragma once
#include "Day.h"

#include <string>
#include <vector>

class Day1 :
    public Day
{
private:
    const std::vector<std::string> alpha = { "zero", "one", "two", "three", "four",
        "five", "six", "seven", "eight", "nine" };
    const std::vector<char> num = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    std::string digitsOf(std::string s);
public:
    llong p1(const std::vector<std::string>& input) override;
    llong p2(const std::vector<std::string>& input) override;
};