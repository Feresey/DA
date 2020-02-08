#ifndef SIMPLEVECOR
#define SIMPLEVECOR

#include <iterator>
#include <list>
#include <queue>
#include <vector>

class SimpleVector {
    std::vector<uint32_t> jumps;
    std::queue<uint32_t, std::list<uint32_t>> need_compress;

    uint32_t avail_mode, local_size, last;
    uint32_t getMinMode(uint32_t num) const;
    void NewElem(uint32_t elem_size);
    void read(std::ifstream&);
    void _write(std::ofstream& os);

    uint32_t _size;
    uint32_t _count;
    bool modifable;

public:
    class Iter : public std::iterator<std::output_iterator_tag, uint32_t, uint32_t, const uint32_t*, uint32_t> {
        const uint32_t* src;
        std::vector<uint32_t> jumps;
        uint32_t mode, pos, local_pos, local_size, last, jump_index, jump_count, _size;

    public:
        Iter(const SimpleVector* vect, bool end = false);
        uint32_t operator*();
        Iter& operator++();
        Iter& operator++(int) { return ++(*this); };
        bool operator==(const Iter& i) const;
        bool operator!=(Iter const& i) const { return !(*this == i); }
    };

    uint32_t* compressed;

    SimpleVector();
    SimpleVector(std::ifstream& in);
    SimpleVector(const std::vector<uint32_t>& vect);
    SimpleVector(const SimpleVector& vect);
    SimpleVector(SimpleVector&& vect);
    ~SimpleVector()
    {
        delete[] compressed;
    }

    std::vector<uint32_t> to_vector() const;

    void push_back(uint32_t new_elem);
    void check();
    bool empty();

    uint32_t size() { return _count; }
    uint32_t size_local() { return local_size; }
    uint32_t back() { return last; }
    Iter begin();
    Iter cbegin() const;
    Iter end();
    Iter cend() const;

    uint32_t operator[](uint32_t pos) const;

    SimpleVector& operator=(const SimpleVector& rhs);
    SimpleVector& operator=(SimpleVector&& rhs);
    void write(std::ofstream& os);
};

#endif //!SIMPLEVECOR
