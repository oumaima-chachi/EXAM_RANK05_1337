#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>
#include <algorithm>

class bigint
{
    private:
        std::string big;
    public:
        bigint(unsigned int nbr = 0) : big(std::to_string (nbr)){};
        bigint(const bigint &other) : big(other.big){};
        std::string getBig() const {return big;};
        
        bigint operator+(const bigint &other) const;
        bigint &operator+=(const bigint &other);

        bigint &operator++();
        bigint operator++(int);

        bigint operator<<(unsigned int amount) const;
        bigint &operator<<=(unsigned int amount);

        bigint operator>>(const bigint &other) const;
        bigint &operator>>=(const bigint &other);

        bool operator<(const bigint &other) const;
        bool operator>(const bigint &other) const;
        bool operator<=(const bigint &other) const;
        bool operator>=(const bigint &other) const;
        bool operator==(const bigint &other) const;
        bool operator!=(const bigint &other) const;

};

std::ostream &operator<<(std::ostream &os, const bigint &other);

#endif