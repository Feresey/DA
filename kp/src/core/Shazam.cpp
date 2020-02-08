#include <cmath>
#include <cstring>
#include <future>
#include <iostream>
#include <mutex>

#include "Shazam.hpp"
#include "Threads.hpp"

std::array<TComplex, LENGTH / 2> Shazam::InitRoots()
{
    std::array<TComplex, LENGTH / 2> res;
    double angle = -2 * M_PI / LENGTH;

    TComplex W(std::cos(angle), std::sin(angle));
    TComplex root(1, 0);

    for (size_t idx = 0; idx < LENGTH / 2; ++idx, root = root * W)
        res[idx] = root;

    return res;
}

std::array<double, LENGTH> Shazam::InitHann()
{
    std::array<double, LENGTH> res{};
    for (size_t i = 0; i < LENGTH - 1UL; ++i)
        res[i] = 0.5 * (1UL - cos(M_PI / double(LENGTH - 1UL) * 2UL * double(i)));
    return res;
}

std::array<size_t, LENGTH> Shazam::InitRev()
{
    std::array<size_t, LENGTH> _rev{};
    size_t log_n = -1UL, temp = LENGTH;
    while (temp) {
        temp >>= 1;
        ++log_n;
    }
    for (size_t i = 0; i < LENGTH; ++i) {
        _rev[i] = 0;
        for (size_t j = 0; j < log_n; ++j)
            if (i & (1UL << j))
                _rev[i] |= 1UL << (log_n - 1 - j);
    }
    return _rev;
}

size_t Shazam::GetPos(size_t num)
{
    assert(num < parts[4] && num >= parts[0]);
    if (num < parts[1] && num >= parts[0])
        return 0;
    if (num < parts[2] && num >= parts[1])
        return 1;
    if (num < parts[3] && num >= parts[2])
        return 2;
    if (num < parts[4] && num >= parts[3])
        return 3;
    throw std::exception();
}

uint32_t Shazam::hash(const uint32_t arr[4])
{
    return (arr[0] - parts[0])
        + (arr[1] - parts[1]) * len[0]
        + (arr[2] - parts[2]) * len[1] * len[0]
        + (arr[3] - parts[3]) * len[2] * len[1] * len[0];
}

void Shazam::DFFT(TComplex* X,
    TComplex* X1,
    TComplex* X2)
{
    FFT(X);
    constexpr size_t N_2 = LENGTH / 2;
    X1[0].re = X[0].re;
    X2[0].re = X[0].im;
    X1[N_2].re = X[N_2].re;
    X2[N_2].re = X[N_2].im;
    X2[0].im = X1[0].im = X1[N_2].im = X2[N_2].im = 0;
    for (size_t k = 1; k < N_2; ++k) {
        X1[k] = TComplex((X[k].re + X[LENGTH - k].re), (X[k].im - X[LENGTH - k].im)) / 2;
        X2[k] = TComplex((X[k].im + X[LENGTH - k].im), (X[LENGTH - k].re - X[k].re)) / 2;
        X1[LENGTH - k] = { X1[k].re, -X1[k].im };
        X2[LENGTH - k] = { X2[k].re, -X2[k].im };
    }
}

void Shazam::FFT(TComplex* X)
{
    for (size_t i = 0; i < LENGTH; ++i)
        if (i < rev[i])
            std::swap(X[i], X[rev[i]]);

    for (size_t ln = 2; ln <= LENGTH; ln <<= 1) {
        for (size_t i = 0; i < LENGTH; i += ln) {
            size_t ln_2 = ln >> 1;
            for (size_t j = 0; j < ln_2; ++j) {
                TComplex u = X[i + j],
                         v = X[i + j + ln_2] * roots[LENGTH / ln * j];
                X[i + j] = u + v;
                X[i + j + ln_2] = u - v;
            }
        }
    }
}

