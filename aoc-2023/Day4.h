#pragma once
#include "Day.h"

#include <set>
#include <string>
#include <tuple>
#include <vector>

typedef std::tuple<int, std::set<int>, std::set<int>> Card;

class Day4 :
    public Day
{
private:
     std::vector<Card> process(std::vector<std::string> input);
public:
    llong p1(const std::vector<std::string>& input) override;
    llong p2(const std::vector<std::string>& input) override;
};