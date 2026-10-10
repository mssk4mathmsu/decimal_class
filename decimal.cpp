#include "decimal.h"

#include <stdexcept>

int Decimal::scale = 2;


Decimal::Decimal() {
    size = scale + 1;
    negative = false;

    digits = new int[size];

    for (int i = 0; i < size; ++i) {
        digits[i] = 0;
    }
}


Decimal::Decimal(const Decimal& other) {
    size = other.size;
    negative = other.negative;

    digits = new int[size];

    for (int i = 0; i < size; ++i) {
        digits[i] = other.digits[i];
    }
}


Decimal::Decimal(int value) {
    long long tempValue = value;

    negative = (tempValue < 0);

    if (tempValue < 0) {
        tempValue = -tempValue;
    }

    for (int i = 0; i < scale; ++i) {
        tempValue *= 10;
    }

    long long temp = tempValue;
    int digitCount = 1;

    while (temp >= 10) {
        temp /= 10;
        ++digitCount;
    }

    size = digitCount;

    if (size < scale + 1) {
        size = scale + 1;
    }

    digits = new int[size];

    for (int i = size - 1; i >= 0; --i) {
        digits[i] = tempValue % 10;
        tempValue /= 10;
    }

    removeLeadingZeros();
}


Decimal::Decimal(double value) {
    negative = (value < 0);

    if (value < 0) {
        value = -value;
    }

    long long multiplier = 1;

    for (int i = 0; i < scale; ++i) {
        multiplier *= 10;
    }

    long long integerValue = (long long)(value * multiplier + 0.5);

    long long temp = integerValue;
    int digitCount = 1;

    while (temp >= 10) {
        temp /= 10;
        ++digitCount;
    }

    size = digitCount;

    if (size < scale + 1) {
        size = scale + 1;
    }

    digits = new int[size];

    for (int i = size - 1; i >= 0; --i) {
        digits[i] = integerValue % 10;
        integerValue /= 10;
    }

    removeLeadingZeros();
}


Decimal::~Decimal() {
    delete[] digits;
}


Decimal& Decimal::operator=(const Decimal& other) {
    if (this != &other) {
        delete[] digits;

        size = other.size;
        negative = other.negative;

        digits = new int[size];

        for (int i = 0; i < size; ++i) {
            digits[i] = other.digits[i];
        }
    }

    return *this;
}


void Decimal::removeLeadingZeros() {
    int firstNonZero = 0;

    while (firstNonZero < size - (scale + 1) && digits[firstNonZero] == 0) {
        ++firstNonZero;
    }

    if (firstNonZero > 0) {
        int newSize = size - firstNonZero;
        int* newDigits = new int[newSize];

        for (int i = 0; i < newSize; ++i) {
            newDigits[i] = digits[i + firstNonZero];
        }

        delete[] digits;
        digits = newDigits;
        size = newSize;
    }

    bool allZero = true;

    for (int i = 0; i < size; ++i) {
        if (digits[i] != 0) {
            allZero = false;
            break;
        }
    }

    if (allZero) {
        negative = false;
    }
}


int Decimal::compareAbsolute(const Decimal& other) const {
    if (size > other.size) {
        return 1;
    }

    if (size < other.size) {
        return -1;
    }

    for (int i = 0; i < size; ++i) {
        if (digits[i] > other.digits[i]) {
            return 1;
        }

        if (digits[i] < other.digits[i]) {
            return -1;
        }
    }

    return 0;
}


Decimal Decimal::operator+(const Decimal& other) const {
    if (negative != other.negative) {
        Decimal temp(other);
        temp.negative = !temp.negative;

        return *this - temp;
    }

    Decimal result;
    delete[] result.digits;

    result.size = (size > other.size ? size : other.size) + 1;
    result.digits = new int[result.size];
    result.negative = negative;

    for (int i = 0; i < result.size; ++i) {
        result.digits[i] = 0;
    }

    int i = size - 1;
    int j = other.size - 1;
    int carry = 0;

    for (int k = result.size - 1; k >= 0; --k) {
        int d1 = (i >= 0 ? digits[i] : 0);
        int d2 = (j >= 0 ? other.digits[j] : 0);

        int sum = d1 + d2 + carry;

        result.digits[k] = sum % 10;
        carry = sum / 10;

        --i;
        --j;
    }

    result.removeLeadingZeros();

    return result;
}


