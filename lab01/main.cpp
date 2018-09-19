#include <iostream>
#include "struct.hpp"
#include <stdio.h>

using namespace std;

int TOTAL_LINES = 0;

void RadixSort(const TKey *buf1, TKey *buf2, const int &date, const int &current_bit){
    int write_lines = 0;
    int digit = 0; //текущая цифра

    while (write_lines < TOTAL_LINES){
        for (int item = 0; item < TOTAL_LINES; item++){ //для всех элеменов buf1
            if ((buf1[item].date[date] / current_bit) % DECIMAL == digit){ // равна ли цифра текущей проверяемой
                if (buf2[write_lines].line != buf1[item].line){ //защита от перезаписи
                    buf2[write_lines] = buf1[item];
                }
                write_lines++;
            }
        }
        digit++; //увеличение проверяемой цифры на 1
    }
}

int main(){
    int bit = 1;
    int current_date = 0;
    int count = 0;

    string *lines = new string[MAX]; //для хранения строк (можно и в самом ключе, но это боле затратно)
    string input;

    TKey *keys1 = new TKey[MAX]; //основной массив ключей 
    ios_base::sync_with_stdio(false); //? нашел на сайте, так чуть быстрее

    while (getline(cin, input)){
        if (input != ""){
            keys1[TOTAL_LINES] = AddKey(input, &lines[TOTAL_LINES]); //добавление нового ключа
            TOTAL_LINES++;
            if (TOTAL_LINES % MAX == MAX - 1){ //довыделение памяти, если необходимо
                lines = Resize(lines, TOTAL_LINES, TOTAL_LINES + MAX);
                keys1 = Resize(keys1, TOTAL_LINES, TOTAL_LINES + MAX);
            }
        }
    }

    for (size_t i = 0; i < TOTAL_LINES; i++){ //и создание новых ссылок на строки у каждого из ключей
        keys1[i].line = &lines[i];
    }

    TKey *keys2 = new TKey[TOTAL_LINES]; //вспомогательный буффер для сортировки
    TKey *keys[2] = {keys1, keys2}; //ну надо же переключаться между буферами

    for (int time : TIME_LENGTH){ //длина дня, месяца и года
        bit = 1;
        for (int current_bit = 0; current_bit < time; current_bit++){ //цикл для каждого десятка
            RadixSort(keys[count % 2], keys[(count + 1) % 2], current_date, bit);
            bit *= DECIMAL; //переход на следующую цифру
            count++;        //для смены первого и второго буферов
        }
        current_date++; //надеюсь, очевидно :D
    }

    for (int i = 0; i < TOTAL_LINES; i++){
        printf("%s\n", keys[count % 2][i].line->c_str());
        //так работает на 0.2 секунды быстрее чем cout
    }

    delete[] lines;
    delete[] keys1;
    delete[] keys2;

    return 0;
}
