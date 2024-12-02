#pragma once
#include "Day.h"

class Day9 :
    public Day
{
private:
    llong nextInSequence(std::vector<llong> sequence);
    llong prevInSequence(std::vector<llong> sequence);
public:
    llong p1(const std::vector<std::string>& input) override;
    llong p2(const std::vector<std::string>& input) override;
};