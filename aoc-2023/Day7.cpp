#include "Day7.h"

#include <algorithm>

const std::map<char, int> Day7::cardMap = { {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}, {'A', 14} };

int Day7::p1(const std::vector<std::string>& input)
{
    std::vector<Hand> hands;
    for (std::string s : input)
    {
        std::vector<std::string> temp = split(s, ' ');
        hands.push_back(std::make_pair(temp[0], std::stoi(temp[1])));
    }

    std::sort(hands.begin(), hands.end(), compareHands);

    int sum = 0;
    for (int i = 0; i < hands.size(); i++)
    {
        sum += (i + 1) * hands[i].second;
    }

    return sum;
}

int Day7::p2(const std::vector<std::string>& input)
{
    return 0;
}

bool Day7::compareHands(const Hand& h1, const Hand& h2)
{
    HandType type1 = handType(h1);
    HandType type2 = handType(h2);

    if (type1 == type2)
    {
        return compareCards(h1.first, h2.first);
    }
    else
    {
        return type1 < type2;
    }
}

Day7::HandType Day7::handType(const Hand& h)
{
    std::map<char, int> count;
    int maxCount = 0;
    for (char c : h.first)
    {
        if (count.find(c) == count.end())
        {
            count[c] = 1;
        }
        else {
            count[c] = count[c] + 1;
        }
        if (count[c] > maxCount)
        {
            maxCount = count[c];
        }
    }

    switch (count.size())
    {
    case 5:
        return HandType::HIGH;
    case 4:
        return HandType::ONEPAIR;
    case 3:
        if (maxCount == 3)
        {
            return HandType::THREE;
        }
        else
        {
            return HandType::TWOPAIR;
        }
    case 2:
        if (maxCount == 4)
        {
            return HandType::FOUR;
        }
        else
        {
            return HandType::FULL;
        }
    case 1:
        return HandType::FIVE;
    }
}

bool Day7::compareCards(const std::string& s1, const std::string& s2)
{
    for (int i = 0; i < s1.size(); i++)
    {
        if (s1[i] != s2[i])
        {
            return cardValue(s1[i]) < cardValue(s2[i]);
;       }
    }
    return true;
}

int Day7::cardValue(const char c)
{
    if (digit(c))
    {
        return c - '0';
    }
    else
    {
        return cardMap.at(c);
    }
}