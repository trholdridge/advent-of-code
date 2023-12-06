#include "Day6.h"

#include <algorithm>
#include <iterator>

int Day6::p1(const std::vector<std::string>& input)
{
    std::vector<int> times = splitInts(input[0].substr(5), ' ');
    std::vector<int> distances = splitInts(input[1].substr(9), ' ');

    int product = 1;
    for (int i = 0; i < times.size(); i++)
        product *= waysToBeat(times[i], distances[i]);
    return product;
}

int Day6::p2(const std::vector<std::string>& input)
{
    std::string timeStr;
    std::string distanceStr;
    std::copy_if(input[0].begin(), input[0].end(), std::back_inserter(timeStr),
        [](const char c) { return digit(c); });
    std::copy_if(input[1].begin(), input[1].end(), std::back_inserter(distanceStr),
        [](const char c) { return digit(c); });
    llong time = std::stoll(timeStr);
    llong distance = std::stoll(distanceStr);

    return waysToBeat(time, distance);
}

llong Day6::waysToBeat(llong time, llong distance)
{
    int minPress;
    int maxPress;

    for (minPress = 0; minPress * (time - minPress) <= distance; minPress++) {}
    for (maxPress = time; maxPress * (time - maxPress) <= distance; maxPress--) {}

    return maxPress - minPress + 1;
}