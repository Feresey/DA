#include <iostream>
#include <map>
#include "TSuffixTree.hpp"



int main()
{
    std::string text;
    std::cin >> text;
    // text += "\n";
    // text.append("\0");
    TSuffixTree tree(text);
    return 0;
}