#ifndef TTREE_H
#define TTREE_H

#include <cstring>
#include <math.h>
#include <iostream>

// #define ull unsigned long long

using namespace std;
const int LENGTH = 255;

class TTree {
public:
    TTree();
    TTree(char* str);
    ~TTree();

    TTree* Search(char* new_key);
    bool Insert(TTree* new_item);
    // friend bool operator==(const TTree &left, const TTree &right);
    void Show(int);
    void Show() { Show(0); }

// private:
    TTree* left;
    TTree* right;
    char* key;
    // ull item;
    int bit;

    // TTree *SearchR(TTree *node, char *new_key, int digit);
    // TTree *InsertR(TTree *node, TTree *new_item, int digit, TTree *root);
};

// bool And(const char *left, const char *right, int bit);
// bool equal(char *left, char *right);

class TPATRICIA {
    friend TTree;

private:
    TTree* root;
    // void Remove_();

public:
    TPATRICIA();
    ~TPATRICIA();
    bool Insert(TTree* itm);
    TTree* Search(char* str);
    TTree* SearchPR(TTree* node, char* str, int digit);
    bool Remove(char* str);
};

bool getBit(char* str, int bit);

#endif // TTREE_H
