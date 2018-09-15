#include <iostream>
#include "struct.hpp"

using namespace std;

TKey AddKey(const string input, string *line)
{
    TKey key;

    char delimiter[2] = {'.', '\t'};
    int prev_pos = -1;
    int pos = input.find(delimiter[0]);

    key.date[DAY] = stoi(input.substr(prev_pos + 1, pos - prev_pos)); //day
    prev_pos = pos;
    pos = input.find(delimiter[0], pos + 1);

    key.date[MONTH] = stoi(input.substr(prev_pos + 1, pos - prev_pos)); //month
    prev_pos = pos;
    pos = input.find(delimiter[1], pos + 1);

    key.date[YEAR] = stoi(input.substr(prev_pos + 1, pos - prev_pos)); //year

    *line = input.substr(pos + 1, input.length()); //input line without key
    key.line = line;

    return key;
}