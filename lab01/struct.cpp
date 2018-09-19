#include <iostream>
#include "struct.hpp"

using namespace std;

TKey AddKey(const std::string input, std::string *line){
    TKey key;

    char delimiter[2] = {'.', '\t'};
    const int SIZE_OF_DELIMITER = 1;
    int prev_pos = -1;
    int pos = input.find(delimiter[0]);

    key.date[DAY] = stoi(input.substr(prev_pos + SIZE_OF_DELIMITER, pos - prev_pos)); //day
    prev_pos = pos;
    pos = input.find(delimiter[0], pos + SIZE_OF_DELIMITER);

    key.date[MONTH] = stoi(input.substr(prev_pos + SIZE_OF_DELIMITER, pos - prev_pos)); //month
    prev_pos = pos;
    pos = input.find(delimiter[1], pos + SIZE_OF_DELIMITER);

    key.date[YEAR] = stoi(input.substr(prev_pos + SIZE_OF_DELIMITER, pos - prev_pos)); //year

    *line = input;

    return key;
}

