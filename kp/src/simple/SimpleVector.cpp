#include <cstring>
#include <fstream>
#include <cassert>

#include "SimpleVector.hpp"

static constexpr uint32_t digits[9] = {
    28,
    14,
    9,
    7,
    5,
    4,
    3,
    2,
    1
};

SimpleVector::SimpleVector()
    : jumps()
    , need_compress()
    , avail_mode(1)
    , local_size(0)
    , last(0)
    , _size(0)
    , _count(0)
    , modifable(true)
    , compressed(nullptr)
{
}

SimpleVector::SimpleVector(std::ifstream& in)
    : SimpleVector()
{
    read(in);
    auto _jumps = SimpleVector();
    _jumps.read(in);
    jumps.resize(_jumps.local_size);
    if (_jumps._count)
        std::copy(_jumps.begin(), _jumps.end(), jumps.begin());
}

SimpleVector& SimpleVector::operator=(const SimpleVector& rhs)
{
    if (this == &rhs)
        return *this;
    _count = rhs._count;
    _size = rhs._size;
    local_size = rhs.local_size;
    need_compress = rhs.need_compress;
    avail_mode = rhs.avail_mode;
    last = rhs.last;
    if (rhs.compressed) {
        compressed = new uint32_t[rhs._size];
        std::memcpy(compressed, rhs.compressed, _count * 4);
    } else
        compressed = nullptr;
    return *this;
}

SimpleVector& SimpleVector::operator=(SimpleVector&& rhs)
{
    _count = rhs._count;
    _size = rhs._size;
    local_size = rhs.local_size;
    need_compress = rhs.need_compress;
    avail_mode = rhs.avail_mode;
    last = rhs.last;
    std::swap(compressed, rhs.compressed);
    return *this;
}

SimpleVector::SimpleVector(const SimpleVector& rhs)
    : jumps(rhs.jumps)
    , need_compress(rhs.need_compress)
    , avail_mode(rhs.avail_mode)
    , local_size(rhs.local_size)
    , last(rhs.last)
    , _size(rhs._size)
    , _count(rhs._count)
    , modifable(true)
    , compressed(nullptr)

{
    if (this == &rhs)
        return;
    if (rhs.compressed) {
        compressed = new uint32_t[rhs._size];
        std::memcpy(compressed, rhs.compressed, _count * 4);
    }
}

SimpleVector::SimpleVector(SimpleVector&& rhs)
    : jumps(rhs.jumps)
    , need_compress(rhs.need_compress)
    , avail_mode(rhs.avail_mode)
    , local_size(rhs.local_size)
    , last(rhs.last)
    , _size(rhs._size)
    , _count(rhs._count)
    , modifable(true)
    , compressed(nullptr)
{
    std::swap(compressed, rhs.compressed);
}

void SimpleVector::read(std::ifstream& in)
{
    in >> _count >> local_size;
    _size = _count;
    if (_count) {
        compressed = new uint32_t[_size];
        in.get();
        in.read(reinterpret_cast<char*>(compressed), _size * 4);
    }
}

SimpleVector::SimpleVector(const std::vector<uint32_t>& vect)
    : SimpleVector()
{
    for (auto new_elem : vect)
        push_back(new_elem);
}

std::vector<uint32_t> SimpleVector::to_vector() const
{
    std::vector<uint32_t> res;
    res.reserve(local_size);
    for (auto i = this->cbegin(); i != this->cend(); ++i)
        res.push_back(*i);
    return res;
}

uint32_t SimpleVector::getMinMode(uint32_t num) const
{
    assert(num < (1U << digits[0]));
    uint32_t index = 1;
    for (; index < 9 && (num < (1U << digits[index])); ++index)
        ;
    return digits[index - 1];
}

void SimpleVector::NewElem(uint32_t elem_size)
{
    uint32_t mode = 28 / elem_size;
    uint32_t hold_mode = mode;
    uint32_t res = 0;
    for (; digits[res] != elem_size; ++res)
        ;
    res = 9 - res;

    while (mode--) {
        res <<= elem_size;
        res += need_compress.empty() ? 0 : need_compress.front();
        if (!need_compress.empty())
            need_compress.pop();
    }
    res <<= 28 % hold_mode;
    if (_size < _count + 1) {
        if (!_size)
            _size = 1;
        else
            _size *= 2;
        uint32_t* temp = new uint32_t[_size];
        if (compressed) {
            std::memcpy(temp, compressed, _count * 4);
            delete[] compressed;
        }
        compressed = temp;
    }
    compressed[_count++] = res;
}

