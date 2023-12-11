#include "Day9.h"

#include <algorithm>

llong Day9::p1(const std::vector<std::string>& input)
{
    std::vector<std::vector<llong>> sequences;

    for (std::string s : input)
    {
        sequences.push_back(splitLongs(s, ' '));
    }

    llong sum = 0;
    for (std::vector<llong> s : sequences)
    {
        sum += nextInSequence(s);
    }

    return sum;
}

llong Day9::p2(const std::vector<std::string>& input)
{
    std::vector<std::vector<llong>> sequences;

    for (std::string s : input)
    {
        sequences.push_back(splitLongs(s, ' '));
    }

    llong sum = 0;
    for (std::vector<llong> s : sequences)
    {
        sum += prevInSequence(s);
    }

    return sum;
}

llong Day9::nextInSequence(std::vector<llong> sequence)
{
    if (std::all_of(sequence.begin(), sequence.end(), [](llong l) { return l == 0; }))
    {
        return sequence.back();
    }
    else
    {
        std::vector<llong> diffs;
        for (int i = 0; i < sequence.size() - 1; i++)
        {
            diffs.push_back(sequence[i + 1] - sequence[i]);
        }
        return nextInSequence(diffs) + sequence.back();
    }
}

llong Day9::prevInSequence(std::vector<llong> sequence)
{
    if (std::all_of(sequence.begin(), sequence.end(), [](llong l) { return l == 0; }))
    {
        return sequence.front();
    }
    else
    {
        std::vector<llong> diffs;
        for (int i = 0; i < sequence.size() - 1; i++)
        {
            diffs.push_back(sequence[i + 1] - sequence[i]);
        }
        return sequence.front() - prevInSequence(diffs);
    }
}
