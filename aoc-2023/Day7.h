#pragma once
#include "Day.h"

#include <map>

typedef std::pair<std::string, int> Hand;

class Day7 :
    public Day
{
private:
    enum HandType
    {
        HIGH,
        ONEPAIR,
        TWOPAIR,
        THREE,
        FULL,
        FOUR,
        FIVE
    };
    static const std::map<char, int> cardMap;

    static HandType handType(const Hand& h);
    static bool compareHands(const Hand& h1, const Hand& h2);
    static bool compareCards (const std::string& s1, const std::string& s2);
    static int cardValue(const char c);
public:
    int p1(const std::vector<std::string>& input) override;
    int p2(const std::vector<std::string>& input) override;
};