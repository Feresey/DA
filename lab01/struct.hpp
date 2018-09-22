#ifndef STRUCT_H
#define STRUCT_H
#include <iostream>

const int LEN = 78;
const int MAX = 100000;
const int DATE_LENGTH = 3; //Day, mounth and year
const int DAY = 0, MONTH = 1, YEAR = 2;
const int TIME_LENGTH[3] = {2, 2, 4};
const int DECIMAL = 10;

struct TKey{
    unsigned short int date[DATE_LENGTH]; //Day, mounth and year
    char line[LEN];                        //указатель на строку (для экономии памяти)
};

TKey AddKey(char * input);

void Copy(char *to_line, char *from_line);

template <typename T>
T *Resize(T array[], size_t total_length, size_t size){
    T *res = new T[size];

    for (size_t i = 0; i < total_length; i++){
        res[i] = array[i];
    }

    delete[] array;
    return res;
}
#endif //STRUCT_H
