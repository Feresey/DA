// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <bitset>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

using uint = unsigned int;
const size_t MAXINT = 110001;
std::map<uint, std::set<uint>> g;
std::vector<uint> mt;
std::bitset<MAXINT> used;
// std::string apart(MAXINT, '\0');
// char ind = 'r';

// void dfs(uint v)
// {
//     apart[v] = ind;
//     ind = (ind == 'r') ? 'b' : 'r';
//     for (auto j : g[v])
//         if (!apart[j])
//             dfs(j);
// }

// bool kun(uint v)
// {
//     if (used[v])
//         return false;
//     used[v] = true;
//     for (auto to : g[v]) {
//         if (!mt[to] || kun(mt[to])) {
//             mt[to] = v;
//             return true;
//         }
//     }
//     return false;
// }

// void BFS(uint start)
// {
// std::queue<int> q;
// // Инициализация: есть информация про начальную вершину
// q.push(start);
// d[start] = 0;
// mark[start] = 1;
// // Главный цикл - пока есть серые вершины
// while (!q.empty()) {
//     // Берем первую из них
//     int v = q.front();
//     q.pop();
//     // Пробегаемся по всем ее соседям
//     for (int i = 0; i < (int)edges[v].size(); ++i) {
//         // Если сосед белый
//         if (mark[edges[v][i]] == 0) {
//             // То вычисляем расстояние
//             d[edges[v][i]] = d[v] + 1;
//             // И он становится серым
//             mark[edges[v][i]] = 1;
//             q.push(edges[v][i]);
//         }
//     }
// }
// }

std::vector<uint> path;
void dfs(uint pos)
{
    for (auto i : g[pos]) {
        if (!used[i]) {
            used[i] = true;
            path.push_back(i);
            for (auto j : g[i])
                dfs(j);
            return;
        }
    }
}

int main()
{
    uint n, m, a, b;
    std::cin >> n >> m;
    while (std::cin >> a >> b) {
        // --a;
        // --b;
        g[a].insert(b);
        g[b].insert(a);
    }
    std::vector<uint> res;
    used.reset();
    for (auto i : g) {
        dfs(i.first);
        if (path.size() > res.size()) {
            res = path;
        }
        path.clear();

        // if ()
    }
    for (auto i : res)
        std::cout << i << ' ';
    std::cout << std::endl;
    // for (auto i : g)
    //     if (!apart[i.first])
    //         dfs(i.first);

    // mt.assign(n + 1, 0);
    // size_t count = 0;
    // for (auto i : apart)
    //     if (i == 'r')
    //         ++count;
    // char mx = (count > apart.size() / 2) ? 'b' : 'r';
    // std::vector<bool> used1(n);
    // for (uint i = 0; i < n; ++i) {
    //     if (apart[i] != mx)
    //         continue;
    //     for (auto to : g[i])
    //         if (!mt[to]) {
    //             mt[to] = i;
    //             used1[i] = true;
    //             break;
    //         }
    // }
    // for (uint i = 0; i < apart.size(); ++i) {
    //     if (apart[i] != mx)
    //         continue;
    //     if (used1[i])
    //         continue;
    //     used.reset();
    //     kun(i);
    // }

    // std::cout << apart << std::endl;
    // std::map<uint, std::set<uint>> ans;
    // for (uint i = 0; i < n; ++i)
    //     if (mt[i]) {
    //         // std::cout << i << ' ' << mt[i] << std::endl;
    //         ans[std::min(i, mt[i])].insert(std::max(i, mt[i]));
    //     }

    // std::cout << ans.size() << std::endl;
    // for (auto i : ans) {
    //     std::cout << i.first << ' ';
    //     for (auto j : i.second)
    //         std::cout << j << std::endl;
    // }
}