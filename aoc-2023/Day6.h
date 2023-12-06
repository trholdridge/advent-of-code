#pragma once
#include "Day.h"

class Day6 :
    public Day
{
private:
    llong waysToBeat(llong time, llong distance);
public:
    int p1(const std::vector<std::string>& input) override;
    int p2(const std::vector<std::string>& input) override;
};

