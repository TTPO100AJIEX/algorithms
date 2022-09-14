#include <iostream>
#include <vector>
#include <cstdint>

class BigInt
{
public:
    static inline std::pair <uint8_t, uint8_t> split_pair(uint8_t pair);
    static inline uint8_t merge_pair(uint8_t low, uint8_t high);

    BigInt() = default;

    inline size_t length() const;
    
    friend std::istream& operator>> (std::istream& outstream, BigInt& number);
    friend std::ostream& operator<< (std::ostream& outstream, const BigInt& number);
    
    BigInt& operator+= (const BigInt& right);
    friend BigInt operator+ (BigInt left, const BigInt& right);

private:
    mutable std::vector <uint8_t> value_;

    inline void normalize(size_t desired_length) const;
};

inline std::pair <uint8_t, uint8_t> BigInt::split_pair(uint8_t pair)
{
    return std::make_pair(pair >> 4, pair & 0xf);
}
inline uint8_t BigInt::merge_pair(uint8_t low, uint8_t high)
{
    return(high + (low << 4));
}

inline size_t BigInt::length() const
{
    uint8_t last_digit = (this->value_.back() << 4);
    return(2 * this->value_.size() - (last_digit == 0));
}

std::istream& operator>>(std::istream& instream, BigInt& number)
{
    std::string value;
    instream >> value;
    number.value_.reserve((value.size() + 1) >> 1);
    for (std::string::reverse_iterator read_it = value.rbegin(); read_it != value.rend(); ++read_it)
    {
        uint8_t low = *read_it - '0', high = read_it + 1 == value.rend() ? 0 : *(++read_it) - '0';
        number.value_.push_back(BigInt::merge_pair(low, high));
    }
    return instream;
}
std::ostream& operator<<(std::ostream& outstream, const BigInt& number)
{
    for (std::vector<uint8_t>::const_reverse_iterator iter = number.value_.rbegin(); iter != number.value_.rend(); ++iter)
    {
        auto [ low, high ] = BigInt::split_pair(*iter);
        outstream << (unsigned int)(high) << (unsigned int)(low);
    }
    return outstream;
}

inline void BigInt::normalize(size_t desired_length) const
{
    desired_length = (desired_length + 1) >> 1;
    if (desired_length <= this->value_.size())
    {
        while (this->value_.back() == 0 && desired_length < this->value_.size()) this->value_.pop_back();
        return;
    }
    this->value_.resize(desired_length);
}

BigInt& BigInt::operator+= (const BigInt& right)
{
    this->normalize(std::max(right.length(), this->length()) + 1);
    uint8_t extra = 0;
    std::vector<uint8_t>::iterator this_it = this->value_.begin();
    for (std::vector<uint8_t>::iterator right_it = right.value_.begin(); right_it != right.value_.end(); ++right_it, ++this_it)
    {
        auto [ this_low, this_high ] = BigInt::split_pair(*this_it);
        auto [ right_low, right_high ] = BigInt::split_pair(*right_it);
        this_low += right_low + extra;
        extra = 0;
        if (this_low > 9)
        {
            this_low += 6;
            this_low &= 0xf;
            extra = 1;
        }
        this_high += right_high + extra;
        extra = 0;
        if (this_high > 9)
        {
            this_high += 9;
            this_high &= 0xf;
            extra = 1;
        }
        *this_it = BigInt::merge_pair(this_low, this_high);
    }
    this->normalize(1);
    return *this;
}
BigInt operator+ (BigInt left, const BigInt& right) { return left += right; }

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    BigInt number1, number2;
    std::cin >> number1 >> number2;
    number1 += number2;
    std::cout << number1;
    return 0;
}