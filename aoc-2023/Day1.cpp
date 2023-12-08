#include "Day1.h"

#include <algorithm>
#include <iterator>
#include <numeric>

llong Day1::p1(const std::vector<std::string>& input)
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

llong Day1::p2(const std::vector<std::string>& input)
{
    std::vector<int> calibrations = {};
    for (std::string s : input)
    {
        std::string digits = digitsOf(s);
        calibrations.push_back(std::stoi(digits.substr(0, 1) + digits.substr(digits.length() - 1, 1)));
    }
    return std::reduce(calibrations.begin(), calibrations.end());
}

std::string Day1::digitsOf(std::string s)
{
    std::string digits;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] >= 48 && s[i] <= 57)
        {
            digits.push_back(s[i]);
        }
        else
        {
            for (int j = 0; j < alpha.size(); j++)
            {
                if (s.substr(i, alpha[j].length()).compare(alpha[j]) == 0) {
                    digits.push_back(num[j]);
                }
            }
        }
    }
    return digits;
}