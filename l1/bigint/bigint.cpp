#include "bigint.hpp"
        
bigint bigint::operator+(const bigint &other) const
{ 
    bigint result(*this);
    result += other;
    return result;
}
bigint &bigint::operator+=(const bigint &other)
{
    int carry = 0;
    int i = big.size() - 1;
    int j = other.big.size() - 1;
    std::string result;
    while (i >= 0 || j >= 0 || carry)
    {
        int x = i >= 0 ? big[i] - '0' : 0;
        int y = j >= 0 ? other.big[j] - '0' : 0;
        int sum = x + y + carry;
        carry = sum / 10;
        result.push_back((sum % 10) + '0');
        --i;
        --j;
    }
    std::reverse(result.begin(), result.end());
    big = result;
    return *this;
}
bigint &bigint::operator++()
{
    bigint dummy(1);
    *this += dummy;
    return *this;
}
bigint bigint::operator++(int)
{
    bigint dummy(1);
    bigint result(*this);
    *this += dummy;
    return result;
}
bigint bigint::operator<<(unsigned int amount) const
{
    bigint result(*this);
    result <<= amount;
    return result;
}
bigint &bigint::operator<<=(unsigned int amount)
{
    if (big != "0")
        big.append(amount, '0');
    return *this;
}

bigint bigint::operator>>(const bigint &other) const
{
    bigint result(*this);
    result >>= other;
    return result;
}
bigint &bigint::operator>>=(const bigint &other)
{
    const unsigned long size = big.size();
    const unsigned long amount = std::atol(other.big.c_str());
    if (amount >= size)
        big = '0';
    else
        big.erase(size - amount);
    return *this;
}

bool bigint::operator<(const bigint &other) const
{
    return (big.size() != other.big.size())
        ? big.size() < other.big.size()
        : big < other.big;
}
bool bigint::operator>(const bigint &other) const
{
    return (other < *this);
}
bool bigint::operator<=(const bigint &other) const
{
    return !(*this > other);
}
bool bigint::operator>=(const bigint &other) const
{
    return !(*this < other);
}
bool bigint::operator==(const bigint &other) const
{
    return big == other.big;
}
bool bigint::operator!=(const bigint &other) const
{
    return big != other.big;
}
std::ostream &operator<<(std::ostream &os, const bigint &other)
{
    os << other.getBig();
    return os;
}