std::vector<float> Shazam::processFile(const std::string& name)
{
    auto mh = mpg123_new(NULL, NULL);
    assert(mh != NULL);
    assert(mpg123_param(mh, MPG123_FLAGS, MPG123_MONO_MIX | MPG123_QUIET | MPG123_FORCE_FLOAT, 0.) == MPG123_OK);

    auto errorCode = mpg123_open(mh, name.c_str());
    if (errorCode != MPG123_OK) {
        std::cout << "Error opening file " << name << std::endl;
        return {};
    }
    // assert(errorCode == MPG123_OK);
    long rate;
    int channels, encoding;
    errorCode = mpg123_getformat(mh, &rate, &channels, &encoding);
    if (errorCode != MPG123_OK) {
        std::cout << "Corrupted file " << name << "!!!" << std::endl;
        return {};
    }
    // assert(errorCode == MPG123_OK);
    if (rate != 44100) {
        std::cout << "Rate is: " << rate << std::endl;
        mpg123_delete(mh);
        return {};
    }
    const size_t part_size = 1024;
    unsigned char part[part_size];
    size_t bytesRead;
    std::vector<float> samples;
    size_t bytesProcessed = 0;
    do {
        int err = mpg123_read(mh, part, part_size, &bytesRead);
        samples.resize((bytesProcessed + bytesRead) / 4 + 1);
        memcpy(reinterpret_cast<unsigned char*>(samples.data()) + bytesProcessed, part, bytesRead);
        bytesProcessed += bytesRead;
        if (err == MPG123_DONE)
            break;

        assert(err == MPG123_OK);
    } while (bytesRead > 0);
    samples.resize(bytesProcessed / 4);
    errorCode = mpg123_close(mh);
    assert(errorCode == MPG123_OK);
    mpg123_delete(mh);
    return samples;
}

std::vector<uint32_t> Shazam::GetHashes(const std::string& name)
{
    const std::vector<float> samples = processFile(name);

    std::vector<uint32_t> res;
    res.reserve(samples.size() / STEP);
    uint32_t start = 0;
    for (; start < samples.size(); start += 2 * STEP) {
        TComplex first[LENGTH],
            second[LENGTH],
            tmp[LENGTH];
        size_t end = start + LENGTH;
        for (size_t i = start, idx = 0; i < end; ++i, ++idx)
            tmp[idx] = (i >= samples.size())
                ? TComplex{ 0, 0 }
                : TComplex{ samples[i] * hann[idx], (i + STEP < samples.size()) ? (samples[i + STEP] * hann[idx]) : 0 };

        DFFT(tmp, first, second);
        double max1 = -1,
               max2 = -1,
               temp;
        uint32_t pos1[] = { parts[0], parts[1], parts[2], parts[3] },
                 pos2[] = { parts[0], parts[1], parts[2], parts[3] };
        size_t pos, pos_prev = 0;
        for (uint32_t i = parts[0]; i < parts[4]; ++i) {
            if (pos = GetPos(i), pos != pos_prev) {
                max1 = -1;
                max2 = -1;
            }
            if (temp = first[i].Abs(), temp > max1) {
                max1 = temp;
                pos1[pos] = i;
            }
            if (temp = second[i].Abs(), temp > max2) {
                max2 = temp;
                pos2[pos] = i;
            }
            pos_prev = pos;
        }
        res.push_back(hash(pos1));
        res.push_back(hash(pos2));
    }

    return res;
}

void Shazam::append(const std::string& name)
{
    const std::vector<uint32_t> hashes = GetHashes(name);

    mutex.lock();

    std::cout << "process file \"" << name << "\" \n";
    uint32_t count = -1U;
    for (auto i : hashes) {
        SongID[i].push_back(SongCount);
        SongTime[i].push_back(++count);
    }
    std::cout << "Song count: " << ++SongCount << "\thash count: " << hashes.size() << '\n';
    Articles.push_back({ name, hashes.size() });

    mutex.unlock();
}

