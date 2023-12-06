#include "Day6.h"

int Day6::p1(const std::vector<std::string>& input)
{
    this->times = splitInts(input[0].substr(5), ' ');
    this->distances = splitInts(input[1].substr(9), ' ');

    int product = 1;
    for (int i = 0; i < times.size(); i++)
        product *= waysToBeat(times[i], distances[i]);
    return product;
}

int Day6::p2(const std::vector<std::string>& input)
{
    return 0;
}

int Day6::waysToBeat(int time, int distance)
{
    int minPress;
    int maxPress;

    for (minPress = 0; minPress * (time - minPress) <= distance; minPress++) {}
    for (maxPress = time; maxPress * (time - maxPress) <= distance; maxPress--) {}

    return maxPress - minPress + 1;
}