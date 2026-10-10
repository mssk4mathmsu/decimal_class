#include <iostream>
#include <stdexcept>
#include "decimal.h"

using std::cout;
using std::endl;

void printTitle(const char* title) {
    cout << "\n===== " << title << " =====\n";
}

void printComparison(const Decimal& a, const Decimal& b, const char* nameA, const char* nameB) {
    cout << nameA << " = " << a << endl;
    cout << nameB << " = " << b << endl;

    cout << nameA << " == " << nameB << " : " << (a == b) << endl;
    cout << nameA << " != " << nameB << " : " << (a != b) << endl;
    cout << nameA << " <  " << nameB << " : " << (a < b) << endl;
    cout << nameA << " <= " << nameB << " : " << (a <= b) << endl;
    cout << nameA << " >  " << nameB << " : " << (a > b) << endl;
    cout << nameA << " >= " << nameB << " : " << (a >= b) << endl;
}

int main() {
    printTitle("Constructors");

    Decimal a;
    Decimal b(123);
    Decimal c(-45);
    Decimal d(12.34);
    Decimal e(-7.89);
    Decimal f(0);

    cout << "a (default) = " << a << endl;
    cout << "b (int 123) = " << b << endl;
    cout << "c (int -45) = " << c << endl;
    cout << "d (double 12.34) = " << d << endl;
    cout << "e (double -7.89) = " << e << endl;
    cout << "f (zero) = " << f << endl;

    printTitle("Copy constructor");

    Decimal g(b);
    Decimal h(e);

    cout << "g(copy of b) = " << g << endl;
    cout << "h(copy of e) = " << h << endl;

    printTitle("Assignment operator");

    Decimal x;
    Decimal y;

    x = d;
    y = c;

    cout << "x = d -> " << x << endl;
    cout << "y = c -> " << y << endl;

    printTitle("Addition");

    cout << "b + d = " << (b + d) << endl;
    cout << "d + e = " << (d + e) << endl;
    cout << "c + e = " << (c + e) << endl;

    Decimal addTest(10);
    addTest += Decimal(2.50);
    cout << "10 += 2.50 -> " << addTest << endl;

    printTitle("Subtraction");

    cout << "b - d = " << (b - d) << endl;
    cout << "d - b = " << (d - b) << endl;
    cout << "c - e = " << (c - e) << endl;
    cout << "e - c = " << (e - c) << endl;

    Decimal subTest(20);
    subTest -= Decimal(3.75);
    cout << "20 -= 3.75 -> " << subTest << endl;

    printTitle("Multiplication");

    cout << "b * d = " << (b * d) << endl;
    cout << "d * e = " << (d * e) << endl;
    cout << "c * Decimal(-2) = " << (c * Decimal(-2)) << endl;
    cout << "d * Decimal(0) = " << (d * Decimal(0)) << endl;

    Decimal mulTest(5);
    mulTest *= Decimal(2.00);
    cout << "5 *= 2.00 -> " << mulTest << endl;

    printTitle("Division");

    cout << "b / Decimal(2) = " << (b / Decimal(2)) << endl;
    cout << "d / Decimal(2) = " << (d / Decimal(2)) << endl;
    cout << "Decimal(10) / Decimal(4) = " << (Decimal(10) / Decimal(4)) << endl;
    cout << "e / Decimal(2) = " << (e / Decimal(2)) << endl;

    Decimal divTest(25);
    divTest /= Decimal(5);
    cout << "25 /= 5 -> " << divTest << endl;

    printTitle("Comparisons");

    printComparison(Decimal(10), Decimal(10), "10", "10");
    printComparison(Decimal(10), Decimal(5), "10", "5");
    printComparison(Decimal(-3), Decimal(2), "-3", "2");
    printComparison(Decimal(-7), Decimal(-2), "-7", "-2");

    printTitle("Index operators");

    Decimal idx(12.34);
    cout << "idx = " << idx << endl;

    cout << "digits through operator[]: ";
    for (int i = 0; i < 4; ++i) {
        cout << idx[i] << ' ';
    }
    cout << endl;

    cout << "digits through operator(): ";
    for (int i = 0; i < 4; ++i) {
        cout << idx(i) << ' ';
    }
    cout << endl;

    printTitle("Changing digits manually");

    Decimal manual(12.34);
    cout << "before: " << manual << endl;

    manual[0] = 9;
    cout << "after manual[0] = 9 -> " << manual << endl;

    manual(1) = 8;
    cout << "after manual(1) = 8 -> " << manual << endl;

    printTitle("Division by zero");

    try {
        Decimal bad = b / Decimal(0);
        cout << bad << endl;
    } catch (const std::runtime_error& ex) {
        cout << "Caught exception: " << ex.what() << endl;
    }

    printTitle("Chain expressions");

    Decimal p(10.50);
    Decimal q(2.00);
    Decimal r(3.00);

    Decimal result1 = (p + q) * r;
    Decimal result2 = (p - q) / Decimal(2);
    Decimal result3 = (p * q) - r;

    cout << "(10.50 + 2.00) * 3.00 = " << result1 << endl;
    cout << "(10.50 - 2.00) / 2.00 = " << result2 << endl;
    cout << "(10.50 * 2.00) - 3.00 = " << result3 << endl;

    printTitle("End");

    return 0;
}
