#include "Day5.h"

#include <algorithm>
#include <iostream>

int Day5::p1(const std::vector<std::string>& input)
{
    this->seeds = splitNums(input[0].substr(7), ' ');
    buildMaps(input);
    std::vector<llong> results(this->seeds);

    for (AlmanacMap m : this->maps)
    {
        for (llong& i : results)
        {
            i = almanac(m, i);
        }
    }

    return *std::min_element(results.begin(), results.end());
}

int Day5::p2(const std::vector<std::string>& input)
{
    return 0;
}

void Day5::buildMaps(const std::vector<std::string>& input)
{
    int map_idx = -1;
    for_each(input.begin() + 2, input.end(),
        [this, &map_idx](std::string s)
        {
            if (s.length() < 1)
            {
                return;
            }
            else if (digit(s[0]))
            {
                std::vector<llong> nums = splitNums(s, ' ');
                this->maps[map_idx][std::make_pair(nums[1], nums[2])] = nums[0];
            }
            else
            {
                this->maps.push_back(AlmanacMap{});
                map_idx++;
            }
        });
}

llong Day5::almanac(const AlmanacMap& m, const llong i)
{
    for (const auto& [key, dest] : m)
    {
        llong src = key.first;
        llong range = key.second;
        if (i - src >= 0 && i - src < range)
        {
            return dest + (i - src);
        }
    }
    return i;
}