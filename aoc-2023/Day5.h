#pragma once

#include "Day.h"

#include <map>
#include <utility>

typedef std::map<std::pair<llong, llong>, llong> AlmanacMap;

class Day5 :
    public Day
{
private:
    std::vector<llong> seeds{};
    std::vector<AlmanacMap> maps{};
    void buildMaps(const std::vector<std::string>& input);
    llong almanac(const AlmanacMap& m, const llong i);
public:
    int p1(const std::vector<std::string>& input) override;
    int p2(const std::vector<std::string>& input) override;
};