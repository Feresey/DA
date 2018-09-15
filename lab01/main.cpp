#include <iostream>
#include "struct.hpp"

using namespace std;
int TOTAL_LINES = 0;
void RadixSort(const TKey *buf1, TKey *buf2, int date, int current_bit)
{
    // bool is_max_bit_place = true; //Достигнут максимальный разряд числа
    // int write_lines = 0;
    // int date = 0; //для переключения между днём, месяцем и годом

    //todo данные будут перезаписываться, если во втором буфере они уже на своём мест

    // is_max_bit_place = false;
    for (int radix = 0; radix < 10; radix++) //пробег по цифрам
    {
        for (int item = 0; item < TOTAL_LINES; item++) //для всех элеменов buf1
        {
            if ((buf1[item].date[date] / current_bit) % DECIMAL == radix) //&& buf1[item].date[date] != buf2[item].date[date])
            {
                buf2[item] = buf1[item];
            }
        }
    }
    // return is_max_bit_place;
}

void Prnt(TKey *keys)
{
    for (int i = 0; i < MAX; i++)
    {
        cout << keys[i].date << endl;
    }
}

int main()
{
    int bit = 1;
    int current_date = 0;
    int count = 0;
    string *lines = new string[MAX];

    string input;

    TKey *keys1 = new TKey[MAX];
    TKey *keys2 = new TKey[MAX];
    TKey *buffer[2] = {keys1, keys2};
    while (getline(cin, input))
    {
        if (input != "")
        {
            keys1[TOTAL_LINES] = AddKey(input, &lines[TOTAL_LINES]);
            // cout << *keys1[TOTAL_LINES].line << endl;
            TOTAL_LINES++;
        }
    }

    //todo чот хуйня
    for (int time : TIME_LENGTH)
    {
        for (int current_bit = 0; current_bit < time; current_bit++)
        {
            RadixSort(buffer[count / 2], buffer[count / 2 + 1], current_date, bit);
            bit *= DECIMAL;
            count++;
        }
        current_date++;
    }

    // Prnt(buffer[count / 2]);
    delete[] lines;
    delete[] keys1;
    delete[] keys2;
    return 0;
}
