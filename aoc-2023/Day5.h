#pragma once

#include "Day.h"

#include <map>
#include <utility>

typedef std::pair<llong, llong> Range;
typedef std::map<Range, llong> AlmanacMap;

class Day5 :
    public Day
{
private:
    std::vector<llong> seeds{};
    std::vector<AlmanacMap> maps{};
    std::vector<Range> destsOf(const std::vector<Range>& dests, const AlmanacMap& m);
    std::vector<Range> destsOf(Range& dest, const AlmanacMap& m);
    void buildMaps(const std::vector<std::string>& input);
    llong almanac(const AlmanacMap& m, const llong i);
public:
    int p1(const std::vector<std::string>& input) override;
    int p2(const std::vector<std::string>& input) override;
};