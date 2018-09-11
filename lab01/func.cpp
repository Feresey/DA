#include <iostream>
#include "struct.hpp"

using namespace std;

TKey AddKey(string input, string *line)
{
    TKey key;
    key.line = new string;

    char delimiter[2] = {'.', '\t'};
    int pos;

    pos = input.find(delimiter[0]);
    key.time[0] = stoi(input.substr(0, pos)); //day
    input.erase(0, pos + 1);

    pos = input.find(delimiter[0]);
    key.time[1] = stoi(input.substr(0, pos)); //month
    input.erase(0, pos + 1);

    pos = input.find(delimiter[1]);
    key.time[2] = stoi(input.substr(0, pos)); //year
    input.erase(0, pos + 1);

    *line = input;
    key.line = line;
    // cout << *key.line << endl;

    return key;
}