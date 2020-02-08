#include <iostream>

#include "TTree.hpp"

using namespace std;

int main()
{
    // char *l = new char[LENGTH];
    // char *r = new char[LENGTH];
    // std::cin >> l >> r;
    // for (int i = 0; i < 8; i++)
    //     std::cout << And(l, r, i);

    // equal(l,r);

    char *inp = new char[LENGTH];
    // cin >> inp;
    TTree *node = new TTree();
    node->Show(0);
    TTree *ins;
    while (cin >> inp)
    {
        ins = new TTree(inp);
        if (!node->Insert(ins))
            delete ins;
        node->Show();
    }

    delete node;
    delete[] inp;
    // delete[] l;
    // delete[] r;
    return 0;
}