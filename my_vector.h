#ifndef BIGINT_OPTIMIZED_MY_VECTOR_H
#define BIGINT_OPTIMIZED_MY_VECTOR_H

#include <cstring>
#include <memory>

typedef unsigned int uint32_t;

struct my_vector {
    my_vector();
    my_vector(size_t size, uint32_t x);
    my_vector(my_vector const &v);

    void push_back(uint32_t value);
    void pop_back();

    std::size_t size() const;

    uint32_t &operator[](size_t ind);
    const uint32_t &operator[](size_t ind) const;
    const uint32_t &back() const;

    my_vector &operator=(my_vector x);

    bool operator==(const my_vector &x) const;

    void swap(my_vector &x);

    ~my_vector();

private:
    size_t _size;
    bool is_big;

    struct big_object
    {
        size_t capacity;
        std::shared_ptr<uint32_t> data;

        big_object()
        {
            capacity = 0;
            data = NULL;
        }

        big_object(uint32_t *x, size_t new_capacity)
        {
            data = std::shared_ptr<uint32_t>(x);
            capacity = new_capacity;
        }

        big_object(const std::shared_ptr<uint32_t> &x, size_t new_capacity)
        {
            data = x;
            capacity = new_capacity;
        }

        ~big_object() = default;
    };

    union container
    {
        container() {};
        ~container() {};

        uint32_t small[4];
        big_object big;

    } data;

    void en_capasity();
};

#endif //BIGINT_OPTIMIZED_MY_VECTOR_H