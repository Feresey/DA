// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int n;
vector<vector<int>> a; // Матрица эффективности a[разраб][задача]
vector<int> xy, yx; // Паросочетания: xy[разраб], yx[задача]
vector<char> vx, vy; // Альтернирующее дерево vx[разраб], vy[задача]
vector<int> maxrow, mincol; // Способности, изученность

bool dotry(int i)
{
    if (vx[i])
        return false;
    vx[i] = true;
    for (int j = 0; j < n; ++j)
        if (a[i][j] - maxrow[i] - mincol[j] == 0)
            vy[j] = true;
    for (int j = 0; j < n; ++j)
        if (a[i][j] - maxrow[i] - mincol[j] == 0 && yx[j] == -1) {
            xy[i] = j;
            yx[j] = i;
            return true;
        }
    for (int j = 0; j < n; ++j)
        if (a[i][j] - maxrow[i] - mincol[j] == 0 && dotry(yx[j])) {
            xy[i] = j;
            yx[j] = i;
            return true;
        }
    return false;
}

int main()
{

    // ... чтение a ...
    // vector<vector<int>> a; // Матрица эффективности a[разраб][задача]

    int m, x, y;
    cin >> n >> m;
    a.resize(n);
    // for (int i = 0; i < n; ++i)
    //     a[i].assign(n, 0);
    while (std::cin >> x >> y) {
        --x;
        --y;
        a[x].push_back[y];
        a[y][x];
    }

    mincol.assign(n, 0);
    maxrow.assign(n, 0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            maxrow[i] = max(maxrow[i], a[i][j]);

    xy.assign(n, -1);
    yx.assign(n, -1);
    for (int c = 0; c < n;) {
        vx.assign(n, 0);
        vy.assign(n, 0);
        int k = 0;
        for (int i = 0; i < n; ++i)
            if (xy[i] == -1 && dotry(i))
                ++k;
        c += k;
        if (k == 0) {
            int z = std::numeric_limits<int>().max();
            for (int i = 0; i < n; ++i)
                if (vx[i])
                    for (int j = 0; j < n; ++j)
                        if (!vy[j])
                            z = min(z, maxrow[i] + mincol[j] - a[i][j]);
            for (int i = 0; i < n; ++i) {
                if (vx[i])
                    maxrow[i] -= z;
                if (vy[i])
                    mincol[i] += z;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i)
        ans += a[i][xy[i]];
    printf("%d\n", ans);
    for (int i = 0; i < n; ++i)
        printf("%d ", xy[i] + 1);
}