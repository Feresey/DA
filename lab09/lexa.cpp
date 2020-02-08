// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 10000;
int n;
vector<int> g[MAXN];
int match[MAXN], p[MAXN], base[MAXN], q[MAXN];
bool used[MAXN], blossom[MAXN];

int lca(int a, int b)
{
    bool used[MAXN] = { 0 };

    for (;;) {
        a = base[a];
        used[a] = true;
        if (match[a] == -1)
            break;
        a = p[match[a]];
    }

    for (;;) {
        b = base[b];
        if (used[b])
            return b;
        b = p[match[b]];
    }
}

void mark_path(int v, int b, int children)
{
    while (base[v] != b) {
        blossom[base[v]] = blossom[base[match[v]]] = true;
        p[v] = children;
        children = match[v];
        v = p[match[v]];
    }
}

int find_path(int root)
{
    memset(used, 0, sizeof used);
    memset(p, -1, sizeof p);
    for (int i = 0; i < n; ++i) {
        base[i] = i;
    }

    used[root] = true;
    int qh = 0, qt = 0;
    q[qt++] = root;
    cout << "before While" << endl;
    while (qh < qt) {
        cout << "After a While qh =" << qh << " qt =" << qt << endl;
        int v = q[qh++];
        for (size_t i = 0; i < g[v].size(); ++i) {
            int to = g[v][i];
            cout << "before Check" << endl;
            if (base[v] == base[to] || match[v] == to) {
                cout << "after Check" << endl;
                continue;
            }
            cout << "before W" << endl;
            if (to == root || match[to] != -1 && p[match[to]] != -1) {
                cout << "after W" << endl;
                int curbase = lca(v, to);
                memset(blossom, 0, sizeof blossom);
                mark_path(v, curbase, to);
                mark_path(to, curbase, v);
                for (int i = 0; i < n; ++i)
                    if (blossom[base[i]]) {
                        base[i] = curbase;
                        if (!used[i]) {
                            used[i] = true;
                            q[qt++] = i;
                        }
                    }
            } else if (p[to] == -1) {
                p[to] = v;
                if (match[to] == -1)
                    return to;
                to = match[to];
                used[to] = true;
                q[qt++] = to;
            }
        }
    }
    return -1;
}

int main()
{

    cout << "Write the number of nodes: ";
    int a, m;
    cin >> n;

    cout << "Please, fill in the table:\n";
    cout << "   ";
    for (int i = 1; i <= n; ++i) {
        cout << i << ' ';
    }
    cout << "\n";

    for (int i = 0; i < n; ++i) {
        cout << i + 1 << ") ";
        cout << "Write the number of arcs: ";
        cin >> m;
        for (int j = 0; j < m; ++j) {
            cin >> a;
            g[i].push_back(a - 1);
        }
    }
    cout << endl;

    for (int i = 0; i < n; ++i) {
        cout << i + 1 << ") ";

        for (int j = 0; j < g[i].size(); ++j) {

            cout << g[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
    memset(match, -1, sizeof match);
    for (int i = 0; i < n; ++i)
        if (match[i] == -1) {
            int v = find_path(i);
            while (v != -1) {
                int pv = p[v], ppv = match[pv];
                match[v] = pv, match[pv] = v;
                v = ppv;
            }
        }

    cout << "Te q/base result is:\n";
    for (int i = 0; i < n; ++i) {
        cout << q[i] << '/' << base[i] << ' ';
    }
}
