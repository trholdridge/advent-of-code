#pragma once
#include "Day.h"

#include <functional>
#include <map>

class Day8 :
    public Day
{
private:
    std::string directions;
    std::map<std::string, std::pair< std::string, std::string>> network;
    void process(const std::vector<std::string>& input);
    llong stepsFrom(std::string node, std::function<bool(const std::string&)> match);
public:
    llong p1(const std::vector<std::string>& input) override;
    llong p2(const std::vector<std::string>& input) override;
};

