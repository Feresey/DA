// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//-V2008_CYCLOMATIC_COMPLEXITY=1
#include <fstream>
#include <iostream>
#include <vector>

#include "Shazam.hpp"

#define usage                                                                                                            \
    {                                                                                                                    \
        std::cout << argv[0] << " index --input <input file> --output <index file>\n"                                    \
                  << argv[0] << " search --index <index file> --input <input file> --output <output file>" << std::endl; \
        return 1;                                                                                                        \
    }

// returns the argument going after the key
std::string GetName(const int argc, char** argv, const std::string& key)
{
    for (int i = 0; i < argc; ++i)
        if (key == argv[i])
            return ++i != argc ? argv[i] : "";
    return "";
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        usage;
        return 1;
    }

    Shazam base;
    if (argv[1] == std::string{"index"}) {
        std::string input, output;
        input = GetName(argc, argv, "--input");
        output = GetName(argc, argv, "--output");
        if (output.empty())
            usage;
		if (input.empty())
			input = "/dev/stdin";
        std::ifstream in(input);
        std::ofstream out(output);

        if (!in.is_open()) {
            std::cout << "could not open file \"" << input << "\" !\n";
            return 1;
        }
        if (!in.is_open()) {
            std::cout << "could not open file \"" << output << "\" !\n";
            return 1;
        }

        std::string line;
        std::vector<std::string> names;
        while (std::getline(in, line))
            names.push_back(line);
        //!!! threading
        base.CreateBase(names, 8);
        base.write(out);
    } else if (argv[1] == std::string("search")) {
        std::string index, input, output;
        index = GetName(argc, argv, "--index");
        input = GetName(argc, argv, "--input");
        output = GetName(argc, argv, "--output");
        if (index.empty())
            usage;
		if (input.empty())
			input = "/dev/stdin";
		if (output.empty())
			output = "/dev/stdout";
        std::ifstream ind(index);
        std::ifstream inp(input);
        std::ofstream out(output);
        if (!ind.is_open()) {
            std::cout << "could not open file \"" << index << "\" !\n";
            return 1;
        }
        if (!inp.is_open()) {
            std::cout << "could not open file \"" << input << "\" !\n";
            return 1;
        }
        if (!out.is_open()) {
            std::cout << "could not open file \"" << output << "\" !\n";
            return 1;
        }
        base.read(ind);

        std::string line;
        while (std::getline(inp, line)) {
            std::string res = base.search(line);
            out << res << "\n";
        }
    } else
        usage;
    return 0;
}
