#include <iostream>
#include <queue>
#include <vector>

std::queue<size_t> TopologicalSort(const std::vector<std::vector<bool>>& matrix)
{
    std::vector<bool> used(matrix.size(), false);
    std::queue<size_t> ans;
    for (size_t l = 0; l < matrix.size(); ++l) {
        size_t j = 0;
        for (; j < used.size() && used[j]; ++j);
        if (j == used.size())
            break;
        bool is_pushed = false;
        for (size_t i = 0; i < matrix.size(); ++i) {
            if (used[i])
                continue;
            size_t k = 0;
            for (; k < matrix.size() && !(matrix[k][i] && !used[k]); ++k);
            if (k == matrix.size()) {
                ans.push(i);
                used[i] = is_pushed = true;
            }
        }
        if (!is_pushed)
            return {}; //std::queue<size_t>();
    }
    return ans;
}

int main()
{
    size_t n, m;
    std::cin >> n >> m;
    std::vector<std::vector<bool>> matrix(n);
    for (size_t i = 0; i < n; ++i)
        matrix[i].assign(n, false);

    while (std::cin >> n >> m)
        matrix[n - 1][m - 1] = true;

    std::queue<size_t> ans = TopologicalSort(matrix);

    if (ans.empty())
        std::cout << -1 << std::endl;
    else do
            std::cout << ans.front() + 1 << " ";
        while (ans.pop(), not ans.empty());
    std::cout << std::endl;
    return 0;
}

