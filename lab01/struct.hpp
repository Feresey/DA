#ifndef STRUCT_H
#define STRUCT_H
#include <iostream>

const int MAX = 200000;
const int LEN = 64;
const int DATE_LENGTH = 3; //Day, mounth and year
const int DAY = 0, MONTH = 1, YEAR = 2;
const int TIME_LENGTH[3] = {2, 2, 4};
const int DECIMAL = 10;

struct TKey
{
    unsigned short int date[DATE_LENGTH]; //Day, mounth and year
    std::string *line;                                              //указатель на строку (для экономии памяти)
};
TKey AddKey(std::string input, std::string *line);

#endif //STRUCT_H
