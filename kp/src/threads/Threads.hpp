#ifndef THREADS_HPP
#define THREADS_HPP

#include <functional>
#include <future>
#include <mutex>
#include <vector>

class Multithread {

    std::mutex m;
    size_t curr;

    template <class Function, class Container>
    void Run(const Container& src, Function f)
    {
        // using namespace std::placeholders;
        while (true) {
            m.lock();
            if (curr == src.size()) {
                m.unlock();
                return;
            }
            auto local = src[curr++];
            m.unlock();

            f(local);
        }
    }

public:
    template <class Function, class Container>
    void Parallel(Function f, const Container& src, const size_t threads)
    {
        curr = 0;
        using namespace std::placeholders;
        std::vector<std::future<void>> processes(threads);
        auto f_ptr = std::bind(&Multithread::Run<Function, Container>, this, _1, _2);
        for (size_t i = 0; i != threads; ++i)
            processes[i] = std::async(std::launch::async, f_ptr, src, f);
    }
    Multithread() = default;
    ~Multithread() = default;
};

#endif //!THREADS_HPP
