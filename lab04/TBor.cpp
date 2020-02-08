// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "TBor.hpp"

void TAho::AddKeys()
{
    std::shared_ptr<TAho::TBor> curr;
    char temp[MAX_WORD_LENGTH];
    std::string inp;
    size_t size;

    while (getline(std::cin, inp)) {
        size = 0;
        curr = root;
        if (inp[0] == '\0')
            break;
        std::transform(inp.begin(), inp.end(), inp.begin(), tolower);
        std::stringstream line(inp);
        while (line >> temp) {
            size++;
            if (!curr->links.count(temp))
                curr->links[temp] = std::shared_ptr<TAho::TBor>(new TAho::TBor(root.get()));
            curr = curr->links[temp];
        }
        curr->key_num = ++key_count;
        line_len.push_back(size);
    }
}

void TAho::Suffix()
{
    std::queue<TAho::TBor*> q;
    q.push(root.get());

    TAho::TBor *current, *child, *curr_suffix;

    while (!q.empty()) {
        current = q.front();
        q.pop();
        for (auto it : current->links) {
            child = it.second.get();
            curr_suffix = current->suff_link;
            while (curr_suffix) {
                auto next_suffix = curr_suffix->links.find(it.first);
                if (next_suffix != curr_suffix->links.end()) {
                    child->suff_link = next_suffix->second.get();
                    break;
                }
                curr_suffix = curr_suffix->suff_link;
            }

            child->out = (child->suff_link->key_num) ? child->suff_link : child->suff_link->out;
            q.push(child);
        }
    }
}

void TAho::Search(std::vector<std::string>& lines, std::vector<std::pair<int, int>>& result)
{
    Suffix();

    size_t size = lines.size();
    for (ull i = 0; i < size; ++i) {
        Next(lines[i]);
        Show(i, result);
    }
}

void TAho::Next(std::string& str)
{
    while (state) {
        if (state->links.count(str)) {
            state = state->links[str].get();
            return;
        }
        state = state->suff_link;
    }
    state = root.get();
}