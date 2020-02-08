#include "TTree.hpp"
#include <fstream>
#include <iostream>
#include <malloc.h>

using std::cin;
using std::cout;
using std::endl;

char* ToLower(char* t)
{
    long unsigned len = strlen(t);
    for (int i = 0; i < len; ++i) {
        t[i] = static_cast<char>(std::tolower(t[i]));
    }
    return t;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL);
    char choice;
    char temp[LEN];
    TTree* p = new TTree();
    ull data;
    int len;

    while (std::cin >> choice) {
        switch (choice) {
        case '+': {
            std::cin >> temp >> data;
            len = static_cast<int>(strlen(ToLower(temp)));

            if (p->Insert(temp, len, data)) {
                std::cout << "OK\n";
            } else {
                std::cout << "Exist\n";
            }
            break;
        }
        case '-': {
            std::cin >> temp;
            len = static_cast<int>(strlen(ToLower(temp)));

            if (p->Remove(temp, len)) {
                std::cout << "OK\n";
            } else {
                std::cout << "NoSuchWord\n";
            }
            break;
        }
        case '!': {
            std::cin >> temp;

            if (*temp == 'S') {
                std::cin >> temp;
                p->Save(temp);
            }
            if (*temp == 'L') {
                delete p;
                std::cin >> temp;
                p = new TTree();
                p->Load(temp);
            }
            break;
        }
        default: {
            cin.putback(choice);
            std::cin >> temp;

            len = static_cast<int>(strlen(ToLower(temp)));
            const ull* d = p->Search(temp, len);

            if (d == nullptr) {
                std::cout << "NoSuchWord\n";
            } else {
                std::cout << "OK: " << *d << '\n';
                d = nullptr;
            }
        }
        }
    }

    // delete p;
    return 0;
}
