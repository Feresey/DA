#include <iostream>
#include <map>
#include <sstream>
#include <vector>

class LZW {
    std::vector<std::string> codes;
    std::stringstream out;

public:
    LZW(const std::string& src, size_t alphalen = 5)
    {
        for (char i = 0; i < alphalen; ++i) {
            std::string tmp = "a";
            tmp[0] += i;
            codes.push_back(tmp);
        }
        out << alphalen << '\n';

        auto hold = codes.cend();
        size_t iter = 0;
        std::string buf;

        while (iter != src.size()) {
            buf += src[iter++];
            auto search = codes.cbegin();
            while (search != codes.cend() && *search != buf)
                ++search;
            if (search != codes.cend()) {
                hold = search;
                continue;
            }

            out << hold - codes.cbegin() << ' ';
            codes.push_back(std::string(buf));
            buf = buf.substr(hold->size());

            search = codes.cbegin();
            while (search != codes.cend() && *search != buf)
                ++search;
            if (search != codes.cend())
                hold = search;
        }

        out << hold - codes.cbegin() << ' ';
    }

    // LZW(const std::vector<int> code)
    // {
    //     for (char i = 0; i < code[0]; ++i) {
    //         std::string tmp = "a";
    //         tmp[0] += i;
    //         codes[tmp] = i;
    //     }

    //     auto hold = codes.end();
    //     size_t iter = 1;
    //     std::string buf;

    //     while (iter != code.size()) {

    //         // buf+=
    //     }
    // }

    std::string GetCode()
    {
        return out.str();
    }
};

int main()
{
    std::string inp;
    std::cin >> inp;
    LZW ar(inp);
    std::cout << ar.GetCode() << std::endl;
}