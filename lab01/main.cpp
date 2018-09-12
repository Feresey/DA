#include <iostream>
#include "struct.hpp"

using namespace std;

void RadixSort(TKey *buf1, TKey *buf2, int keyname)
{
    bool if_max_bit_place = false; //Достигнут максимальный разряд числа
    int current_bit = 10;

    for (int i = 0; i < DECIMAL; i++)
    {
    }
}

int main()
{
    int total_lines = 0;

    string *lines = new string[MAX];
    string input;

    TKey *keys1 = new TKey[MAX];
    TKey *keys2 = new TKey[MAX];

    while (getline(cin, input))
    {
        if (input != "")
        {
            keys1[total_lines] = AddKey(input, &lines[total_lines]);
            total_lines++;
        }
    }

    RadixSort(keys1, keys2, DAY);

    return 0;
}
