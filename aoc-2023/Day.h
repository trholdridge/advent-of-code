#pragma once

#include <string>
#include <vector>

typedef long long llong;

class Day
{
protected:
    static bool digit(const char c);
    static std::vector<std::string> split(const std::string& s, const char delim);
    static std::vector<std::string> split(const std::string& s, const std::string& delim);
    static std::vector<llong> splitLongs(const std::string& s, const char delim);
    static std::vector<int> splitInts(const std::string& s, const char delim);
public:
    virtual llong p1(const std::vector<std::string>& input) = 0;
    virtual llong p2(const std::vector<std::string>& input) = 0;
};

