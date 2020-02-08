// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "TBor.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>


int main()
{
    TAho* root = new TAho();
    std::vector<std::string> keys;
    std::vector<std::pair<int, int>> res;
    char temp[MAX_WORD_LENGTH];
    std::string inp;
    int word_num = 1, line_num = 1;

    root->AddKeys();

    while (getline(std::cin, inp)) {
        std::transform(inp.begin(), inp.end(), inp.begin(), tolower);
        std::stringstream line(inp);
        while (line >> temp) {
            keys.push_back(temp);
            res.push_back(std::make_pair(line_num, word_num++));
        }
        ++line_num;
        word_num = 1;
    }

    root->Search(keys,res);
    delete root;
    return 0;
}
