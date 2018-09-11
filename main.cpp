#include <iostream>
#include "struct.hpp"

using namespace std;

int main()
{
    string *lines = new string[MAX];
    TKey *keys1 = new TKey[MAX];
    TKey *keys2 = new TKey[MAX];
    string input;
    int total_lines = 0;
    while (getline(cin, input))
    {
        if (input != "")
        {
            keys1[total_lines] = AddKey(input, &lines[total_lines]);
            cout << *keys1[total_lines].line << endl; 
            total_lines++;
        }
    }

    return 0;
}
