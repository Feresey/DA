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
    char *number = new char[to_pos - from_pos]; // По условию 2 - это максимальная длина переводимой строки
    int symbol = 0;                             // Итератор для записи в переменную number
    for (int i = from_pos; i < to_pos - 1; i++)
    {
        number[symbol++] = input_string[i];
    }

    return atoi(number);
}

void Copy(char *to_line, char *from_line)
{
    if (!to_line)
    {
        to_line = new char[LEN];
    }
    for (int pos = 0; from_line[pos] != '\0'; pos++)
    {
        to_line[pos] = from_line[pos];
    }
}

TKey AddKey(char *input)
{
    TKey key;

    char delimiter[2] = {'.', '\t'};
    const int SIZE_OF_DELIMITER = 1;
    int prev_pos = -1;
    int pos = Find(input, 0, delimiter[0]);

    key.date[DAY] = StringToInt(input, prev_pos + SIZE_OF_DELIMITER, pos - prev_pos); //day
    prev_pos = pos;
    pos = Find(input, pos + SIZE_OF_DELIMITER, delimiter[0]);

    key.date[MONTH] = StringToInt(input, prev_pos + SIZE_OF_DELIMITER, pos - prev_pos); //month
    prev_pos = pos;
    pos = Find(input, pos + SIZE_OF_DELIMITER, delimiter[1]);

    key.date[YEAR] = StringToInt(input, prev_pos + SIZE_OF_DELIMITER, pos - prev_pos); //year

    return key;
}