Decimal& Decimal::operator+=(const Decimal& other) {
    *this = *this + other;
    return *this;
}


Decimal Decimal::operator-(const Decimal& other) const {
    if (negative != other.negative) {
        Decimal temp(other);
        temp.negative = negative;

        return *this + temp;
    }

    int cmp = compareAbsolute(other);

    if (cmp == 0) {
        return Decimal(0);
    }

    const Decimal* bigger = this;
    const Decimal* smaller = &other;
    bool resultNegative = negative;

    if (cmp < 0) {
        bigger = &other;
        smaller = this;
        resultNegative = !negative;
    }

    Decimal result;
    delete[] result.digits;

    result.size = bigger->size;
    result.digits = new int[result.size];
    result.negative = resultNegative;

    for (int i = 0; i < result.size; ++i) {
        result.digits[i] = 0;
    }

    int i = bigger->size - 1;
    int j = smaller->size - 1;
    int borrow = 0;

    for (int k = result.size - 1; k >= 0; --k) {
        int d1 = bigger->digits[i] - borrow;
        int d2 = (j >= 0 ? smaller->digits[j] : 0);

        if (d1 < d2) {
            d1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.digits[k] = d1 - d2;

        --i;
        --j;
    }

    result.removeLeadingZeros();

    return result;
}


Decimal& Decimal::operator-=(const Decimal& other) {
    *this = *this - other;
    return *this;
}


Decimal Decimal::operator*(const Decimal& other) const {
    Decimal result;
    delete[] result.digits;

    result.size = size + other.size;
    result.digits = new int[result.size];
    result.negative = (negative != other.negative);

    for (int i = 0; i < result.size; ++i) {
        result.digits[i] = 0;
    }

    for (int i = size - 1; i >= 0; --i) {
        for (int j = other.size - 1; j >= 0; --j) {
            result.digits[i + j + 1] += digits[i] * other.digits[j];
        }
    }

    for (int i = result.size - 1; i > 0; --i) {
        result.digits[i - 1] += result.digits[i] / 10;
        result.digits[i] %= 10;
    }

    int newSize = result.size - scale;
    int* newDigits = new int[newSize];

    for (int i = 0; i < newSize; ++i) {
        newDigits[i] = result.digits[i];
    }

    delete[] result.digits;
    result.digits = newDigits;
    result.size = newSize;

    result.removeLeadingZeros();

    return result;
}


Decimal& Decimal::operator*=(const Decimal& other) {
    *this = *this * other;
    return *this;
}


Decimal Decimal::operator/(const Decimal& other) const {
    bool zero = true;
    for (int i = 0; i < other.size; ++i) {
        if (other.digits[i] != 0) {
            zero = false;
            break;
        }
    }

    if (zero) {
        throw std::runtime_error("Division by zero");
    }

    int dividendSize = size + scale;
    int* dividend = new int[dividendSize];

    for (int i = 0; i < size; ++i) {
        dividend[i] = digits[i];
    }
    for (int i = size; i < dividendSize; ++i) {
        dividend[i] = 0;
    }

    int* quotient = new int[dividendSize];
    for (int i = 0; i < dividendSize; ++i) {
        quotient[i] = 0;
    }

    int remainderSize = 1;
    int* remainder = new int[1];
    remainder[0] = 0;

    for (int pos = 0; pos < dividendSize; ++pos) {
        int* newRemainder = new int[remainderSize + 1];
        for (int i = 0; i < remainderSize; ++i) {
            newRemainder[i] = remainder[i];
        }
        newRemainder[remainderSize] = dividend[pos];

        delete[] remainder;
        remainder = newRemainder;
        ++remainderSize;

        int firstNonZero = 0;
        while (firstNonZero < remainderSize - 1 && remainder[firstNonZero] == 0) {
            ++firstNonZero;
        }

        if (firstNonZero > 0) {
            int newSize = remainderSize - firstNonZero;
            int* normalized = new int[newSize];
            for (int i = 0; i < newSize; ++i) {
                normalized[i] = remainder[i + firstNonZero];
            }
            delete[] remainder;
            remainder = normalized;
            remainderSize = newSize;
        }

        int qDigit = 0;

        while (qDigit < 10) {
            int cmp = 0;

            if (remainderSize > other.size) {
                cmp = 1;
            } else if (remainderSize < other.size) {
                cmp = -1;
            } else {
                for (int i = 0; i < remainderSize; ++i) {
                    if (remainder[i] > other.digits[i]) {
                        cmp = 1;
                        break;
                    }
                    if (remainder[i] < other.digits[i]) {
                        cmp = -1;
                        break;
                    }
                }
            }

            if (cmp < 0) {
                break;
            }

            int borrow = 0;
            int i = remainderSize - 1;
            int j = other.size - 1;

            while (i >= 0) {
                int sub = borrow;
                if (j >= 0) {
                    sub += other.digits[j];
                }

                if (remainder[i] < sub) {
                    remainder[i] += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }

                remainder[i] -= sub;
                --i;
                --j;
            }

            int first = 0;
            while (first < remainderSize - 1 && remainder[first] == 0) {
                ++first;
            }

            if (first > 0) {
                int newSize = remainderSize - first;
                int* normalized = new int[newSize];
                for (int k = 0; k < newSize; ++k) {
                    normalized[k] = remainder[k + first];
                }
                delete[] remainder;
                remainder = normalized;
                remainderSize = newSize;
            }

            ++qDigit;
        }

        quotient[pos] = qDigit;
    }

    delete[] dividend;
    delete[] remainder;

    Decimal result;
    delete[] result.digits;

    result.digits = quotient;
    result.size = dividendSize;
    result.negative = (negative != other.negative);

    result.removeLeadingZeros();

    bool allZero = true;
    for (int i = 0; i < result.size; ++i) {
        if (result.digits[i] != 0) {
            allZero = false;
            break;
        }
    }
    if (allZero) {
        result.negative = false;
    }

    return result;
}



Decimal& Decimal::operator/=(const Decimal& other) {
    *this = *this / other;
    return *this;
}


bool Decimal::operator==(const Decimal& other) const {
    if (negative != other.negative || size != other.size) {
        return false;
    }

    for (int i = 0; i < size; ++i) {
        if (digits[i] != other.digits[i]) {
            return false;
        }
    }

    return true;
}


bool Decimal::operator!=(const Decimal& other) const {
    return !(*this == other);
}


bool Decimal::operator<(const Decimal& other) const {
    if (negative != other.negative) {
        return negative;
    }

    int cmp = compareAbsolute(other);

    if (negative) {
        return cmp > 0;
    }

    return cmp < 0;
}


bool Decimal::operator<=(const Decimal& other) const {
    return *this < other || *this == other;
}


bool Decimal::operator>(const Decimal& other) const {
    return !(*this <= other);
}


bool Decimal::operator>=(const Decimal& other) const {
    return !(*this < other);
}


int& Decimal::operator[](int index) {
    return digits[index];
}


const int& Decimal::operator[](int index) const {
    return digits[index];
}


int& Decimal::operator()(int index) {
    return digits[size - 1 - index];
}


const int& Decimal::operator()(int index) const {
    return digits[size - 1 - index];
}


std::ostream& operator<<(std::ostream& out, const Decimal& value) {
    if (value.negative) {
        out << '-';
    }

    int integerPartSize = value.size - Decimal::scale;

    if (integerPartSize <= 0) {
        out << "0.";

        for (int i = 0; i < -integerPartSize; ++i) {
            out << '0';
        }

        for (int i = 0; i < value.size; ++i) {
            out << value.digits[i];
        }

        return out;
    }

    for (int i = 0; i < value.size; ++i) {
        if (i == integerPartSize && Decimal::scale > 0) {
            out << '.';
        }

        out << value.digits[i];
    }

    return out;
}
