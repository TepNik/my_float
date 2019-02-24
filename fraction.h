#ifndef _MY_FLOAT_H_
#define _MY_FLOAT_H_
#include <iostream>

namespace tnik
{
class fraction
{
  private:
    bool sign; // 0 - is positive, 1 - negative
    unsigned long long top, bot;
  	void swap(fraction&);

  public:
    fraction();
    fraction(long long, long long);
    template<typename T, typename
                std::enable_if<
                    std::is_arithmetic<T>::value,
                    T
                >::type *n = nullptr
            >
    fraction(T);
    fraction(const fraction&);

    friend std::ostream& operator<<(std::ostream&, const fraction&);
    friend std::istream& operator>>(std::istream&, fraction&);

    void operator=(const fraction&);
    fraction operator+(const fraction&) const;
    fraction operator-(const fraction&) const;
    fraction operator*(const fraction&) const;
    fraction operator/(const fraction&) const;

    fraction operator++(int);
    friend fraction& operator++(fraction &obj);
    fraction operator--(int);
    friend fraction& operator--(fraction &obj);

    fraction& operator+=(const fraction&);
    fraction& operator-=(const fraction&);
    fraction& operator*=(const fraction&);
    fraction& operator/=(const fraction&);

    explicit operator long double() const;

  	bool operator==(const fraction&) const;
  	bool operator<(const fraction&) const;
  	bool operator<=(const fraction&) const;
  	bool operator>(const fraction&) const;
  	bool operator>=(const fraction&) const;
};

bool what_sign(const long long x, const long long y);

unsigned long long gcd(const unsigned long long a, const unsigned long long b);

unsigned long long pow(const unsigned long long x, const unsigned long long y);

template<typename T, typename
                std::enable_if<
                    std::is_arithmetic<T>::value,
                    T
                >::type *n
            >
fraction::fraction(T input)
{
    if (input < 0)
        sign = true;
    else
        sign = false;
    unsigned long long down = 1ULL;
    input = std::abs(input);
    while ((unsigned long long) input != input)
    {
        input *= 10;
        down *= 10;
    }
    top = input;
    bot = down;
    long long gcd_for_float = gcd(top, bot);
    top /= gcd_for_float;
    bot /= gcd_for_float;
}
}

#endif
