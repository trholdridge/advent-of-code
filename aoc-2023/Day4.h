#pragma once

#include <set>
#include <string>
#include <tuple>
#include <vector>

typedef std::tuple<int, std::set<int>, std::set<int>> Card;

class Day4
{
private:
     std::vector<Card> process(std::vector<std::string> input);
public:
    int p1(std::vector<std::string> input);
    int p2(std::vector<std::string> input);
};

