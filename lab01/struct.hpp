#ifndef STRUCT_H
#define STRUCT_H
#include <iostream>

const int LEN = 78;
const int MAX = 100000;
const int DATE_LENGTH = 3; //Day, mounth and year
const int DAY = 0, MONTH = 1, YEAR = 2;
const int TIME_LENGTH[3] = {2, 2, 4};
const int DECIMAL = 10;

struct TKey
{
    unsigned short int date[DATE_LENGTH]; //Day, mounth and year
    char *line;                           //указатель на строку (для экономии памяти)
};

TKey AddKey(char *input);

void Copy(char *to_line, char *from_line);

TKey *Resize(TKey *array, size_t total_length, size_t size);

char **Resize(char **array, size_t total_length, size_t size);

#endif //STRUCT_H
