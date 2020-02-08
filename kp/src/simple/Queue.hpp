#ifndef QUEUE
#define QUEUE
#include <cstddef>

template <class T>
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
            if (next)
                delete next;
        }
    };
    node* first;
    node* last;
    size_t count;

public:
    Queue()
        : first(nullptr)
        , last(nullptr)
        , count(0)
    {
    }
    ~Queue() { delete first; }
    void push(T new_elem)
    {
        ++count;
        if (!first)
            first = last = new node(new_elem);
        else {
            // T temp = last->data;
            // last->data = new_elem;
            last->next = new node(new_elem);
            last = last->next;
        }
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
        return res;
    }
    size_t size() { return count; }
};

#endif //!QUEUE