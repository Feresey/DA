#ifndef STRUCT_H
#define STRUCT_H
#include <iostream>

using namespace std;

const int MAX = 1000;
const int LEN = 64;
const int DATE_LENGTH = 3; //Day, mounth and year
const int DAY = 0, MONTH = 1, YEAR = 2;
const int TIME_LENGTH[3] = {2, 2, 4};
const int DECIMAL = 10;

typedef struct
{
    int date[DATE_LENGTH]; //Day, mounth and year
    string *line;          //указатель на строку (для экономии памяти)
} TKey;

void prnt(TKey *a);

TKey AddKey(string input, string *line);

#endif //STRUCT_H