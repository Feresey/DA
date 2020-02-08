// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <bitset>
#include <iostream>
#include <map>
#include <set>
#include <vector>

const int MAXINT = 110004;
std::map<int, std::set<int>> g;
std::vector<int> mt;
std::bitset<MAXINT> used;

bool kun(int v)
{
    if (used[v])
        return false;
    used[v] = true;
    for (auto to : g[v]) {
        if (mt[to] == -1 || kun(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

int main()
{
    int n, m, a, b;
    std::cin >> n >> m;
    while (std::cin >> a >> b) {
        --a;
        --b;
        g[a].insert(b);
        g[b].insert(a);
    }

    mt.assign(n + 2, -1);

    for (int i = 0; i < n; ++i) {
        used.reset();
        kun(i);
    }

    std::map<int, int> ans;
    for (int i = 0; i < n; ++i)
        if (mt[i] != -1)
            ans[std::min(i, mt[i])] = std::max(i, mt[i]);

    std::cout << ans.size() << std::endl;
    for (auto i : ans)
        std::cout << i.first + 1 << ' ' << i.second + 1 << std::endl;
}