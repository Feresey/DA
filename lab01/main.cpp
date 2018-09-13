#include <iostream>
#include "struct.hpp"

using namespace std;

bool RadixSort(const TKey *buf1, TKey *buf2, int date, int current_bit)
{
    bool is_max_bit_place = true; //Достигнут максимальный разряд числа
    int write_lines = 0;
    // int date = 0; //для переключения между днём, месяцем и годом

    //todo данные будут перезаписываться, если во втором буфере они уже на своём мест

    is_max_bit_place = false;
    for (int radix = 0; radix < 10; radix++) //пробег по цифрам
    {
        for (int item = 0; item < MAX; item++) //для всех элеменов buf1
        {
            if (buf1[item].date[date] / current_bit % DECIMAL == radix)
            {
                if (is_max_bit_place)
                {
                    is_max_bit_place = true;
                }
            }
        }
    }
    return is_max_bit_place;
}

int main()
{
    int total_lines = 0;
    int bit = 1;
    string *lines = new string[MAX];

    string input;

    TKey *keys1 = new TKey[MAX];
    TKey *keys2 = new TKey[MAX];

    while (getline(cin, input))
    {
        if (input != "")
        {
            keys1[total_lines] = AddKey(input, &lines[total_lines]);
            cout << *keys1[total_lines].line << endl;
            total_lines++;
        }
    }
    for (int time = 0; time < DATE_LENGTH; time++)
    {
        bit = 1;
        while (RadixSort(keys1, keys2, time, bit))
        {
            bit *= DECIMAL;
        }
    }
    delete[] lines;
    delete[] keys1;
    delete[] keys2;
    return 0;
}
