#include "my_vector.h"

my_vector::my_vector()
{
    _size = 0;
    is_big = false;
}

my_vector::my_vector(size_t size, uint32_t x)
{
    this->_size = size;
    if (size <= 4) {
        std::fill(data.small, data.small + size, x);
        is_big = false;
    } else {
        is_big = true;
        new(&data.big)big_object(new uint32_t[size], size);
        std::fill(data.big.data.get(), data.big.data.get() + size, x);
    }
}

void my_vector::push_back(uint32_t value)
{
    detach();
    if (!is_big && _size < 4)
    {
        data.small[_size++] = value;
    } else
        {
        if (!is_big || _size == data.big.capacity)
            en_capasity();
        data.big.data.get()[_size] = value;
        _size++;
    }
}

std::size_t my_vector::size() const 
{
    return _size;
}

uint32_t &my_vector::operator[](size_t ind) {
    if (is_big) {
        detach();
        return data.big.data.get()[ind];
    } else {
        return data.small[ind];
    }
}
const uint32_t &my_vector::operator[](size_t ind) const
{
    if (is_big)
        return data.big.data.get()[ind];
    else
        return data.small[ind];
}

const uint32_t &my_vector::back() const
{
    if (is_big)
        return data.big.data.get()[_size - 1];
    else
        return data.small[_size - 1];
}

void my_vector::pop_back()
{
    _size--;
}

my_vector::~my_vector() {
    if (is_big)
        data.big.~big_object();
}

my_vector::my_vector(const my_vector &v) {
    _size = v._size;
    is_big = v.is_big;
    if (is_big) {
        new(&data.big)big_object(v.data.big.data, v.data.big.capacity);
    } else {
        for (size_t i = 0; i < 4; i++)
            data.small[i] = v.data.small[i];
    }
}

my_vector &my_vector::operator=(my_vector rhs) {
    swap(rhs);
    return *this;
}

void my_vector::en_capasity() {
    if (is_big) {
        auto *x = new uint32_t[2 * data.big.capacity];
        std::copy(data.big.data.get(), data.big.data.get() + data.big.capacity, x);
        data.big.data = std::shared_ptr<uint32_t>(x, std::default_delete<uint32_t[]>());
    } else {
        uint32_t x[4];
        for (size_t i = 0; i < 4; i++)
            x[i] = data.small[i];
        new(&data.big)big_object(new uint32_t[8], 1);
        for (size_t i = 0; i < 4; i++)
            data.big.data.get()[i] = x[i];
        is_big = true;
    }
    data.big.capacity *= 2;
}

bool my_vector::operator==(const my_vector &x) const {
    if (_size != x.size()) {
        return false;
    }
    for (size_t i = 0; i < _size; i++) {
        if (data.big.data.get()[i] != x[i]) {
            return false;
        }
    }
    return true;
}

void my_vector::swap(my_vector &other) {
    std::swap(is_big, other.is_big);
    std::swap(_size, other._size);

    char x[sizeof(container)];
    memcpy(x, &data, sizeof(container));
    memcpy(&data, &other.data, sizeof(container));
    memcpy(&other.data, x, sizeof(container));
}

void my_vector::detach() {
    if (!is_big || data.big.data.unique()) {
        return;
    }
    auto *x = new uint32_t[data.big.capacity];
    std::copy(data.big.data.get(), data.big.data.get() + data.big.capacity, x);
    data.big.data = std::shared_ptr<uint32_t>(x,std::default_delete<uint32_t[]>());
}