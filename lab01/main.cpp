#include "struct.hpp"
#include <cstdio>
#include <iostream>

int main(){
    int TOTAL_LINES = 0;

    int bit = 1;
    int current_date = 0;
    int count = 0;

    char *input = new char[LEN];

    TKey *keys1 = new TKey[MAX]; //основной массив ключей

    while (fgets(input, LEN, stdin)){
        if (*input != '\n'){
            keys1[TOTAL_LINES] = AddKey(input); //добавление нового ключа
            
            TOTAL_LINES++;
            if (TOTAL_LINES % MAX == MAX - 1){ //довыделение памяти, если необходимо
                keys1 = Resize(keys1, TOTAL_LINES, TOTAL_LINES + MAX);
            }
        }
    }

    TKey *keys2 = new TKey[TOTAL_LINES]; //вспомогательный буффер для сортировки
    TKey *keys[2] = {keys1, keys2};      //ну надо же переключаться между буферами

    for (int time: TIME_LENGTH){ //длина дня, месяца и года
        bit = 1;
        for (int current_bit = 0; current_bit < time; current_bit++){ //цикл для каждого десятка
            RadixSort(keys[count % 2], keys[(count + 1) % 2], current_date, bit, TOTAL_LINES);
            bit *= DECIMAL; //переход на следующую цифру
            count++;        //для смены первого и второго буферов
        }
        current_date++; //надеюсь, очевидно :D
    }

    for (int i = 0; i < TOTAL_LINES; i++){
        printf("%s\n", keys[count % 2][i].line);
    }

    for (int i = 0; i < TOTAL_LINES; i++){
        delete[] keys1[i].line;
    }
    delete[] input;
    delete[] keys1;
    delete[] keys2;

    return 0;
}
