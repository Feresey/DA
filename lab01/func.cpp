#include "struct.hpp"
#include <iostream>
using namespace std;

TKey AddKey(string input, string *line)
{
    TKey key;
    key.line = new string;

    char delimiter = '.';
    char tab = '\t';

    key.day = stoi(input.substr(0, input.find(delimiter)));
    input.erase(0, input.find(delimiter) + 1);

    key.mounth = stoi(input.substr(0, input.find(delimiter)));
    input.erase(0, input.find(delimiter) + 1);

    key.mounth = stoi(input.substr(0, input.find(tab)));
    input.erase(0, input.find(tab) + 1);

    *line=input;
    key.line = line;
    // cout << *key.line << endl;

    return key;
}