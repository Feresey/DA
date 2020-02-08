#include "TTree.hpp"
#include "StackContainer.hpp"

TTree::TTree()
    : right(nullptr)
    , left(nullptr)
    , key(nullptr)
    , length(0)
    , data(0)
{
}

TTree::TTree(const TTree& orig)
    : right(orig.right)
    , left(orig.left)
    , key(orig.key)
    , length(orig.length)
    , data(orig.data)
{
}

TTree& TTree::operator=(const TTree& orig)
{
    right = orig.right;
    left = orig.left;
    key = orig.key;
    length = orig.length;
    data = orig.data;

    return *this;
}

void CopyStr(char* dst, const char* src, int len)
{
    for (int i = 0; i < len; ++i) {
        dst[i] = src[i];
    }
}

int Prefix(const char* lfs, int lfsLen, const char* rhs, int rhsLen)
{
    int prefix;

    for (prefix = 0; prefix != lfsLen && prefix != rhsLen && lfs[prefix] == rhs[prefix]; ++prefix)
        ;
    return prefix;
}

const ull* TTree::Search(const char* t, int len)
{
    TTree* node = this;
    int prefix;
    ++len;
    while (node != nullptr) {
        prefix = Prefix(node->key, node->length, t, len);

        if (prefix == 0) {
            node = node->right;
        } else if (prefix == len) {
            return &(node->data);
        } else if (prefix == node->length) {
            node = node->left;
        } else {
            node = nullptr;
        }

        t += prefix;
        len -= prefix;
    }
    return nullptr;
}

bool TTree::Insert(const char* t, int len, ull num)
{
    TTree* node = this;
    TTree* parent = nullptr;
    int prefix;
    bool sonsBrother = false;
    ++len;
    if (node->length == 0) {
        node->key = new char[len];
        CopyStr(node->key, t, len);
        node->length = len;
        node->data = num;
        return true;
    }

    while (true) {
        if (len == 0)
            ++len;
        if (node == nullptr) {
            node = new TTree;
            delete[] node->key;
            node->key = new char[len];
            CopyStr(node->key, t, len);
            node->length = len;
            node->data = num;

            if (parent != nullptr) {
                if (sonsBrother) {
                    parent->right = node;
                } else {
                    node->right = parent->left;
                    parent->left = node;
                }
            }
            break;
        }

        prefix = Prefix(node->key, node->length, t, len);

        if (prefix == 0) {
            sonsBrother = true;
            parent = node;
            node = node->right;
        } else if (prefix < len) {
            if (prefix < node->length) {
                TTree* newNode = new TTree;
                newNode->key = new char[node->length - prefix];
                CopyStr(newNode->key, node->key + prefix, node->length - prefix);

                newNode->length = node->length - prefix;
                newNode->data = node->data;
                newNode->left = node->left;
                node->left = newNode;
                char* buf = new char[prefix];

                CopyStr(buf, node->key, prefix);

                delete[] node->key;
                node->key = buf;
                node->length = prefix;
            }
            sonsBrother = false;
            parent = node;
            node = node->left;
            t += prefix;
            len -= prefix;
        } else {
            return false;
        }
    }
    return true;
}

