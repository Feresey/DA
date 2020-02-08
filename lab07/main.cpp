#include <cmath>
#include <iostream>

inline long long len(long long num)
{
    long long res = 0;
    while (num /= 10, res++, num)
        ;
    return res;
}

int main()
{
    long long n, m, res;
    std::cin >> n >> m;
    res = (n % m) ? 0 : -1;
    while (n) {
        if (len(n) != len(n - 1))
            break;
        long long temp = pow(10, len(n) - 1);
        temp = temp % m || !temp ? temp : temp - 1;
        res += n / m - temp / m;
        n /= 10;
    }
    std::cout << (res < 0 ? 0 : res) << std::endl;
    return 0;
}
