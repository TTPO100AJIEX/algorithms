#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <cstdint>
#include <charconv>

class BigInt {
public:
    BigInt() = default;
    BigInt(const std::string& value, bool normalized = false);
    BigInt(size_t length);

    static void stringFormat(std::string& value);
    std::string value() const;

    friend std::istream& operator>>(std::istream& outstream, BigInt& number);
    friend std::ostream& operator<<(std::ostream& outstream, const BigInt& number);

    BigInt& operator*=(const BigInt& right);
    BigInt& operator+=(const BigInt& right);
    void inplaceSum(const BigInt& right, size_t offset = 0);
    BigInt& operator-=(const BigInt& right);  // "this" must be bigger than right

private:
    mutable std::string value_;  // reversed base-10 notation

    void normalizeToLength(size_t desired_length) const;
};

BigInt::BigInt(const std::string& value, bool normalized) : value_(value) {
    if (!normalized) {
        BigInt::stringFormat(this->value_);
    }
}
BigInt::BigInt(size_t length) {
    this->value_.reserve(length);
}

void BigInt::stringFormat(std::string& value) {
    size_t length = value.size();
    for (size_t i = 0; i < length / 2; ++i) {
        value[i] -= '0';
        value[length - i - 1] -= '0';
        std::swap(value[i], value[length - i - 1]);
    }
    if (length % 2 == 1) {
        value[length / 2] -= '0';
    }
}
std::string BigInt::value() const {
    std::string value = this->value_;
    size_t length = value.size();
    for (size_t i = 0; i < length / 2; ++i) {
        value[i] += '0';
        value[length - i - 1] += '0';
        std::swap(value[i], value[length - i - 1]);
    }
    if (length % 2 == 1) {
        value[length / 2] += '0';
    }
    return (value);
}
std::istream& operator>>(std::istream& instream, BigInt& number) {
    instream >> number.value_;
    BigInt::stringFormat(number.value_);
    return instream;
}
std::ostream& operator<<(std::ostream& outstream, const BigInt& number) {
    outstream << number.value();
    return outstream;
}

void BigInt::normalizeToLength(size_t desired_length) const {
    if (desired_length <= this->value_.size()) {
        size_t delete_from =
            std::max(desired_length, this->value_.find_last_not_of(static_cast<char>(0)) + 1);
        if (delete_from >= this->value_.size()) {
            return;
        }
        this->value_.erase(this->value_.begin() + delete_from, this->value_.end());
        return;
    }
    this->value_.append(desired_length - this->value_.size(), static_cast<char>(0));
}

BigInt& BigInt::operator*=(const BigInt& right) {
    if (this->value_.size() < 10 && right.value_.size() < 10) {
        int64_t result = static_cast<int64_t>(std::stoi(this->value())) *
                         static_cast<int64_t>(std::stoi(right.value()));
        this->value_ = std::to_string(result);
        BigInt::stringFormat(this->value_);
        return *this;
    }
    size_t part_size = (std::max(this->value_.size(), right.value_.size()) + 1) / 2;
    this->normalizeToLength(2 * part_size);
    right.normalizeToLength(2 * part_size);
    BigInt b(this->value_.substr(0, part_size), true), a(this->value_.substr(part_size), true);
    BigInt d(right.value_.substr(0, part_size), true), c(right.value_.substr(part_size), true);
    BigInt ac = a, bd = b;
    ac *= c;
    bd *= d;
    a += b;
    c += d;
    ac.normalizeToLength(2 * part_size);
    bd.normalizeToLength(2 * part_size);

    this->value_ = bd.value_ + ac.value_;
    a *= c;
    ac += bd;
    a -= ac;
    this->inplaceSum(a, part_size);

    this->normalizeToLength(1);
    right.normalizeToLength(1);
    return *this;
}

BigInt& BigInt::operator+=(const BigInt& right) {
    this->inplaceSum(right);
    return *this;
}
void BigInt::inplaceSum(const BigInt& right, size_t offset) {
    int extra = 0;
    this->normalizeToLength(std::max(right.value_.size(), this->value_.size()) + 1);
    std::string::iterator this_it = this->value_.begin() + offset;
    for (std::string::const_iterator right_it = right.value_.begin();
         right_it != right.value_.end(); ++right_it, ++this_it) {
        int sum = *this_it + *right_it + extra;
        extra = sum / 10;
        sum %= 10;
        *this_it = sum;
    }
    for (; extra != 0 && this_it != this->value_.end(); ++this_it) {
        int sum = *this_it + extra;
        extra = sum / 10;
        sum %= 10;
        *this_it = sum;
    }
    this->normalizeToLength(1);
}

BigInt& BigInt::operator-=(const BigInt& right) {
    std::string::iterator this_it = this->value_.begin();
    for (std::string::const_iterator right_it = right.value_.begin();
         right_it != right.value_.end(); ++right_it, ++this_it) {
        int result = (*this_it) - (*right_it);
        if (result < 0) {
            result += 10;
            (*(this_it + 1))--;
        }
        *this_it = result;
    }
    for (; this_it != this->value_.end() && *this_it < 0; this_it++) {
        *this_it += 10;
        (*(this_it + 1))--;
    }
    this->normalizeToLength(1);
    return *this;
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    BigInt number1, number2;
    std::cin >> number1 >> number2;
    number1 *= number2;
    std::cout << number1;
    return 0;
}