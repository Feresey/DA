#ifndef BIGINT
#define BIGINT

#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

const int CELL_LENGTH = 4;
const int CELL_MAX = static_cast<int>(pow(10, CELL_LENGTH));
static int zero = 0;

class TBigInt {
    std::vector<int> num;
    int& operator[](size_t pos)
    {
        if (num.size() <= pos)
            return zero;
        else
            return num[pos];
    }
    const int& operator[](size_t pos) const
    {
        return static_cast<TBigInt>(*this)[pos];
    }
    TBigInt& FilterZeros()
    {
        while (size() > 1 && !num.back())
            num.pop_back();
        return *this;
    }
    size_t size() const { return num.size(); }

    int cmp(const TBigInt& Number) const;

public:
    explicit TBigInt(const std::string& src);
    explicit TBigInt(size_t n = 1)
        : num(n, 0U)
    {
    }
    ~TBigInt(){};

    TBigInt operator+(const TBigInt&) const;
    TBigInt operator-(const TBigInt&) const;
    TBigInt operator*(const TBigInt&)const;
    TBigInt operator/(const TBigInt&) const;
    TBigInt operator^(TBigInt);
    bool operator==(const TBigInt& Number) const { return cmp(Number) == 0; }
    bool operator<(const TBigInt& Number) const { return cmp(Number) == -1; }
    bool operator>(const TBigInt& Number) const { return cmp(Number) == 1; }
    friend std::ostream& operator<<(std::ostream&, const TBigInt&);
};

#endif
