#include "Day8.h"

#include <algorithm>
#include <iostream>
#include <numeric>

int Day8::p1(const std::vector<std::string>& input)
{
    process(input);
    return stepsFrom("AAA", [](const std::string& s) { return s == "ZZZ"; });
}

int Day8::p2(const std::vector<std::string>& input)
{
    process(input);
    std::vector<std::string> nodes;
    for (const auto& [key, val] : network)
    {
        if (key[2] == 'A')
        {
            nodes.push_back(key);
        }
    }

    std::vector<llong> steps;
    for (std::string node : nodes)
    {
        steps.push_back(stepsFrom(node, [](std::string s) { return s[2] == 'Z'; }));
    }

    llong lcm = std::accumulate(steps.begin(), steps.end(), static_cast<llong>(1),
        [](const llong a, const llong b)
        {
            return std::lcm(a, b);
        });
    return lcm;
}

void Day8::process(const std::vector<std::string>& input)
{
    this->directions = input[0];

    for (int i = 2; i < input.size(); i++)
    {
        std::vector<std::string> tokens = split(input[i], ' ');
        std::string left = tokens[2].substr(1, tokens[2].size() - 2);
        std::string right = tokens[3].substr(0, tokens[3].size() - 1);
        this->network[tokens[0]] = std::make_pair(left, right);
    }
}

llong Day8::stepsFrom(std::string node, std::function<bool(const std::string&)> match)
{
    llong steps = 0;
    while (!match(node) || steps == 0)
    {
        switch (directions[steps % directions.size()])
        {
        case 'L':
            node = network[node].first;
            break;
        case 'R':
            node = network[node].second;
            break;
        }
        steps++;
    }

    return steps;
}