void Shazam::CreateBase(const std::vector<std::string>& names, size_t threads)
{
    auto f = std::bind(&Shazam::append, this, std::placeholders::_1);
    Multithread aga;
    aga.Parallel(f, names, threads);
}

void Shazam::write(std::ofstream& out)
{
    std::cout << "prepare to write...\n";
    out << LENGTH << ' ' << STEP << ' ' << max_value << '\n';
    size_t count = -1UL;
    for (auto i : SongID) {
        ++count;
        if (i.empty())
            continue;
        out << count << ' ';
        SimpleVector(i).write(out);
    }
    count = -1UL;
    for (auto i : SongTime) {
        ++count;
        if (i.empty())
            continue;
        out << count << ' ';
        SimpleVector(i).write(out);
    }
    out << "0\n"
        << Articles.size() << '\n';
    for (auto i : Articles)
        out << i.second << '\n'
            << i.first << '\n';
    std::cout << "WRITE!!!\n";
}

void Shazam::read(std::ifstream& in)
{
    size_t len, step, count;
    std::cout << "prepare to read...\n";
    in >> len >> step >> count;
    assert(len == LENGTH
        && step == STEP
        && count == max_value);
    size_t length = 0, compressed = 0;
    size_t h, h_prev = 0;
    while (in >> h, h > h_prev || !h_prev) {
        auto s = SimpleVector(in);
        SongID[h] = s.to_vector();
        length += SongID[h].size();
        compressed += s.size();
        h_prev = h;
    }

    h_prev = 0;
    do {
        auto s = SimpleVector(in);
        SongTime[h] = s.to_vector();
        length += SongTime[h].size();
        compressed += s.size();
        h_prev = h;
    } while (in >> h, h > h_prev || !h_prev);

    in >> SongCount;
    Articles.reserve(SongCount);
    std::string line;
    step = SongCount;
    while (step--) {
        in >> len;
        in.get();
        std::getline(in, line);
        Articles.push_back({ line, len });
    }
    std::cout << length << "\nREAD!!!\n"
              << compressed << '\n';
}

std::unordered_map<uint32_t, std::unordered_map<int, uint32_t>> Shazam::_search(const std::string& name)
{
    // map<SongID, map<TimeOffset, Count>>
    std::unordered_map<uint32_t, std::unordered_map<int, uint32_t>> res;
    std::cout << "process file \"" << name << "\" \n";
    std::vector<uint32_t> hashes = GetHashes(name);
    LastHashCount = hashes.size();
    std::cout << "hash count: " << LastHashCount << '\n';

    for (uint32_t i = 0; i != hashes.size(); ++i) {
        for (auto iter = SongTime[hashes[i]].begin(), idx = SongID[hashes[i]].begin();
             iter != SongTime[hashes[i]].end();
             ++iter, ++idx)
            res[*idx][int(*iter) - int(i)]++;
    }
    return res;
}

std::string Shazam::search(const std::string& name)
{
    auto base = _search(name);
    // map<MatchPercent, pair<SongID, TimeOffset>>
    std::map<double, std::pair<uint32_t, int>> results;
    for (auto id : base) {
        int offset = 0;
        double max = 0;
        for (auto i : id.second)
            if (double(i.second) > max) {
                max = double(i.second);
                offset = i.first;
            }
        max *= 100.0 / double(LastHashCount);
        if (max < 101 && max > 2)
            results[max] = { id.first, offset };
    }

    // #ifdef DEBUG
    std::cout.precision(2);

    for (auto i : results)
        std::cout << "match: " << std::fixed << i.first << "%\t"
                  << "name: \"" << Articles[i.second.first].first << "\" "
                  << "time offset: " << double(i.second.second) / 44100 * STEP << '\n';
    std::cout << std::endl;
    // #endif

    auto temp = results.rbegin();
    return (!results.empty() && temp->first > 10) ? Articles[temp->second.first].first : "! NOT FOUND";
}
