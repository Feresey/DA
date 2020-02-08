#include <iostream>
#include <vector>

std::vector<int> LS(std::vector<int> numbers)
{
    std::vector<int> len(numbers.size(), 0);
    len[0] = 1;
    for (size_t i = 0; i < numbers.size(); ++i) {
        int mx = 0;
        for (size_t j = 0; j < i; ++j)
            if (numbers[i] > numbers[j] && len[j] > mx)
                mx = len[j];
        len[i] = mx + 1;
    }
    return len;
}

int main()
{
    std::vector<int> a;
    int n;
    while (std::cin >> n)
        a.push_back(n);

    auto res = LS(a);

    for (auto i : res)
        std::cout << i << " ";
    std::cout << std::endl;
    return 0;
}
