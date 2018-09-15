#include <iostream>
#include "struct.hpp"

using namespace std;
int TOTAL_LINES = 0;

// void prnt(TKey *a);

void RadixSort(TKey *buf1, TKey *buf2, const int date, const int current_bit)
{
    int write_lines = 0;
    int digit = 0;
    prnt(buf1);
    // cout << "write" << endl;
    while (digit < TOTAL_LINES)
    {
        for (int item = 0; item < TOTAL_LINES; item++) //для всех элеменов buf1
        {
            if ((buf1[item].date[date] / current_bit) % DECIMAL == digit) // равна ли цифра текущей проверяемой
            {
                // if (buf1[item].line != buf2[write_lines].line) //защита от перезаписи
                // {
                buf2[write_lines] = buf1[item];
                cout << "item " << item << " bit " << current_bit << " date " << date << " digit " << digit << ' ' << *buf1[item].line << endl;

                // }
                write_lines++;
            }
        }
        digit++; //увеличение проверяемой цифры на 1
    }
    cout << endl;
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
        bit = 1;
        for (int current_bit = 0; current_bit < time; current_bit++)
        {
            RadixSort(buffer[count % 2], buffer[(count + 1) % 2], current_date, bit);
            bit *= DECIMAL;
            count++;
        }
        current_date++;
    }

    prnt(buffer[count % 2]);

    // Prnt(buffer[(count) % 2]);
    delete[] lines;
    delete[] keys1;
    delete[] keys2;
    return 0;
}

void prnt(TKey *a)
{

    for (int i = 0; i < TOTAL_LINES; i++)
    {
        cout << *a[i].line << endl;
    }
}