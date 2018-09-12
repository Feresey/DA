#include <iostream>
#include "struct.hpp"

using namespace std;

void RadixSort(const TKey *buf1, TKey *buf2, const int keyname)
{
    int current_bit = 1;
    int write_lines = 0;
    do
    {
        for (int i = 0; i < DECIMAL; i++)
        {
            for (int item = 0; item < MAX; i++)
            {
                if (buf1[item].date[keyname] % (current_bit * DECIMAL) / current_bit == i)
                {
                    buf2[write_lines++] = buf1[i];
                }
            }
            current_bit *= DECIMAL;
        }
    } while (write_lines != 0);
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
            cout << *keys1[total_lines].line << endl;
            total_lines++;
        }
    }

    // RadixSort(keys1, keys2, DAY);
    delete[] lines;
    delete[] keys1;
    delete[] keys2;
    return 0;
}
