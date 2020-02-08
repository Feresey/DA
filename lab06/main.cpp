// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "BigInt.hpp"

int main()
{
    std::string num1, num2;
    char sym;
    TBigInt BigZero, res;

    while (std::cin >> num1 >> num2 >> sym) {
        TBigInt a(num1);
        TBigInt b(num2);

        switch (sym) {
        case '+':
            res = a + b;
            std::cout << res << '\n';
            break;
        case '-':
            if (a < b) {
                std::cout << "Error\n";
                break;
            }
            res = a - b;
            std::cout << res << '\n';
            break;
        case '*':
            res = a * b;
            std::cout << res << '\n';
            break;
        case '^':
            if (num1 == "0") {
                if (num2 == "0")
                    std::cout << "Error" << std::endl;
                else
                    std::cout << "0" << std::endl;
                break;
            }
            res = a ^ b;
            std::cout << res << '\n';
            break;
        case '/':
            if (b == BigZero) {
                std::cout << "Error\n";
                break;
            }
            res = a / b;
            std::cout << res << '\n';
            break;
        case '<':
            std::cout << ((a < b) ? "true" : "false") << '\n';
            break;
        case '>':
            std::cout << ((a > b) ? "true" : "false") << '\n';
            break;
        case '=':
            std::cout << ((a == b) ? "true" : "false") << '\n';
            break;
        default:
            break;
        }
    }

    return 0;
}
