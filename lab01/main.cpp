// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Sort.hpp"
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>

template <class Type>
void resize(Type*& data, size_t old_size, size_t new_size)
{
    Type* temp = new Type[new_size];
    memcpy(temp, data, old_size * sizeof(Type));
    delete[] data;
    data = temp;
}

int parse(const char* src)
{
    if (!src || strlen(src) < 8)
        return -1;
    char buf[] = "0000000";
    size_t fill = 0, prev_pos = 0;
    size_t borders[] = { 2, 2, 4 };
    int count = 0;
    while (count != 3) {
        size_t pos = prev_pos;
        while (isdigit(src[pos]))
            ++pos;
        if (src[pos] == '\0')
            return -1;
        fill += borders[count] - pos + prev_pos;
        while (prev_pos != pos)
            buf[fill++] = src[prev_pos++];
        ++prev_pos;
        ++count;
    }

    // yyyy mm dd
    char temp[] = {
        buf[4], buf[5], buf[6], buf[7],
        buf[2], buf[3],
        buf[0], buf[1],
        '\0'
    };

    return atoi(temp);
}

int main()
{
    size_t size = 1, fill = 0;
    unsigned int* numbers = new unsigned int[size];
    char** strings = new char*[size];
    const size_t INPUT_SIZE = 300;
    char input[INPUT_SIZE];
    while (fgets(input, INPUT_SIZE, stdin)) {
        if (!strcmp(input, "\n"))
            continue;
        if (fill == size) {
            size_t size_2 = size * 2;
            resize(numbers, size, size_2);
            resize(strings, size, size_2);
            size = size_2;
        }
        size_t len = strlen(input);
        int res = parse(input);
        if (res < 0)
            continue;
        numbers[fill] = static_cast<unsigned int>(res);
        strings[fill] = new char[len + 1];
        memcpy(strings[fill], input, len + 1);
        ++fill;
    }

    RadixSort(numbers, strings, fill);

    for (size_t i = 0; i != fill; ++i) {
        printf("%s", strings[i]);
        delete[] strings[i];
    }
    delete[] numbers;
    delete[] strings;
    return 0;
}
