#include "Day8.h"

#include <map>

int Day8::p1(const std::vector<std::string>& input)
{
    std::string directions = input[0];
    std::map<std::string, std::pair< std::string, std::string>> network;

    for (int i = 2; i < input.size(); i++)
    {
        std::vector<std::string> tokens = split(input[i], ' ');
        std::string left = tokens[2].substr(1, tokens[2].size() - 2);
        std::string right = tokens[3].substr(0, tokens[3].size() - 1);
        network[tokens[0]] = std::make_pair(left, right);
    }

    std::string node = "AAA";
    int steps = 0;
    while (node != "ZZZ")
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

int Day8::p2(const std::vector<std::string>& input)
{
    return 0;
}
