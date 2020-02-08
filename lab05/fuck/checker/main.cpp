#include "suffixTree.h"
#include <iostream>

int main()
{
    // std::ios_base::sync_with_stdio(false);
    std::string pattern, text;
    std::cin >> pattern >> text;
    TSuffixTree tree(pattern + '$');
    size_t count = 1;
    for (auto i : tree.Find(text)) {
        if (i == pattern.size())
            std::cout << count << "\n";
        ++count;
    }

    return 0;
}