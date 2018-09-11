#ifndef STRUCT
#define STRUCT
#include <iostream>

using namespace std;

const int MAX=1000,LEN=64;

typedef struct
{
    int day;
    int mounth;
    int year;
    string *line;
} TKey;

TKey AddKey(string input, string* line);

#endif