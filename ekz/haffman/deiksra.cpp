#include <iostream>
#include <vector>


const int INF = 1'000'000;
std::vector<int> deikstra(std::vector<std::vector<std::pair<int, int>>> g, int s)
{
    std::vector<int> len(g.size(),INF);
    std::vector<bool> used(g.size(),false);

    len[s] = 0;

    for (int i = 0; i < g.size(); ++i)
    {
        int v = -1;

        for (int j = 0; j < g[i].size(); ++j)
        {
            
        }
    }

    return len;
}

int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> g(n);
    g.resize(n);
    int a, b;
    while (m--) {
        std::cin >> a >> b >> n;
        g[a].push_back({ b, n });
    }
    int v;
    std::cin >> v;
    auto len = deikstra(g,v);

    for (auto i : len)
        std::cout << i << ' ';
    std::cout << std::endl;
}