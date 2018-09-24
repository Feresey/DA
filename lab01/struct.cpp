#include "struct.hpp"
#include <iostream>

// using namespace std;

int Find(const char *line, size_t start_pos, const char delimiter)
{
    for (int pos = start_pos; line[pos] != '\0'; pos++)
    {
        if (line[pos] == delimiter)
        {
            return pos;
        }
    }

    return -1;
}

int StringToInt(char *input_string, size_t from_pos, size_t to_pos)
{
    char *number = new char[to_pos - from_pos+1]; // По условию 2 - это максимальная длина переводимой строки
    int symbol = 0;                             // Итератор для записи в переменную number
    for (int i = from_pos; i < to_pos; i++)
    {
        number[symbol++] = input_string[i];
    }
    number[symbol] = '\0';
    return atoi(number);
}

void Copy(char *to_line, char *from_line)
{
    int pos;
    for (pos = 0; from_line[pos] != '\n'; pos++)
    {
        to_line[pos] = from_line[pos];
    }
    to_line[pos] = '\0';
}

TKey AddKey(char *input)
{
    TKey key;

    char delimiter[2] = {'.', '\t'};
    const int SIZE_OF_DELIMITER = 1;
    int prev_pos = -1;
    int pos = Find(input, 0, delimiter[0]);

    key.date[DAY] = StringToInt(input, prev_pos + SIZE_OF_DELIMITER, pos); //day
    prev_pos = pos;
    pos = Find(input, pos + SIZE_OF_DELIMITER, delimiter[0]);

    key.date[MONTH] = StringToInt(input, prev_pos + SIZE_OF_DELIMITER, pos); //month
    prev_pos = pos;
    pos = Find(input, pos + SIZE_OF_DELIMITER, delimiter[1]);

    key.date[YEAR] = StringToInt(input, prev_pos + SIZE_OF_DELIMITER, pos); //year

    key.line = new char[LEN];

    return key;
}
