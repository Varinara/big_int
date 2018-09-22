#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <cstddef>
#include <iosfwd>
#include <vector>
#include "my_vector.h"

struct big_integer {
    big_integer();
    big_integer(big_integer const &other);
    big_integer(int a);
    big_integer(unsigned int a);

    explicit big_integer(my_vector const &x, bool s);
    explicit big_integer(std::string const &x);

    ~big_integer();

    big_integer &operator=(big_integer const &other);
    big_integer &operator+=(big_integer const &x);
    big_integer &operator-=(big_integer const &x);
    big_integer &operator*=(big_integer const &x);
    big_integer &operator/=(big_integer const &x);
    big_integer &operator%=(big_integer const &x);
    big_integer &operator&=(big_integer const &x);
    big_integer &operator|=(big_integer const &x);
    big_integer &operator^=(big_integer const &x);

    big_integer &operator<<=(int x);

    big_integer &operator>>=(int x);

    big_integer operator+() const;

    big_integer operator-() const;

    big_integer operator~() const;

    friend bool operator==(big_integer const &a, big_integer const &b);
    friend bool operator!=(big_integer const &a, big_integer const &b);
    friend bool operator<(big_integer const &a, big_integer const &b);
    friend bool operator>(big_integer const &a, big_integer const &b);
    friend bool operator<=(big_integer const &a, big_integer const &b);
    friend bool operator>=(big_integer const &a, big_integer const &b);

    friend std::string to_string(big_integer const &a);

private:
    bool sign = true;
    my_vector data;

    void swap(big_integer &b);
    void del_zeros();
    my_vector twos_complement(big_integer const &x);
    std::pair<big_integer, big_integer> div_and_mod(big_integer const &a, big_integer const &b);
    my_vector quotient(my_vector a, uint32_t b);
    my_vector remainder(my_vector a, uint32_t b);
    template<class FunctorT>
    big_integer &apply_bitwise_operation(big_integer const &x, FunctorT functor);
};

big_integer operator+(big_integer a, big_integer const &b);
big_integer operator-(big_integer a, big_integer const &b);
big_integer operator*(big_integer a, big_integer const &b);
big_integer operator/(big_integer a, big_integer const &b);
big_integer operator%(big_integer a, big_integer const &b);
big_integer operator&(big_integer a, big_integer const &b);
big_integer operator|(big_integer a, big_integer const &b);
big_integer operator^(big_integer a, big_integer const &b);
big_integer operator<<(big_integer a, int b);
big_integer operator>>(big_integer a, int b);

bool operator==(big_integer const &a, big_integer const &b);
bool operator!=(big_integer const &a, big_integer const &b);
bool operator<(big_integer const &a, big_integer const &b);
bool operator>(big_integer const &a, big_integer const &b);
bool operator<=(big_integer const &a, big_integer const &b);
bool operator>=(big_integer const &a, big_integer const &b);

std::string to_string(big_integer const &a);
std::ostream &operator<<(std::ostream &s, big_integer const &a);

#endif // BIG_INTEGER_H
