#include <iostream>
#include <vector>

class TopologicalSort {
    std::vector<bool> used;
    std::vector<size_t> ans;

    void dfs(const std::vector<std::vector<bool>>& matrix, size_t v)
    {
        used[v] = true;
        for (size_t i = 0; i < matrix.size(); ++i)
            if (not used[i] and matrix[v][i])
                dfs(matrix, i);

        ans.push_back(v);
    }

public:
    TopologicalSort(const std::vector<std::vector<bool>>& matrix)
        : used(matrix.size(), false)
        , ans({})
    {
        for (size_t i = 0; i < matrix.size(); ++i)
            if (not used[i])
                dfs(matrix, i);

        for (auto i = ans.rbegin(); i != ans.rend(); ++i)
            std::cout << *i + 1 << " ";
        std::cout << std::endl;
    }
};

int main()
{
    size_t n, m;
    std::cin >> n >> m;
    std::vector<std::vector<bool>> matrix(n);
    for (size_t i = 0; i < n; ++i)
        matrix[i].assign(n, false);

    for (size_t i = 0; i < m; ++i) {
        size_t a, b;
        std::cin >> a >> b;
        matrix[a - 1][b - 1] = true;
    }

    TopologicalSort result(matrix);
    return 0;
}
