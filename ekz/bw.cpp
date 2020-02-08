#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

std::pair<std::string, size_t> GetCoded(const std::string& src)
{
    std::vector<std::string> table;
    std::string temp = src + src;

    for (size_t i = 0; i < src.size(); ++i)
        table.push_back(temp.substr(i, src.size()));
    std::sort(table.begin(), table.end());

    temp = "";
    long pos = -1;

    for (auto i = table.begin(); i != table.end(); ++i) {
        if (*i == src)
            pos = i - table.begin();
        temp += i->back();
    }

    return { temp, pos };
}

std::string GetDecoded(const std::string& src, size_t pos)
{
    std::string temp = src;
    std::sort(temp.begin(), temp.end());
    std::vector<long> nums(src.size(), -1);

    auto it_sort = temp.begin(), it_end = temp.end();
    while (it_sort != it_end) {
        for (size_t i = 0; i < src.size(); ++i)
            if (src[i] == *it_sort && nums[i] == -1) {
                nums[i] = it_sort - temp.begin();
                break;
            }
        ++it_sort;
    }

    temp = "";
    while (temp.size() != src.size()) {
        size_t search = 0;
        for (; search < nums.size() && nums[search] != pos; ++search)
            ;
        pos = search;
        temp += src[pos];
    }
    return temp;
}

int main()
{
    std::string str;
    std::getline(std::cin, str);

    auto coded = GetCoded(str);
    std::cout << coded.first << '\t' << coded.second << std::endl;
    std::cout << GetDecoded(coded.first, coded.second) << std::endl;
    return 0;
}