bool TTree::Remove(const char* t, int len)
{
    TTree* node = this;
    TTree* parent = nullptr;
    TTree* brother = nullptr;
    int prefix;
    ++len;
    while (true) {
        if (len == 0) {
            ++len;
        }
        if (node == nullptr) {
            return false;
        }
        prefix = Prefix(node->key, node->length, t, len);
        if (prefix == len) {
            TTree* temp = node->right;

            if (parent != nullptr) {
                if (temp == nullptr) {
                    if (brother != nullptr && parent->left == brother) {
                        //merge parent & brother
                        char* buf = new char[parent->length + brother->length];

                        CopyStr(buf, parent->key, parent->length);
                        CopyStr(buf + parent->length, brother->key, brother->length);
                        delete[] parent->key;

                        parent->key = buf;
                        parent->length += brother->length;
                        parent->data = brother->data;
                        parent->left = brother->left;

                        brother->right = nullptr;
                        brother->left = nullptr;
                        delete brother;
                    } else {
                        brother->right = nullptr;
                    }
                } else {
                    if (brother == nullptr && temp->right == nullptr && parent->left == node) {
                        //merge parent & temp
                        char* buf = new char[parent->length + temp->length];
                        CopyStr(buf, parent->key, parent->length);
                        CopyStr(buf + parent->length, temp->key, temp->length);
                        delete[] parent->key;
                        parent->key = buf;
                        parent->length += temp->length;
                        parent->left = temp->left;
                        parent->data = temp->data;
                        temp->right = nullptr;
                        temp->left = nullptr;
                        delete temp;
                    } else if (brother == nullptr && temp->right != nullptr && parent->left == node) {
                        parent->left = temp;
                    } else if (brother != nullptr) {
                        brother->right = temp;
                    }
                }
                node->right = nullptr;
                node->left = nullptr;
                delete node;
                break;
            } else {
                if (brother == nullptr) {
                    if (node->right == nullptr) {
                        delete[] node->key;
                        node->length = 0;
                        node->key = nullptr;
                        node->data = 0;
                    } else {
                        delete[] node->key; //! copy
                        brother = node->right;
                        node->key = new char[brother->length];
                        CopyStr(node->key, brother->key, brother->length);
                        node->length = brother->length;
                        node->data = brother->data;
                        node->right = brother->right;
                        node->left = brother->left;
                        brother->right = nullptr;
                        brother->left = nullptr;
                        delete brother;
                    }
                } else {
                    brother->right = temp;
                    node->right = nullptr;
                    node->left = nullptr;
                    delete node;
                }
            }
            break;
        } else if (prefix == 0) {
            brother = node;
            node = node->right;
        } else if (prefix == node->length) {
            parent = node;
            node = node->left;
            brother = nullptr;

            t += prefix;
            len -= prefix;
        } else {
            return false;
        }
    }
    return true;
}

void TTree::Save(const char* path)
{
    const int size = 257;
    char* kkey = new char[size];
    int len = 0;
    TStack<const TTree*>* s = new TStack<const TTree*>;
    const TTree* node = this;
    const TTree* last = nullptr;
    std::ofstream file(path, std::ofstream::binary);

    if (!file) {
        std::cout << "ERROR: couldn't create file!\n";
        return;
    }

    s->Push(node);

    while (s->Empty() == 0) {
        if (node->left != nullptr && last != node->left && last != node->right) {
            CopyStr(kkey + len, node->key, node->length);
            len += node->length;
            kkey[len] = '\0';

            s->Push(node);
            node = node->left;
        } else {
            if (last != node->left || node->left == nullptr) {
                CopyStr(kkey + len, node->key, node->length);
                len += node->length;
                kkey[len] = '\0';
            }

            if (last == nullptr || (last != node->right && last != node->left)) {
                file << kkey << " " << node->data << std::endl;
            }

            if (node->right != nullptr && (last == nullptr || last != node->right)) {
                len -= node->length;
                s->Push(node);
                node = node->right;
                continue;
            }

            last = node;
            len -= node->length;
            kkey[len] = '\0';
            node = *(s->Top());
            s->Pop();
        }
    }

    std::cout << "OK\n";

    file.close();
    delete s;
    delete[] kkey;
}

void TTree::Load(const char* path)
{
    char key[LEN];
    ull data;
    std::ifstream file(path, std::ifstream::binary);

    while (file >> key >> data) {
        this->Insert(key, static_cast<int>(strlen(key)), data);
    }

    std::cout << "OK\n";
}

TTree::~TTree()
{
    delete[] key;
    delete right;
    delete left;
}