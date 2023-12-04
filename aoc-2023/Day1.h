#pragma once

#include <string>
#include <vector>

class Day1
{
private:
    const std::vector<std::string> alpha = { "zero", "one", "two", "three", "four",
        "five", "six", "seven", "eight", "nine" };
    const std::vector<char> num = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    std::string digitsOf(std::string s);
public:
    int p1(std::vector<std::string> input);
    int p2(std::vector<std::string> input);
};