#include "struct.hpp"
#include <cstdio>
#include <iostream>
#include <stdio.h>

int main(){
    int TOTAL_LINES = 0;

    int bit = 1;
    int current_date = 0;
    int count = 0;

    char **lines = new char *[MAX]; //для хранения строк (можно и в самом ключе, но это боле затратно)
    char *input = new char[LEN];

    TKey *keys1 = new TKey[MAX]; //основной массив ключей

    // ios_base::sync_with_stdio(false);
    //? нашел на сайте, так чуть быстрее но valgrind выдает ошибки освобождения памяти,
    //? хотя конечный счётчик ошибок выгдядит так:
    //? ERROR SUMMARY: 0 errors from 0 contexts
    // cin.tie(NULL);

    while (fgets(input, LEN, stdin)){
        if (*input != '\n'){
            lines[TOTAL_LINES] = new char[LEN];
            
            Copy(lines[TOTAL_LINES], input);
            keys1[TOTAL_LINES] = AddKey(input); //добавление нового ключа
            
            TOTAL_LINES++;

            if (TOTAL_LINES % MAX == MAX - 1){ //довыделение памяти, если необходимо
                lines = Resize(lines, TOTAL_LINES, TOTAL_LINES + MAX);
                keys1 = Resize(keys1, TOTAL_LINES, TOTAL_LINES + MAX);
            }
        }
    }

    for (size_t i = 0; i < TOTAL_LINES; i++){ //создание ссылок на строки у каждого из ключей
        keys1[i].line = lines[i];
    }

    TKey *keys2 = new TKey[TOTAL_LINES]; //вспомогательный буффер для сортировки
    TKey *keys[2] = {keys1, keys2};      //ну надо же переключаться между буферами

    for (int time : TIME_LENGTH){ //длина дня, месяца и года
        bit = 1;
        for (int current_bit = 0; current_bit < time; current_bit++){ //цикл для каждого десятка
            RadixSort(keys[count % 2], keys[(count + 1) % 2], current_date, bit, TOTAL_LINES);
            bit *= DECIMAL; //переход на следующую цифру
            count++;        //для смены первого и второго буферов
        }
        current_date++; //надеюсь, очевидно :D
    }

    for (int i = 0; i < TOTAL_LINES; i++){
        std::cout << keys[count % 2][i].line << std::endl;
    }

    for (int i = 0; i < TOTAL_LINES; i++){
        delete[] lines[i];
    }

    delete[] lines;
    delete[] input;
    delete[] keys1;
    delete[] keys2;

    return 0;
}
