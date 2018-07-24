#pragma once
#include <iostream>

class myfloat
{
  private:
    bool sign; // 0 - is positive, 1 - negative
    unsigned long long top, bot;

  public:
    myfloat();
    myfloat(long long, long long);
    myfloat(long double);
    //myfloat(double) = delete;
    //myfloat(float) = delete;
    myfloat(const myfloat &);

    friend std::ostream& operator<<(std::ostream&, const myfloat&);
    friend std::istream& operator>>(std::istream&, myfloat&);

    void operator=(const myfloat&);
    myfloat operator+(const myfloat&) const;
    myfloat operator-(const myfloat&) const;
    myfloat operator*(const myfloat&) const;
    myfloat operator/(const myfloat&) const;

    myfloat operator++(int);
    friend myfloat& operator++(myfloat &obj);
    myfloat operator--(int);
    friend myfloat& operator--(myfloat &obj);

    myfloat& operator+=(long double);
    myfloat& operator+=(const myfloat&);
    friend long double& operator+=(long double&, const myfloat&);

    myfloat& operator-=(long double);
    myfloat& operator-=(const myfloat&);
    friend long double& operator-=(long double&, const myfloat&);

    myfloat& operator*=(long double);
    myfloat& operator*=(const myfloat&);
    friend long double& operator*=(long double&, const myfloat&);

    myfloat& operator/=(long double);
    myfloat& operator/=(const myfloat&);
    friend long double& operator/=(long double&, const myfloat&);

    operator long double() const;
    //operator int();

    void swap(myfloat&);
};

bool what_sign(const long long x, const long long y);

unsigned long long gcd(const unsigned long long a, const unsigned long long b);

unsigned long long pow(const unsigned long long x, const unsigned long long y);
