#pragma once
#include "Day.h"

class Day6 :
    public Day
{
private:
    std::vector<int> times;
    std::vector<int> distances;
    int waysToBeat(int time, int distance);
public:
    int p1(const std::vector<std::string>& input) override;
    int p2(const std::vector<std::string>& input) override;
};

