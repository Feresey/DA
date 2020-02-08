// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "BigInt.hpp"

TBigInt::TBigInt(const std::string& inp)
    : num({})
{
    if (inp.empty())
        return;
    size_t pos = 0;
    while (inp[pos] == '0')
        ++pos;
    long long start, end = static_cast<long long>(inp.size());
    for (start = end - CELL_LENGTH; start >= pos && end > 0; start -= CELL_LENGTH) {
        if (start < 0)
            start = 0;
        num.push_back(atoi(inp.substr(static_cast<size_t>(start), static_cast<size_t>(end - start)).c_str()));
        end -= CELL_LENGTH;
    }
}

TBigInt TBigInt::operator+(const TBigInt& Number) const
{
    TBigInt res(std::max(size(), Number.size()));
    int r = 0;
    for (size_t i = 0; i < res.size(); ++i) {
        res[i] = (*this)[i] + Number[i] + r;
        if (r = (res[i] >= CELL_MAX), r)
            res[i] -= CELL_MAX;
    }
    if (r)
        res.num.push_back(r);
    return res;
}

TBigInt TBigInt::operator-(const TBigInt& Number) const 
{
    TBigInt res(size());
    bool r = 0;
    for (size_t i = 0; i < res.size(); ++i) {
        res[i] = (*this)[i] - Number[i] - (r ? 1 : 0);
        if (r = (res[i] < 0), r)
            res[i] += CELL_MAX;
    }
    if (r)
        res.num.push_back(r);
    return res.FilterZeros();
}

TBigInt TBigInt::operator*(const TBigInt& Number) const 
{
    TBigInt res(size() + Number.size());
    int r;
    for (size_t i = 0; i < size(); ++i) {
        if (!(*this)[i])
            continue;
        r = 0;
        for (size_t j = 0; j < Number.size() || r; ++j) {
            size_t pos = i + j;
            res[pos] += (*this)[i] * Number[j] + r;
            if (r = res[pos] / CELL_MAX, r)
                res[pos] -= r * CELL_MAX;
        }
    }
    return res.FilterZeros();
}

int TBigInt::cmp(const TBigInt& Number) const
{
    if (size() != Number.size())
        return (size() > Number.size()) ? 1 : -1;
    for (size_t i = size() - 1; i + 1 != 0; --i)
        if ((*this)[i] != Number[i])
            return ((*this)[i] > Number[i]) ? 1 : -1;
    return 0;
}

TBigInt TBigInt::operator/(const TBigInt& Number) const
{
    TBigInt res(size()), cv, help;
    for (size_t i = size() - 1; i + 1 != 0; --i) {
        cv.num.insert(cv.num.begin(), (*this)[i]);
        if (!cv.num.back())
            cv.num.pop_back();
        int l, r, x;
        l = x = 0;
        r = CELL_MAX;
        while (l <= r) {
            int m = (l + r) / 2;
            help = TBigInt(std::to_string(m)) * Number;
            if (help < cv || help == cv) {
                x = m;
                l = m + 1;
            } else
                r = m - 1;
        }
        res[i] = x;
        help = TBigInt(std::to_string(x)) * Number;
        cv = cv - help;
    }
    return res.FilterZeros();
}

TBigInt TBigInt::operator^(TBigInt Number)
{
    TBigInt res("1"), BigZero, two("2");
    while (!(Number == BigZero)) {
        if (Number.num.front() & 1)
            res = res * (*this);
        (*this) = (*this) * (*this);
        Number = Number / two;
    }
    return res;
}

std::ostream& operator<<(std::ostream& os, const TBigInt& num)
{
    size_t n = num.size();
    if (!n)
        return os;
    os << num[n - 1];
    for (size_t i = n - 2; i + 1 != 0; --i)
        os << std::setfill('0') << std::setw(CELL_LENGTH) << num[i];

    return os;
}
