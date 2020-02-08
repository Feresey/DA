#ifndef Tree
#define Tree

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <sstream>
#include <vector>

const int MAX_WORD_LENGTH = 17;

#define ull unsigned long long

class TAho {
private:
    struct TBor {
        std::map<std::string, std::shared_ptr<TBor>> links;
        TBor* suff_link;
        TBor* out;
        ull key_num;

        TBor(TBor* fail_link)
            : links()
            , suff_link(fail_link)
            , out(nullptr)
            , key_num(0)
        {
        }
    };

    std::shared_ptr<TBor> root;
    std::vector<size_t> line_len;
    ull key_count;
    TAho::TBor* state;

    void Next(std::string& str);
    void Suffix();
    void Show(ull& i, std::vector<std::pair<int, int>>& result)
    {
        ull index;
        if (state->key_num) {
            index = i - line_len[state->key_num - 1] + 1;
            printf("%d, %d, %lld\n", result[index].first, result[index].second, state->key_num);
        }

        TAho::TBor* help = state->out;
        while (help) {
            if (help->key_num) {
                index = i - line_len[help->key_num - 1] + 1;
                printf("%d, %d, %lld\n", result[index].first, result[index].second, help->key_num);
            }
            help = help->out;
        }
    }

public:
    TAho()
        : root(std::make_shared<TBor>(TBor(nullptr)))
        , line_len()
        , key_count(0)
        , state(root.get())
    {
    }
    void AddKeys();
    void Search(std::vector<std::string>&, std::vector<std::pair<int, int>>&);
};

#endif // !Tree
