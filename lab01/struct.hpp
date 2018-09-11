#ifndef STRUCT
#define STRUCT
#include <iostream>

using namespace std;

const int MAX = 1000;
const int LEN = 64;
const int DATE = 3; //Day, mounth and year

typedef struct
{
    int time[3];
    string *line;
} TKey;

TKey AddKey(string input, string *line);

#endif