#ifndef STRUCT
#define STRUCT
#include <iostream>

using namespace std;

const int MAX = 1000;
const int LEN = 64;
const int DATE = 3; //Day, mounth and year
const int DAY = 0, MONTH = 1, YEAR = 2;
const int DECIMAL = 10;
typedef struct
{
    int date[DATE];
    string *line;
} TKey;

TKey AddKey(string input, string *line);

#endif