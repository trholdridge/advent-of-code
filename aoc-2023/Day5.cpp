#include "Day5.h"

#include <algorithm>
#include <iostream>
#include <queue>

llong Day5::p1(const std::vector<std::string>& input)
{
    this->seeds = splitLongs(input[0].substr(7), ' ');
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

llong Day5::p2(const std::vector<std::string>& input)
{
    this->seeds = splitLongs(input[0].substr(7), ' ');
    std::vector<Range> srcs;
    for (int i = 0; i < this->seeds.size(); i += 2)
    {
        srcs.push_back(std::make_pair(this->seeds[i], this->seeds[i + 1]));
    }
    buildMaps(input);

    for (const AlmanacMap& m : this->maps)
    {
        srcs = destsOf(srcs, m);
    }

    return (*std::min_element(srcs.begin(), srcs.end(),
        [](const Range& a, const Range& b)
        {
            return a.first < b.first;
        })).first;
}

std::vector<Range> Day5::destsOf(const std::vector<Range>& srcs, const AlmanacMap& m)
{
    std::vector<Range> results;
    std::vector<Range> temp;
    for (Range s : srcs)
    {
        temp = destsOf(s, m);
        results.insert(results.end(), temp.begin(), temp.end());
    }
    return results;
}

std::vector<Range> Day5::destsOf(Range& src, const AlmanacMap& m)
{
    // Range will become fragmented over time, all pieces must be processed
    std::queue<Range> queue({ src });

    std::vector<Range> dests;
    while (!queue.empty())
    {
        Range r = queue.front();
        queue.pop();
        bool foundOverlap = false;
        llong srcStart = r.first;
        llong srcEnd = r.first + r.second;
        for (const auto& [key, dest] : m)
        {
            llong mapStart = key.first;
            llong mapEnd = key.first + key.second;
            if (!(srcEnd <= mapStart || srcStart >= mapEnd))
            {
                if (mapStart > srcStart)
                {
                    queue.push(std::make_pair(srcStart, mapStart - srcStart));
                }
                if (mapEnd < srcEnd)
                {
                    queue.push(std::make_pair(mapEnd, srcEnd - mapEnd));
                }
                dests.push_back(std::make_pair(dest + (std::max(srcStart, mapStart) - mapStart),
                    std::min(srcEnd, mapEnd) - std::max(srcStart, mapStart)));
                foundOverlap = true;
            }
        }
        if (!foundOverlap)
        {
            dests.push_back(r);
        }
    }
    return dests;
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
                std::vector<llong> nums = splitLongs(s, ' ');
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