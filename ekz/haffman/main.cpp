#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>

class Haffman {
    struct tree {
        char data;
        int prio;
        tree *l, *r;
        tree(int priority = 0, char sym = '\0')
            : data(sym)
            , prio(priority)
            , l(nullptr)
            , r(nullptr)
        {
        }

        ~tree()
        {
            if (l)
                delete l;
            if (r)
                delete r;
        }

        void show(int h = 0)
        {
            if (l)
                l->show(h + 1);

            for (int i = 0; i < h; ++i)
                std::cout << '\t';
            std::cout << data << ':' << prio << '\n';
            if (r)
                r->show(h + 1);
        }
    };
    static bool cmp(tree* left, tree* right) { return left->prio >= right->prio; };

    tree* root;

    tree* merge(tree* left, tree* right)
    {
        tree* res = new tree(left->prio + right->prio);
        res->l = cmp(left, right) ? right : left;
        res->r = res->l == right ? left : right;
        // tree* it = left;
        // while (it->r)
        //     it = it->r;
        // it->r = res;
        return res;
    }

public:
    Haffman(const std::string& text)
        : root(nullptr)
    {
        auto c = [](tree* l, tree* r) { return l->prio >= r->prio; };
        std::priority_queue<tree*, std::vector<tree*>, decltype(c)> q(c);
        std::map<char, int> ch;

        for (auto i : text)
            ch[i]++;
        for (auto i : ch)
            q.push(new tree(i.second, i.first));

        while (q.size() != 1) {
            tree *a, *b;
            a = q.top();
            q.pop();
            b = q.top();
            q.pop();
            q.push(merge(a, b));
        }
        root = q.top();
    }

    void show()
    {
        root->show();
    }

    std::map<char, int> GetCodes()
    {
        std::map<char, int> res;
        std::vector<tree*> up;
        // up.push_back(root);
        // int code = 0;
        // while (up.back()->l) {
        //     up.push_back(up.back()->l);
        //     code <<= 1;
        // }

        // while (!up.empty()) {
        //     tree* cur = up.back();
        //     up.pop_back();

        // }
    }

    ~Haffman()
    {
        if (root)
            delete root;
    }
};

int main()
{
    char t[200];
    std::cin.getline(t, 200);
    Haffman h(t);
    h.show();
    return 0;
}