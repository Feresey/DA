#ifndef SORT_HPP
#define SORT_HPP

#include <cstddef>

template <class T>
void swap(T& one, T& two)
{
    if (&one == &two)
        return;
    T temp = one;
    one = two;
    two = temp;
}

size_t* counts;

// returns array of sorted indexies
template <class First>
size_t* CountingSort(const First* src, const size_t size, unsigned int zdvig, const First mask)
{
    size_t* indexies = new size_t[size];
    for (size_t i = 0; i <= mask; ++i)
        counts[i] = 0;

    for (size_t i = 0; i != size; ++i)
        counts[(src[i] >> zdvig) & mask]++;

    for (size_t i = 0; i != mask; ++i)
        counts[i + 1] += counts[i];
    for (size_t i = size - 1; i + 1 != 0; --i)
        indexies[i] = --counts[(src[i] >> zdvig) & mask];

    return indexies;
}

template <class First, class Second>
void RadixSort(First* numbers, Second* values, size_t size)
{
    First* temp_num = new First[size];
    Second* temp_str = new Second[size];
    unsigned int zdvig = 0;
    const unsigned int elem_size = 8;
    const First mask = (1 << elem_size) - 1;
    counts = new size_t[mask + 1];
    while (zdvig < sizeof(First)*8) {
        size_t* index = CountingSort(numbers, size, zdvig, mask);
        for(size_t i = 0; i != size; ++i){
            temp_num[index[i]] = numbers[i];
            temp_str[index[i]] = values[i];
        }
        swap(temp_num, numbers);
        swap(temp_str, values);
        delete[] index;
        zdvig += elem_size;
    }
    delete[] temp_num;
    delete[] temp_str;
    delete[] counts;
}

#endif /* SORT_HPP */
