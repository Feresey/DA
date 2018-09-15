#include <iostream>
#include "struct.hpp"

using namespace std;

TKey AddKey(const std::string input, std::string *line)
{
    TKey key;

    char delimiter[2] = {'.', ' '};
    const int SIZE_OF_DELIMITER = 1;
    int prev_pos = -1;
    int pos = input.find(delimiter[0]);
    int string_length;
    // cout << pos << endl;

    key.date[DAY] = stoi(input.substr(prev_pos + SIZE_OF_DELIMITER, pos - prev_pos)); //day
    prev_pos = pos;
    pos = input.find(delimiter[0], pos + SIZE_OF_DELIMITER);
    // cout << pos << endl;
    key.date[MONTH] = stoi(input.substr(prev_pos + SIZE_OF_DELIMITER, pos - prev_pos)); //month
    prev_pos = pos;
    pos = input.find(delimiter[1], pos + SIZE_OF_DELIMITER);
    // cout << pos << endl;

    key.date[YEAR] = stoi(input.substr(prev_pos + SIZE_OF_DELIMITER, pos - prev_pos)); //year

    string_length = input.length() - (pos + SIZE_OF_DELIMITER);
    cout << string_length << endl;
    *line = input.substr(pos + SIZE_OF_DELIMITER, string_length) + empty_string.substr(0, LEN - string_length); //input line without key
    key.line = line;

    return key;
}
