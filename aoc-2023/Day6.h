#pragma once
#include "Day.h"

class Day6 :
    public Day
{
private:
    llong waysToBeat(llong time, llong distance);
public:
    llong p1(const std::vector<std::string>& input) override;
    llong p2(const std::vector<std::string>& input) override;
};

