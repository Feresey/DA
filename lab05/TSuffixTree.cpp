#include "TSuffixTree.hpp"
#include <iomanip>
TSuffixTree::Node::Node(int start, size_t end, Node* suff)
    : children()
    , suffixLink(suff)
    , start(start)
    , end(end)
    , suffixIndex(-1)
{
}

size_t TSuffixTree::Node::length(size_t pos)
{ 
	return std::min(end, pos) - start + 1UL;
}

TSuffixTree::Node::~Node()
{
    for (auto i : children)
        delete i.second;
}

TSuffixTree::TSuffixTree(const std::string& txt)
    : root(Node(-1, txt.size() - 1UL, nullptr))
    , text(txt)
    , activeNode(&root)
    , activeEdge(0)
    , activeLength(0)
{
    Node* sl_need = &root;
    int remainingSuffixCount = 0;
    for (size_t i = 0; i < text.size(); ++i) {
        sl_need = &root;
        remainingSuffixCount++;
        while (remainingSuffixCount) {
            if (!activeLength) {
                activeEdge = i;
            }
            Node* next = activeNode->children[text[activeEdge]];
            if (!next) {
                activeNode->children[text[activeEdge]] = new Node(i, text.size() - 1, &root);
                if (sl_need != &root)
                    sl_need->suffixLink = activeNode;
                sl_need = activeNode;
            } else {
                if (walkDown(next, i)) {
                    continue;
                }
                if (text[next->start + activeLength] == text[i]) {
                    ++activeLength;
                    if (sl_need != &root)
                        sl_need->suffixLink = activeNode;
                    sl_need = activeNode;
                    break;
                }

                Node* split = new Node(next->start, next->start + activeLength - 1UL, &root);
                Node* is_leaf = new Node(i, text.size() - 1UL, &root);

                activeNode->children[text[activeEdge]] = split;
                split->children[text[i]] = is_leaf;
                next->start += activeLength;
                split->children[text[next->start]] = next;

                if (sl_need != &root)
                    sl_need->suffixLink = split;
                sl_need = split;
            }
            --remainingSuffixCount;
            if (activeNode == &root && activeLength) {
                --activeLength;
                activeEdge = i - remainingSuffixCount + 1;
            } else {
                activeNode = activeNode->suffixLink ? activeNode->suffixLink : &root;
            }
        }
    }
    index(&root, 0);
    // for (size_t i = activeLength; i + 1 != 1; --i) {
    //     for (size_t l = i; l; --l)
    //         std::cout << text[l];
    //     std::cout << std::endl;
    // }
    std::cout << "\n\nAP:\t"
              << text[activeEdge] << '\t'
              << activeLength << std::endl;
}

int TSuffixTree::walkDown(Node* currNode, size_t pos)
{
    if (activeLength >= currNode->length(pos)) {
        activeEdge += currNode->length(pos);
        activeLength -= currNode->length(pos);
        activeNode = currNode;
        return 1;
    }
    return 0;
}

void TSuffixTree::index(Node* n, size_t h)
{
    if (n->start != -1) {
        std::cout << std::setfill(' ') << std::setw(h + 1);
        for (size_t i = n->start; i <= n->end; ++i)
            std::cout << text[i];
        // std::cout  << std::endl;
    }
    bool is_leaf = true;
    for (auto i : n->children) {
        if (is_leaf && n->start != -1)
            std::cout << std::endl;
        is_leaf = false;
        if (i.second)
            index(i.second, (n->start == -1) ? 0 : h + n->length(text.size() + 1));
    }
    if (is_leaf) {
        std::cout << std::endl;
    }
}

TMatch::TMatch(const TSuffixTree& tree, const std::string& text)
    : statistics(text.size())
    , size(tree.text.size() - 1u)
{
    std::size_t active_length = 0u, active_char_idx = 0u, summary = 0u;
    TSuffixTree::Node* active_vertex = &tree.root;

    for (std::string::const_iterator it = text.cbegin(), pos = text.cbegin(); it != text.cend(); ++it) {
        //      assert(summary < text.size() && summary < tree.text.size());
        std::map<char, TSuffixTree::Node*>::const_iterator link;
        while (pos != text.cend() && ((active_length < active_vertex->length(size) && *pos == tree.text[active_vertex->start + active_length]) || (active_length >= active_vertex->length(size) && (link = active_vertex->Edges().find(*pos), link != active_vertex->Edges().cend())))) {
            if (active_length >= active_vertex->length(size)) {
                summary += active_vertex->length(size);
                active_vertex = link->second;
                active_char_idx = active_vertex->start;
                active_length = 0u;
            }
            ++active_length;
            ++pos;
        }
        statistic[it - text.cbegin()] = summary + active_length;
        if (active_vertex == tree.root) {
            //          assert(!summary);
            ++pos;
            continue;
        }
        if (active_length < active_vertex->length(size)) {
            active_vertex = active_vertex->GetParent()->GetSuffixLink()->Edges().at(tree.text[active_char_idx]);
            if (active_vertex == tree.root) {
                --active_length;
                ++active_char_idx;
                ++summary;
            }
            for (std::size_t length; active_length > active_vertex->length(size); active_length -= length, summary += length) {
                length = active_vertex->length(size);
                active_char_idx += length;
                active_vertex = active_vertex->Edges().at(tree.text[active_char_idx]);
            }
        } else {
            active_vertex = active_vertex->GetSuffixLink();
            active_length = active_vertex->length(size);
            if (active_vertex == tree.root) {
                ++summary;
            }
        }
        --summary;
    }
}
