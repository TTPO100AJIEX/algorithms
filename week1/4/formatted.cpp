#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <cstdint>

class BigInt {
public:
    BigInt() = default;
    BigInt(const std::string& value, bool normalized = false);

    size_t length() const {
        return this->value_.size();
    }
    std::string value() const;

    friend std::istream& operator>>(std::istream& os, BigInt& e);
    friend std::ostream& operator<<(std::ostream& os, const BigInt& e);

    friend BigInt operator+(const BigInt& left, const BigInt& right);
    friend BigInt operator-(BigInt left, const BigInt& right);  // left must be bigger than right
    friend BigInt operator*(const BigInt& left, const BigInt& right);
    friend BigInt operator*(BigInt left, unsigned int power_of_10);

private:
    std::string value_;

    void removeLeadingZeros();
    BigInt addLeadingZerosToLength(size_t desired_length) const;
    std::pair<BigInt, BigInt> split(size_t part_length) const;
};

BigInt::BigInt(const std::string& value, bool normalized) : value_(value) {
    if (normalized) {
        return;
    }
    for (std::string::iterator it = this->value_.begin(); it != this->value_.end(); it++) {
        *it -= '0';
    }
}

std::string BigInt::value() const {
    std::string value = this->value_;
    for (std::string::iterator it = value.begin(); it != value.end(); it++) {
        (*it) += '0';
    }
    return (value);
}

std::istream& operator>>(std::istream& instream, BigInt& number) {
    instream >> number.value_;
    for (std::string::iterator it = number.value_.begin(); it != number.value_.end(); it++) {
        *it -= '0';
    }
    return instream;
}
std::ostream& operator<<(std::ostream& outstream, const BigInt& number) {
    for (std::string::const_iterator it = number.value_.cbegin(); it != number.value_.cend();
         it++) {
        outstream << static_cast<char>(*it + '0');
    }
    return outstream;
}

void BigInt::removeLeadingZeros() {
    this->value_.erase(0, this->value_.find_first_not_of(static_cast<char>(0)));
    if (this->length() == 0) {
        this->value_ = "0";
        this->value_[0] -= '0';
    }
}
BigInt BigInt::addLeadingZerosToLength(size_t desired_length) const {
    BigInt result(this->value_, true);
    result.value_.insert(0, desired_length - result.length(), static_cast<char>(0));
    return result;
}
std::pair<BigInt, BigInt> BigInt::split(size_t part_length) const {
    size_t middle_index = this->length() - part_length;
    BigInt part1(this->value_.substr(0, middle_index), true),
        part2(this->value_.substr(middle_index), true);
    return std::make_pair(part1, part2);
}

BigInt operator+(const BigInt& left, const BigInt& right) {
    BigInt result;
    const BigInt* term_ptr;
    if (left.length() > right.length()) {
        result = left;
        term_ptr = &right;
    } else {
        result = right;
        term_ptr = &left;
    }
    const BigInt& term = *term_ptr;
    // now result is not smaller than term
    int extra = 0;
    std::string::reverse_iterator result_it = result.value_.rbegin();
    for (std::string::const_reverse_iterator term_it = term.value_.crbegin();
         term_it != term.value_.crend(); ++term_it, ++result_it) {
        int sum = *result_it + *term_it + extra;
        extra = sum / 10;
        sum %= 10;
        *result_it = sum;
    }
    for (; extra != 0 && result_it != result.value_.rend(); result_it++) {
        int sum = *result_it + extra;
        extra = sum / 10;
        sum %= 10;
        *result_it = sum;
    }
    if (extra != 0) {
        result.value_.insert(result.value_.begin(), extra);
    }
    return result;
}

BigInt operator-(BigInt left, const BigInt& right)  // left must be bigger than right
{
    std::string::reverse_iterator left_it = left.value_.rbegin();
    for (std::string::const_reverse_iterator right_it = right.value_.crbegin();
         right_it != right.value_.crend(); ++right_it, ++left_it) {
        int result = (*left_it) - (*right_it);
        if (result < 0) {
            result += 10;
            (*(left_it + 1))--;
        }
        *left_it = result;
    }
    for (; left_it != left.value_.rend() && *left_it < 0; left_it++) {
        *left_it += 10;
        (*(left_it + 1))--;
    }
    left.removeLeadingZeros();
    return left;
}

BigInt operator*(const BigInt& left, const BigInt& right) {
    if (left.length() < 10 && right.length() < 10) {
        int64_t result = static_cast<int64_t>(std::stoi(left.value())) *
                         static_cast<int64_t>(std::stoi(right.value()));
        return (std::to_string(result));
    }
    size_t parts_length = (std::max(left.length(), right.length()) + 1) / 2;
    auto [a, b] = left.addLeadingZerosToLength(parts_length * 2).split(parts_length);
    auto [c, d] = right.addLeadingZerosToLength(parts_length * 2).split(parts_length);
    BigInt result1 = a * c, result2 = b * d;
    BigInt result = result1 * (2 * parts_length) +
                    ((a + b) * (c + d) - result1 - result2) * parts_length + result2;
    result.removeLeadingZeros();
    return result;
}
BigInt operator*(BigInt left, unsigned int power_of_10) {
    left.value_.append(power_of_10, static_cast<char>(0));
    return left;
}

int main(void) {
    BigInt number1, number2;
    std::cin >> number1 >> number2;
    std::cout << number1 * number2;

    return 0;
}