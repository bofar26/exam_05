#include "bigint.hpp"
#include <algorithm>
#include <stdexcept>

bigint::bigint(std::size_t value)
{
    // do-while 保证 value == 0 时也会存入一个 '0'。
    do
    {
        digits += static_cast<char>('0' + value % 10);
        value /= 10;
    } while (value != 0);
    std::reverse(digits.begin(), digits.end());
}

bigint::bigint(const bigint& other) : digits(other.digits) {}

bigint& bigint::operator=(const bigint& other)
{
    digits = other.digits;
    return *this;
}

bigint::~bigint() {}

bigint bigint::operator+(const bigint& other) const
{
    bigint result;
    result.digits.clear();
    std::size_t i = digits.size();
    std::size_t j = other.digits.size();
    int carry = 0;

    // 从个位开始做竖式加法；用“剩余位数”避免无符号下标减到 -1。
    while (i > 0 || j > 0 || carry != 0)
    {
        int sum = carry;
        if (i > 0)
            sum += digits[--i] - '0';
        if (j > 0)
            sum += other.digits[--j] - '0';
        result.digits += static_cast<char>('0' + sum % 10);
        carry = sum / 10;
    }
    std::reverse(result.digits.begin(), result.digits.end());
    return result;
}

bigint& bigint::operator+=(const bigint& other)
{
    *this = *this + other;
    return *this;
}

bigint& bigint::operator++()
{
    *this += 1;
    return *this;
}

bigint bigint::operator++(int)
{
    bigint old(*this);
    ++(*this);
    return old;
}

std::size_t bigint::boundedShift(std::size_t limit) const
{
    std::size_t count = 0;
    for (std::size_t i = 0; i < digits.size(); ++i)
    {
        std::size_t digit = digits[i] - '0';
        // 在 count * 10 + digit 之前判断，避免机器整数溢出。
        if (count > limit / 10
            || (count == limit / 10 && digit > limit % 10))
            return limit;
        count = count * 10 + digit;
    }
    return count;
}

bigint& bigint::operator<<=(const bigint& count)
{
    if (digits == "0")
        return *this;
    const std::size_t available = digits.max_size() - digits.size();
    // digits 非空，所以 available + 1 不会溢出；用它表示“放不下”。
    const std::size_t n = count.boundedShift(available + 1);
    if (n > available)
        throw std::length_error("bigint: digit shift is too large");
    digits.append(n, '0');
    return *this;
}

bigint& bigint::operator>>=(const bigint& count)
{
    const std::size_t n = count.boundedShift(digits.size());
    if (n >= digits.size())
        digits = "0";
    else
        digits.erase(digits.size() - n);
    return *this;
}

bigint bigint::operator<<(const bigint& count) const
{
    bigint result(*this);
    result <<= count;
    return result;
}

bigint bigint::operator>>(const bigint& count) const
{
    bigint result(*this);
    result >>= count;
    return result;
}

bool bigint::operator==(const bigint& other) const
{
    return digits == other.digits;
}

bool bigint::operator!=(const bigint& other) const
{
    return !(*this == other);
}

bool bigint::operator<(const bigint& other) const
{
    if (digits.size() != other.digits.size())
        return digits.size() < other.digits.size();
    return digits < other.digits;
}

bool bigint::operator>(const bigint& other) const
{
    return (other < *this);
}

bool bigint::operator<=(const bigint& other) const
{
    return !(other < *this);
}

bool bigint::operator>=(const bigint& other) const
{
    return !(*this < other);
}

std::ostream& operator<<(std::ostream& out, const bigint& value)
{
    out << value.digits;
    return out;
}
