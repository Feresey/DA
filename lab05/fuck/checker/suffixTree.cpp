#include "suffixTree.h"
#include <algorithm>

TSuffixTree::TNode::TNode(TNode* papa = nullptr, size_t start = 0, size_t end = 0, TNode* suf = nullptr)
    : edges()
    , parent(papa)
    , suffix_link(suf)
    , begin(start)
    , length(end)
{
}

TSuffixTree::TNode::TNode(const std::string& text, TNode* const& node, const size_t& pos)
    : edges({ { text[node->begin + pos], node } })
    , parent(node->parent)
    , begin(node->begin)
    , length(pos)
{
    edges[text.back()] = new TNode(this, text.size() - 1, -1UL);
    node->parent->edges[text[node->begin]] = this;
    node->parent = this;
    node->begin += pos;
    if (node->length != -1UL)
        node->length -= pos;
}

TSuffixTree::TSuffixTree(const std::string& text)
    : pattern()
    , root(new TNode())
    , active_vertex(root)
    , active_length(0)
    , active_char_idx(0)
{
    root->suffix_link = new TNode();
    for (auto it : "abcdefghijklmnopqrstuvwxyz$")
        root->suffix_link->edges[it] = root;

    for (auto i : text)
        extend(i);
}

void TSuffixTree::extend(char new_ch)
{
    pattern.push_back(new_ch);
    TNode* needSL = nullptr;
    while ((active_length < active_vertex->length && pattern[active_vertex->begin + active_length] != new_ch) || (active_length >= active_vertex->length && !active_vertex->edges.count(new_ch))) {
        if (active_length < active_vertex->length && pattern[active_vertex->begin + active_length] != new_ch) {
            TNode* temp = new TNode(pattern, active_vertex, active_length);
            if (needSL)
                needSL->suffix_link = temp;

            needSL = active_vertex->parent;
            active_vertex = needSL->parent->suffix_link->edges.at(pattern[active_char_idx]);
            if (active_vertex == root) {
                --active_length;
                ++active_char_idx;
            }
            for (size_t length; active_length > active_vertex->length; active_length -= length) {
                length = active_vertex->length;
                active_char_idx += length;
                active_vertex = active_vertex->edges.at(pattern[active_char_idx]);
            }
        } else {
            active_vertex->edges[pattern.back()] = new TNode(active_vertex, pattern.size() - 1, -1UL);
            if (needSL) {
                needSL->suffix_link = active_vertex;
                needSL = nullptr;
            }
            if (active_vertex != root) {
                active_vertex = active_vertex->suffix_link;
                active_length = active_vertex->length;
            }
        }
    }
    if (needSL)
        needSL->suffix_link = active_vertex;

    auto it = active_vertex->edges.find(new_ch);

    if (active_length >= active_vertex->length && it != active_vertex->edges.end() && it->second->begin < pattern.size() - 1) {
        active_length = 1;
        active_vertex = it->second;
        active_char_idx = active_vertex->begin;
    } else
        ++active_length;
}

TSuffixTree::~TSuffixTree()
{
    root->suffix_link->edges.clear();
    delete root->suffix_link;
    delete root;
}

std::vector<size_t> TSuffixTree::Find(const std::string& text)
{
    std::vector<size_t> stat(text.size());
    size_t active_length = 0, active_char_idx = 0, summary = 0;
    TNode* active_vertex = root;
    auto pos = text.begin();

    for (size_t it = 0; it < text.size(); ++it) {
        while (pos != text.end()
            && ((active_length < active_vertex->length && *pos == pattern[active_vertex->begin + active_length])
                   || (active_length >= active_vertex->length && active_vertex->edges.count(*pos)))) {
            if (active_length >= active_vertex->length) {
                summary += active_vertex->length;
                active_vertex = active_vertex->edges[*pos];
                active_char_idx = active_vertex->begin;
                active_length = 0;
            }
            ++active_length;
            ++pos;
        }
        stat[it] = summary + active_length;
        if (active_vertex == root) {
            ++pos;
            continue;
        }
        if (active_length < active_vertex->length) {
            active_vertex = active_vertex->parent->suffix_link->edges.at(pattern[active_char_idx]);
            if (active_vertex == root) {
                --active_length;
                ++active_char_idx;
                ++summary;
            }
            for (size_t length; active_length > active_vertex->length; active_length -= length, summary += length) {
                length = active_vertex->length;
                active_char_idx += length;
                active_vertex = active_vertex->edges.at(pattern[active_char_idx]);
            }
        } else {
            active_vertex = active_vertex->suffix_link;
            active_length = active_vertex->length;
            if (active_vertex == root)
                ++summary;
        }
        --summary;
    }
    return stat;
}