#ifndef PATR_PATRICIATREE_H
#define PATR_PATRICIATREE_H

#include "iostream"
#include <cstring>
#include <fstream>

#define ull unsigned long long

const int LEN = 257;

class TTree {
public:
    TTree();
    TTree(const TTree&);
    const ull* Search(const char*, int);
    bool Insert(const char*, int, ull);
    bool Remove(const char*, int);
    void Load(const char*);
    void Save(const char*);

    TTree& operator=(const TTree&);

    ~TTree();

private:
    TTree* right;
    TTree* left;
    char* key;
    int length;
    ull data;
};

#endif //PATR_PATRICIATREE_H
