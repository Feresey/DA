#include <algorithm>
#include <iostream>
#include <vector>

int parse(const char* src)
{
    char buf[] = "0000000";
    size_t fill = 0, prev_pos = 0;
    size_t borders[] = { 2, 2, 4 };
    int count = 0;
    while (count != 3) {
        size_t pos = prev_pos;
        while (src[pos] != '\t' && src[pos] != '.')
            ++pos;
        fill += borders[count] - pos + prev_pos;
        while (prev_pos != pos)
            buf[fill++] = src[prev_pos++];
        ++prev_pos;
        ++count;
    }

    // yyyy mm dd
    char temp[] = {
        buf[4], buf[5], buf[6], buf[7],
        buf[2], buf[3],
        buf[0], buf[1],
        '\0'
    };

    return atoi(temp);
}

int main()
{
    using Para = std::pair<int, std::string>;
    std::vector<Para> nums;
    std::string input;
    while (std::getline(std::cin, input))
        if (input != "")
            nums.push_back({ parse(input.c_str()), input });
    std::stable_sort(nums.begin(), nums.end(), [](const Para& lhs, const Para& rhs) { return lhs.first < rhs.first; });
    for (const auto& i : nums)
        std::cout << i.second << std::endl;
    return 0;
}
