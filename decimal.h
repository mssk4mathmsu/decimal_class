#ifndef DECIMAL_H
#define DECIMAL_H

#include <iostream>

class Decimal {
private:
    int* digits;
    int size;
    bool negative;
    static int scale;

    void removeLeadingZeros();
    int compareAbsolute(const Decimal& other) const;

public:
    Decimal();
    Decimal(const Decimal& other);
    Decimal(int value);
    Decimal(double value);
    ~Decimal();

    Decimal& operator=(const Decimal& other);

    Decimal operator+(const Decimal& other) const;
    Decimal& operator+=(const Decimal& other);

    Decimal operator-(const Decimal& other) const;
    Decimal& operator-=(const Decimal& other);

    Decimal operator*(const Decimal& other) const;
    Decimal& operator*=(const Decimal& other);

    Decimal operator/(const Decimal& other) const;
    Decimal& operator/=(const Decimal& other);

    bool operator==(const Decimal& other) const;
    bool operator!=(const Decimal& other) const;
    bool operator<(const Decimal& other) const;
    bool operator<=(const Decimal& other) const;
    bool operator>(const Decimal& other) const;
    bool operator>=(const Decimal& other) const;

    int& operator[](int index);
    const int& operator[](int index) const;

    int& operator()(int index);
    const int& operator()(int index) const;

    friend std::ostream& operator<<(std::ostream& out, const Decimal& value);
};

#endif
