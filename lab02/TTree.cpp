#include "TTree.hpp"
// #include <stdio.h>

TTree::TTree()
{
    left = right = this;
    // item = 0;
    bit = -1;
    key = new char[LENGTH];
    for (int i = 0; i < LENGTH - 1; i++)
        key[i] = '\0';
}

TTree::TTree(char *str)
    : TTree()
{
    strcpy(key, str);
}

TTree::~TTree()
{
    if (right)
    {
        if (right->bit <= this->bit)
            right = nullptr;
        else
            delete right;
    }
    if (left)
    {
        if (left->bit <= this->bit)
            left = nullptr;
        else
            delete left;
    }
    delete[] key;
}

TPATRICIA::TPATRICIA()
{
    root = new TTree();
    root->right = nullptr;
    root->left = root;
}

TPATRICIA::~TPATRICIA()
{
    delete root;
}

TTree *TPATRICIA::SearchPR(TTree *node, char *str, int digit)
{
    if (node->bit <= digit)
        return node;
    if (getBit(str, node->bit))
    {
        if (node->right->bit > node->bit)
            return SearchPR(node->right, str, node->bit);
        else
            return node;
    }
    else
    {
        if (node->left->bit > node->bit)
            return SearchPR(node->left, str, node->bit);
        else
            return node;
    }
}

TTree *TPATRICIA::Search(char *str)
{
    TTree *max_mask = SearchPR(root->left, str, -1);
    TTree *right_mask = strcmp(max_mask->right->key, str) ? max_mask->right : nullptr;
    TTree *left_mask = strcmp(max_mask->left->key, str) ? max_mask->left : nullptr;

    return (left_mask) ? left_mask : right_mask;
    // return (!strcmp(str, max_mask->key)) ? max_mask : nullptr;
}

bool TPATRICIA::Insert(TTree *itm)
{
    TTree *max_mask = SearchPR(root->left, itm->key, -1);
}

bool equal(char *left, char *right)
{
    int i = 0;
    while (left[i] == right[i])
    {
        // printf("%d\t%d\n", left[i],right[i]);
        if (left[i] == '\0' || right[i] == '\0')
            return false;
        if (i >= LENGTH - 1)
            return false;
        i++;
    }

    return i == LENGTH - 1;
}

bool And(const char *left, const char *right, const unsigned int bit)
{                                  // Коньюнкция по указанному биту для соответствующих символов из двух данных строк
    int mask = 1 << (8 - bit % 8); // запись одной единички, в двоичном представлении, в число, на позицию bit, считая от левого конца байта
    char r_item = right[bit / 8];
    char l_item = left[bit / 8];
    return (l_item & mask) & (r_item & mask);
}

bool getBit(char *str, int bit)
{
    int mask = 1 << (7 - bit % 8);
    // int mask = pow(2, 8) - pow(2, 1 + bit % 8);
    // char item = str[bit / 8];
    return str[bit / 8] & mask;
}

// TTree* TTree::SearchPR(TTree* node, char* str, int digit)
// {
//     if (node->bit <= digit) // Условие сработает, когда мы перейдём по связи "вверх"
//         return node;
//     if (getBit(str, node->bit))
//         return SearchPR(node->right, str, node->bit);
//     else
//         return SearchPR(node->left, str, node->bit);
// }

// TTree* TTree::Search(char* str)
// {
//     TTree* res = SearchPR(this, str, -1);
//     return (equal(str, res->key)) ? res : nullptr;
// }

// TTree* TTree::InsertR(TTree* node, TTree* new_item, int diff, TTree* root)
// {
//     if ((node->bit >= diff) || (node->bit <= root->bit)) {
//         // root->bit = diff;
//         // cout << diff << endl;
//         // for (new_item->bit = diff; new_item->key[new_item->bit] != '\0'; new_item->bit++)
//         // ;
//         new_item->bit = diff;
//         new_item->left = (getBit(new_item->key, diff) ? node : new_item);
//         new_item->right = (getBit(new_item->key, diff) ? new_item : node);

//         return new_item;
//     }

//     if (!getBit(new_item->key, node->bit))
//         node->left = InsertR(node->left, new_item, diff, node);
//     else
//         node->right = InsertR(node->right, new_item, diff, node);

//     return node;
// }

// bool TTree::Insert(TTree* new_item)
// {
//     if (right == left && strlen(key) == 0) {
//         strcpy(key, new_item->key);
//         for (bit = LENGTH - 2; !getBit(key, bit) && bit > 0; bit--)
//             ;
//         // bit *= 8;
//         return false;
//     }
//     int i;
//     TTree* w = SearchPR(left, new_item->key, -1);

//     if (equal(new_item->key, w->key)) {
//         delete new_item;
//         cout << "equal items\n";
//         return false;
//     }
//     for (i = 0; getBit(new_item->key, i) == getBit(w->key, i); i++)
//         ;
//     //? left ?
//     left = InsertR(left, new_item, i, this);
//     return true;
// }

// bool operator==(const TTree &left, const TTree &right)
// {
//     int i;
//     for (i = 0; left.key[i] != '\0' && right.key[i] != '\0' && left.key[i] == right.key[i] && i < LENGTH - 1; i++)
//         ;

//     return left.key[i] == right.key[i];
// }

void TTree::Show(int height)
{
    if (right && right->bit > bit)
        right->Show(height + 1);
    // cout << key << endl;
    if (*key != '\0')
    {
        for (int i = 0; i < height; i++)
            cout << '\t';

        cout << '(' << key << ',' << bit << ')' << endl;
    }

    if (left && left->bit > bit)
        left->Show(height + 1);
}