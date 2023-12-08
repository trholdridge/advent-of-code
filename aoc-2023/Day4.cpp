#include "Day4.h"

#include <algorithm>
#include <cmath>
#include <map>
#include <numeric>
#include <sstream>

llong Day4::p1(const std::vector<std::string>& input)
{
    llong sum = 0;
    std::vector<Card> cards = process(input);
    for (Card c : cards)
    {
        std::vector<int> matches;
        std::set_intersection(std::get<1>(c).begin(), std::get<1>(c).end(),
            std::get<2>(c).begin(), std::get<2>(c).end(), std::back_inserter(matches));
        sum += static_cast<llong>(std::pow(2, static_cast<llong>(matches.size() - 1)));
    }
    return sum;
}

llong Day4::p2(const std::vector<std::string>& input)
{
    std::map<int, int> copies;
    std::vector<Card> cards = process(input);
    for (Card c : cards)
    {
        int id = std::get<0>(c);
        std::vector<int> matches;
        std::set_intersection(std::get<1>(c).begin(), std::get<1>(c).end(),
            std::get<2>(c).begin(), std::get<2>(c).end(), std::back_inserter(matches));
        if (copies.find(id) == copies.end())
        {
            copies[id] = 1;
        }
        for (int i = 1; i <= matches.size(); i++)
        {
            if (copies.find(id + i) == copies.end())
            {
                copies[id + i] = 1 + copies[id];
            }
            else
            {
                copies[id + i] = copies[id + i] + copies[id];
            }
        }
    }
    return std::accumulate(std::begin(copies), std::end(copies), 0,
        [](int previous, const std::pair<int, int> p)
        { return previous + p.second; });
}

std::vector<Card> Day4::process(std::vector<std::string> input)
{
    std::vector<Card> cards;
    for (std::string line : input)
    {
        size_t colon_idx = line.find(":");
        int id = std::stoi(line.substr(4, colon_idx - 4));
        size_t bar_idx = line.find("|");
        std::istringstream nums1(line.substr(colon_idx + 2, bar_idx - 1 - (colon_idx + 2)));
        std::istringstream nums2(line.substr(bar_idx + 2));
        std::vector<std::string> tokens1{ std::istream_iterator<std::string>{nums1},
                      std::istream_iterator<std::string>{} };
        std::vector<std::string> tokens2{ std::istream_iterator<std::string>{nums2},
                      std::istream_iterator<std::string>{} };
        std::set<int> winning;
        for (std::string tok : tokens1)
        {
            winning.insert(std::stoi(tok));
        }
        std::set<int> mine;
        for (std::string tok : tokens2)
        {
            mine.insert(std::stoi(tok));
        }
        cards.push_back({ id, winning, mine });
    }
    return cards;
}