// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <bitset>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

const int MAXINT = 110004;
std::vector<std::vector<size_t>> g;
std::bitset<MAXINT> used;
std::vector<size_t> mt;

bool dfs(size_t pos)
{
    if (used[pos])
        return false;
    used[pos] = true;
	auto it = std::find_if(g[pos].begin(), g[pos].end(),
			[](size_t to){return mt[to] == -1UL || dfs(mt[to]);});
    return (it != g[pos].end()) ?
		mt[*it] = pos, mt[pos] = *it, true
		: false;
}

int main()
{
    size_t n, m, a, b;
    std::cin >> n >> m;
	g.resize(n+1);
    while (std::cin >> a >> b) {
        --a;
        --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    mt.assign(n, -1UL);

    for (size_t i = 0; i < n; ++i)
        if (mt[i] == -1UL) {
            used.reset();
            dfs(i);
        }

    std::map<size_t, size_t> ans;
    for (size_t i = 0; i < n; ++i)
        if (mt[i] != -1UL)
            ans[std::min(i, mt[i])] = std::max(i, mt[i]);

    std::cout << ans.size() << std::endl;
    // for (auto i : ans)
	std::for_each(ans.begin(), ans.end(), [](const std::pair<size_t, size_t>& i){std::cout << i.first + 1 << ' ' << i.second + 1 << std::endl;});
	return 0;
}

