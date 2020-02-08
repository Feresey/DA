#ifndef SHAZAM
#define SHAZAM

#include <array>
#include <cassert>
#include <fstream>
#include <map>
#include <mutex>

#include "Complex.hpp"
#include "SimpleVector.hpp"

// specifically for the search function (43% faster than usual map)
#include <unordered_map>
// #define unordered_map map // (test)

#include <inttypes.h>
#include <mpg123.h>
#include <vector>

const size_t LENGTH = 4096;
const uint32_t STEP = 1024;

// template <size_t LENGTH = 4096, uint32_t STEP = 1024>
class Shazam {
    using Table = std::vector<std::vector<uint32_t>>;
    std::array<TComplex, LENGTH / 2> InitRoots();
    std::array<double, LENGTH> InitHann();
    std::array<size_t, LENGTH> InitRev();

    std::array<double, LENGTH> hann = InitHann();
    std::array<size_t, LENGTH> rev = InitRev();
    std::array<TComplex, LENGTH / 2> roots = InitRoots();

    // boundaries of the segments of frequencies
    static constexpr uint32_t parts[5] = {
        (100 * LENGTH) / 44100,
        (300 * LENGTH) / 44100,
        (800 * LENGTH) / 44100,
        (1800 * LENGTH) / 44100,
        (2700 * LENGTH) / 44100
    };

    // lengths of segments
    static constexpr uint32_t len[4] = {
        parts[1] - parts[0] + 1,
        parts[2] - parts[1] + 1,
        parts[3] - parts[2] + 1,
        parts[4] - parts[3] + 1
    };

    // number of hashes
    static constexpr size_t max_value = len[3] * len[2] * len[1] * len[0];

    // table of id
    Table SongID;

    // table of time
    Table SongTime;

    uint32_t SongCount;

    // song name
    std::vector<std::pair<std::string, size_t>> Articles;

    size_t LastHashCount;

    // returns the index of the segment in which the point lies
    size_t GetPos(size_t);
    uint32_t hash(const uint32_t arr[4]);
    void FFT(TComplex* X);
    void DFFT(TComplex* X,
        TComplex* X1,
        TComplex* X2);

    // returns the vector of the amplitude values for the song
    std::vector<float> processFile(const std::string&);

    // fills the tables of ID and Time
    std::vector<uint32_t> GetHashes(const std::string& name);

    std::unordered_map<uint32_t, std::unordered_map<int, uint32_t>> _search(const std::string& name);

	std::mutex mutex;
public:
    Shazam()
        : SongID(max_value)
        , SongTime(max_value)
        , SongCount(0)
        , LastHashCount(0)
		, mutex()
    {
        // InitHann(hann);
        // InitRoots(roots);
        // InitRev(rev);
        assert(LENGTH >= parts[4]
            && len[0] && len[1] && len[2] && len[3]);
        std::cout << max_value << std::endl;
        assert(mpg123_init() == MPG123_OK);
    }

    ~Shazam()
    {
        mpg123_exit();
    }

    void append(const std::string& name);
    void CreateBase(const std::vector<std::string>& names, size_t threads = 1);

    // write base to file
    void write(std::ofstream& out);

    // read base from file
    void read(std::ifstream& in);

    std::string search(const std::string&);
};

#endif //!SHAZAM
