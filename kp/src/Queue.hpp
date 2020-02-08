#ifndef QUEUE
#define QUEUE
#include <cstddef>

template<size_t LENGTH , uint32_t STEP>
class Queue {
    struct node {
        T data;
        node* next;
        node(T value)
            : data(value)
            , next(nullptr)
        {
        }
        ~node()
        {
            std::cout << data << ' ';
            if (next)
                delete next;
        }
    };
    node* first;
    node* last;
    uint8_t count;

public:
    Queue()
        : first(nullptr)
        , last(nullptr)
        , count(0)
    {
    }
    ~Queue()
    {
        if (first) {
            delete first;
            std::cout << std::endl;
        }
    }
    void push(T new_elem)
    {
        ++count;
        if (!first)
            first = last = new node(new_elem);
        else
            last = last->next = new node(new_elem);
    }
    bool empty() { return first == nullptr; }

    T pop()
    {
        if (empty())
            throw 1;
        --count;
        T res;
        res = first->data;
        node* del = first;
        first = first->next;
        del->next = nullptr;
        delete del;
        if (!first)
            last = nullptr;
        return res;
    }
    size_t size() { return static_cast<size_t>(count); }

    T front() { return first->data; }
    void clear()
    {
        delete first;
        first = last = nullptr;
    }
    // Queue<T>& operator=(const Queue<T>& src)
    // {
    //     // Queue<T> rest = Queue<T>();
    //     if (!src.first) {
    //         first = nullptr;
    //         return *this;
    //     }
    //     if (first)
    //         delete first;
    //     first = last = nullptr;
    //     node* pos = src.first;
    //     do {
    //         last = last->next = pos;
    //         pos = pos->next;
    //     } while (pos);
    //     // node* new_elem = new node(src.first->data);
    //     // first = src.first.data;
    //     return *this;
    // }
};

#endif //!QUEUE