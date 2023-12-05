#include "Day.h"

#include <algorithm>
#include <sstream>

bool Day::digit(char c)
{
    return c >= '0' && c <= '9';
}

std::vector<std::string> Day::split(const std::string& s, char delim)
{
    std::vector<std::string> tokens;
    std::istringstream iss(s);
    std::string token;
    while (std::getline(iss, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::string> Day::split(const std::string& s, const std::string& delim)
{
    return std::vector<std::string>();
}

std::vector<llong> Day::splitNums(const std::string& s, const char delim)
{
    std::vector<llong> nums;
    std::vector<std::string> tokens = split(s, delim);
    for (std::string token : tokens)
    {
        nums.push_back(std::stoll(token));
    }
    return nums;
}
