#include "Day7.h"

#include <algorithm>
#include <functional>

const std::map<char, int> Day7::cardMap = { {'T', 10}, {'J', 1}, {'Q', 12}, {'K', 13}, {'A', 14} };

llong Day7::p1(const std::vector<std::string>& input)
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

llong Day7::p2(const std::vector<std::string>& input)
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

bool Day7::compareHands(const Hand& h1, const Hand& h2)
{
    HandType type1 = handType2(h1);
    HandType type2 = handType2(h2);

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
    std::map<char, int> count = {};
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
    case 0:
        return HandType::FIVE;
    }
}

Day7::HandType Day7::handType2(const Hand& h)
{
    std::map<char, int> count;
    int jokerCount = 0;
    char mode = h.first[0];
    for (char c : h.first)
    {
        if (c == 'J')
        {
            jokerCount += 1;
            continue;
        }

        if (count.find(c) == count.end())
        {
            count[c] = 1;
        }
        else {
            count[c] = count[c] + 1;
        }
        if (mode == 'J' || count[c] > count[mode])
        {
            mode = c;
        }
    }
    count[mode] = count[mode] + jokerCount;

    switch (count.size())
    {
    case 5:
        return HandType::HIGH;
    case 4:
        return HandType::ONEPAIR;
    case 3:
        if (count[mode] == 3)
        {
            return HandType::THREE;
        }
        else
        {
            return HandType::TWOPAIR;
        }
    case 2:
        if (count[mode] == 4)
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