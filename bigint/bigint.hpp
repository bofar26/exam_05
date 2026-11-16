#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <cstddef>
#include <ostream>
#include <string>

class bigint
{
private:
    // 正序保存十进制数字；始终非空，且除了 "0" 以外没有前导零。
    std::string digits;

    // 返回 min(当前数值, limit)，用于安全地处理任意大的位移次数。
    std::size_t boundedShift(std::size_t limit) const;

public:
    // 不写 explicit，使 42 可以隐式转换成 bigint。
    bigint(std::size_t value = 0);
    bigint(const bigint& other);
    bigint& operator=(const bigint& other);
    ~bigint();

    bigint operator+(const bigint& other) const;
    bigint& operator+=(const bigint& other);
    bigint& operator++();
    bigint operator++(int);

    bigint operator<<(const bigint& count) const;
    bigint operator>>(const bigint& count) const;
    bigint& operator<<=(const bigint& count);
    bigint& operator>>=(const bigint& count);

    bool operator==(const bigint& other) const;
    bool operator!=(const bigint& other) const;
    bool operator<(const bigint& other) const;
    bool operator>(const bigint& other) const;
    bool operator<=(const bigint& other) const;
    bool operator>=(const bigint& other) const;

    friend std::ostream& operator<<(std::ostream& out, const bigint& value);
};

#endif
