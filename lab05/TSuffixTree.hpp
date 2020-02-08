#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <map>
#include <vector>

class TSuffixTree;

class TMatch {
    std::vector<size_t> statistics;
    size_t size;

public:
    TMatch(const TSuffixTree&, const std::string& text);
};

class TSuffixTree {
    struct Node {
        std::map<char, Node*> children;
        Node* suffixLink;
        int start;
        size_t end;
        int suffixIndex;
        Node(int, size_t, Node*);
        ~Node();
        Node() {}
        size_t length(size_t);
    };

    Node root;
    std::string text;

    Node* activeNode;
    size_t activeEdge;
    size_t activeLength;

    int walkDown(Node*, size_t);
    void index(Node*, size_t);

    friend TMatch::TMatch(const TSuffixTree&, const std::string&);
public:
    explicit TSuffixTree(const std::string&);
};

#endif
