#include "Day1.h"

#include <algorithm>
#include <iterator>
#include <numeric>

int Day1::p1(std::vector<std::string> input)
{
    std::vector<int> calibrations = {};
    for (std::string s : input)
    {
        std::string digits;
        std::copy_if(s.begin(), s.end(), std::back_inserter(digits),
            [](char c) { return c >= 48 && c <= 57; });
        calibrations.push_back(std::stoi(digits.substr(0, 1) + digits.substr(digits.length() - 1, 1)));
    }
    return std::reduce(calibrations.begin(), calibrations.end());
}