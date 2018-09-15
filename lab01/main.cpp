#include <iostream>
#include "struct.hpp"

using namespace std;
int TOTAL_LINES = 0;
void RadixSort(TKey *buf1, TKey *buf2, const int date, const int current_bit)
{
    int write_lines = 0;
    int digit = 0; //текущая цифра

    while (write_lines < TOTAL_LINES)
    {
        for (int item = 0; item < TOTAL_LINES; item++) //для всех элеменов buf1
        {
            if ((buf1[item].date[date] / current_bit) % DECIMAL == digit) // равна ли цифра текущей проверяемой
            {
                buf2[write_lines++] = buf1[item];
            }
        }
        digit++; //увеличение проверяемой цифры на 1
    }
}

int main()
{
    int bit = 1;
    int current_date = 0;
    int count = 0;

    string *lines = new string[MAX];

    string input;

    TKey *input_lines = new TKey[MAX];
    TKey *second_buffer = new TKey[MAX];
    TKey *buffer[2] = {input_lines, second_buffer};

    while (getline(cin, input))
    {
        if (input != "")
        {
            input_lines[TOTAL_LINES] = AddKey(input, &lines[TOTAL_LINES]);
            TOTAL_LINES++;
        }
    }

    for (int time : TIME_LENGTH) //длина дня, месяца и года
    {
        bit = 1;
        for (int current_bit = 0; current_bit < time; current_bit++) //цикл для каждого десятка
        {
            RadixSort(buffer[count % 2], buffer[(count + 1) % 2], current_date, bit);
            bit *= DECIMAL; //переход на следующую цифру
            count++;        //для смены первого и второго буферов
        }
        current_date++; //надеюсь, очевидно :D
    }

    for (int i = 0; i < TOTAL_LINES; i++)
    {
        cout << *buffer[count % 2][i].line << endl;
    }

    delete[] lines;
    delete[] input_lines;
    delete[] second_buffer;

    return 0;
}