void SimpleVector::push_back(uint32_t new_elem)
{
    assert(modifable);

    uint32_t t = new_elem - last;
    bool ind = (new_elem >= last);
    if (last != new_elem)
        last = new_elem;

    if (ind)
        new_elem = t;
    else
        jumps.push_back(local_size);

    need_compress.push(new_elem);
    local_size++;
    uint32_t temp = getMinMode(new_elem);
    if (temp > avail_mode) {
        //need to compress maximum count of numbers, excluding new_elem
        while (need_compress.size() >= 28 / temp) {
            if (14 < need_compress.size())
                avail_mode = 2;
            else if (9 < need_compress.size())
                avail_mode = 3;
            else if (7 < need_compress.size())
                avail_mode = 4;
            else if (5 < need_compress.size())
                avail_mode = 5;
            else if (4 < need_compress.size())
                avail_mode = 7;
            else if (3 < need_compress.size())
                avail_mode = 9;
            else if (2 < need_compress.size())
                avail_mode = 14;
            else
                avail_mode = 28;
            NewElem(avail_mode);
        }
        avail_mode = need_compress.empty() ? 1 : temp;
    }
    if (need_compress.size() >= 28 / avail_mode) {
        NewElem(avail_mode);
        uint32_t max = 0;
        std::queue<uint32_t, std::list<uint32_t>> trash;
        while (!need_compress.empty()) {
            uint32_t val = need_compress.front();
            need_compress.pop();
            if (val > max)
                max = val;
            trash.push(val);
        }
        need_compress = trash;
        avail_mode = getMinMode(max);
    }
}

void SimpleVector::check()
{
    if (!need_compress.empty())
        NewElem(avail_mode);
    modifable = false;
}

bool SimpleVector::empty()
{
    check();
    return local_size == 0;
}

SimpleVector::Iter SimpleVector::begin()
{
    check();
    return Iter(this, local_size == 0);
}

SimpleVector::Iter SimpleVector::cbegin() const
{
    return Iter(this, local_size == 0);
}

SimpleVector::Iter SimpleVector::end()
{
    check();
    return Iter(this, true);
}

SimpleVector::Iter SimpleVector::cend() const
{
    return Iter(this, true);
}

uint32_t SimpleVector::operator[](uint32_t pos) const
{
    assert(pos < local_size && need_compress.empty());
    auto it = Iter(this, local_size == 0);
    while (pos--)
        ++it;
    return *it;
}

void SimpleVector::_write(std::ofstream& of)
{
    check();
    of << _count << ' ' << local_size << '\n';
    if (compressed) {
        of.write(reinterpret_cast<char*>(compressed), _count * 4);
        of << '\n';
    }
}

void SimpleVector::write(std::ofstream& of)
{
    _write(of);
    SimpleVector(jumps)._write(of);
}

SimpleVector::Iter::Iter(const SimpleVector* vect, bool end)
    : src(vect->compressed)
    , jumps(vect->jumps)
    , mode(0)
    , pos(0)
    , local_pos(0)
    , local_size(end ? 0 : vect->local_size)
    , last(0)
    , jump_index(0)
    , jump_count(0)
    , _size(vect->_count)
{
    if (!end && src)
        mode = digits[9 - (src[0] >> 28)];
    else
        pos = _size;
}

uint32_t SimpleVector::Iter::operator*()
{
    if (pos == _size)
        return 0;
    return last + ((src[pos] >> (28 - (local_pos + 1) * mode)) & (-1U >> (32 - mode)));
}

SimpleVector::Iter& SimpleVector::Iter::operator++()
{
    if (jumps.size() > jump_count && jumps[jump_count] == ++jump_index) {
        last = 0;
        ++jump_count;
    } else
        last = **this;
    if (!local_size--)
        return *this;

    if (++local_pos >= 28 / mode) {
        local_pos = 0;
        if (++pos == _size)
            return *this;
        mode = digits[9 - (src[pos] >> 28)];
    }

    return *this;
}

bool SimpleVector::Iter::operator==(const Iter& i) const
{
    return (local_size == 0 && i.local_size == 0)
        || ((i.src == src)
               && pos == i.pos
               && local_pos == i.local_pos);
}

