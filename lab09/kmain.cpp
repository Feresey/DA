// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <bitset>
#include <iostream>
#include <limits>
#include <map>
#include <memory.h>
#include <set>
#include <vector>

// #define min(a, b) ((a) < (b) ? (a) : (b))
// #define max(a, b) ((a) > (b) ? (a) : (b))
#define fill(m, v) memset(m, v, sizeof(m));
using namespace std;
// const int MAXINT = std::numeric_limits<int>().max();

int n, m;
int i, j, k, l;
map<int, set<int>> g;
vector<bool> used, p, u2;
// vector<int> f;
int f[110001];
// void govno()
// {
//     int i, j;
//     // fill(u2, 0);

// }

bool dfs_kuhn(int v)
{
    if (used[v])
        return false;
    used[v] = true;
    for (auto i : g[v])
        if (f[i] < 0 || dfs_kuhn(f[i])) {
            f[i] = v;
            return true;
        }
    return false;
}

int main()
{
    cin >> n >> m;
    for (k = 0; k < m; ++k) {
        cin >> i >> j;
        --i;
        --j;
        g[j].insert(i);
        g[i].insert(j);
    }

    // f.assign(n + 1, -1);
    fill(f, 255);
    // f[0] = MAXINT;
    // f[0] = numeric_limits<int>.max();
    // memset()
    // f.assign(n, 0);
    // govno();
    u2.assign(n, false);
    for (i = 0; i < n; ++i) {
        for (auto j : g[i])
            if (f[j] < 0) {
                f[j] = i;
                u2[i] = true;
                break;
            }
    }
    for (i = 0; i < n; ++i)
        if (!u2[i]) {
            // fill(u, 0);
            used.assign(n, false);
            dfs_kuhn(i);
        }

    std::map<int, int> ans;
    for (int i = 0; i < n; ++i)
        if (f[i] >= 0) {
            // std::cout << i << ' ' << f[i] << std::endl;
            ans[min(i, f[i])] = max(i, f[i]);
        }
    std::cout << ans.size() << std::endl;
    for (auto i : ans)
        std::cout << i.first + 1 << ' ' << i.second + 1 << std::endl;
    // for (i = 0; i < n; ++i)
    //     if (f[i] >= 0) {
    //         // cout << f[i] + 1 << ' ' << i + 1 << endl;
    //     }

    return 0;
}