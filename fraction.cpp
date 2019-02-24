#ifndef _MY_FLOAT_CPP_
#define _MY_FLOAT_CPP_
#include "fraction.h"
#include <cmath>

namespace tnik
{

fraction::fraction() {}

fraction::fraction(long long x, long long y)
            : top(std::abs(x) / gcd(std::abs(x), std::abs(y)))
            , bot(std::abs(y) / gcd(std::abs(x), std::abs(y)))
            , sign(what_sign(x, y)){}

fraction::fraction(const fraction &temp)
{
    top = temp.top;
    bot = temp.bot;
    sign = temp.sign;
}

///////////////////////////////////////////

std::ostream &operator<<(std::ostream &stream, const fraction& obj)
{
    if (obj.top == 0)
    {
        stream << 0;
        return stream;
    }
    if (obj.sign)
        stream << '-';
    if (obj.bot == 1)
    {
        stream << obj.top;
        return stream;
    }
    stream << obj.top << '/' << obj.bot;
    return stream;
}

std::istream &operator>>(std::istream& stream, fraction &obj)
{
    long long x, y;
    stream >> x >> y;
    obj.top = std::abs(x) / gcd(std::abs(x), std::abs(y));
    obj.bot = std::abs(y) / gcd(std::abs(x), std::abs(y));
    obj.sign = what_sign(x, y);
    return stream;
}

///////////////////////////////////////////

void fraction::operator=(const fraction& temp)
{
    top = temp.top;
    bot = temp.bot;
    sign = temp.sign;
}

fraction fraction::operator+(const fraction& s) const
{
    fraction temp(*this);
    fraction sec = s;
    if (temp.bot % sec.bot == 0)
    {
        unsigned long long x = temp.bot / sec.bot;
        sec.bot *= x;
        sec.top *= x;
    }
    else if (sec.bot % temp.bot == 0)
    {
        unsigned long long x = sec.bot / temp.bot;
        temp.bot *= x;
        temp.top *= x;
    }
    else
    {
        unsigned long long temp2 = temp.bot;
        temp.bot *= sec.bot;
        temp.top *= sec.bot;
        sec.bot *= temp2;
        sec.top *= temp2;
    }
    if ((temp.sign && sec.sign) || ((!temp.sign) && (!sec.sign)))
        temp.top += sec.top;
    else if (temp.top >= sec.top)
        temp.top -= sec.top;
    else
    {
        temp.top = sec.top - temp.top;
        temp.sign = sec.sign;
    }
    unsigned long long gcd_for_float = gcd(temp.bot, temp.top);
    temp.top /= gcd_for_float;
    temp.bot /= gcd_for_float;
    return temp;
}

fraction fraction::operator-(const fraction& s) const
{
    fraction sec = s;
    sec.sign ^= 1;
    return *this + sec;
}

fraction fraction::operator*(const fraction& s) const
{
    fraction sec = s;
    fraction temp(*this);
    if ((temp.top == 0) || (sec.top == 0))
        return fraction(0, 1);
    unsigned long long gcd1 = gcd(temp.top, sec.bot);
    unsigned long long gcd2 = gcd(temp.bot, sec.top);
    temp.top /= gcd1;
    sec.bot /= gcd1;
    temp.bot /= gcd2;
    sec.top /= gcd2;
    temp.top *= sec.top;
    temp.bot *= sec.bot;
    temp.sign ^= sec.sign;
    return temp;
}

fraction fraction::operator/(const fraction& s) const
{
    fraction sec = s;
    sec.top ^= sec.bot;
    sec.bot ^= sec.top;
    sec.top ^= sec.bot;
    return *this * sec;
}

///////////////////////////////////////////

fraction fraction::operator++(int)
{
    fraction obj2(*this);
    if (sign == false)
        top += bot;
    else if (top >= bot)
        top -= bot;
    else
    {
        top = bot - top;
        sign = false;
    }
    return obj2;
}

fraction& operator++(fraction &obj)
{
    if (obj.sign == false)
        obj.top += obj.bot;
    else if (obj.top >= obj.bot)
        obj.top -= obj.bot;
    else
    {
        obj.top = obj.bot - obj.top;
        obj.sign = false;
    }
    return obj;
}

///////////////////////////////////////////

fraction fraction::operator--(int)
{
    fraction obj2(*this);
    if (sign == true)
        top += bot;
    else if (top >= bot)
        top -= bot;
    else
    {
        top = bot - top;
        sign = true;
    }
    return obj2;
}

fraction& operator--(fraction &obj)
{
    if (obj.sign == true)
        obj.top += obj.bot;
    else if (obj.top >= obj.bot)
        obj.top -= obj.bot;
    else
    {
        obj.top = obj.bot - obj.top;
        obj.sign = true;
    }
    return obj;
}

///////////////////////////////////////////

fraction& fraction::operator+=(const fraction& obj)
{
    *this = *this + obj;
    return *this;
}

fraction& fraction::operator-=(const fraction& obj)
{
    *this = *this - obj;
    return *this;
}

fraction& fraction::operator*=(const fraction& obj)
{
    *this = *this * obj;
    return *this;
}

fraction& fraction::operator/=(const fraction& obj)
{
    *this = *this / obj;
    return *this;
}

///////////////////////////////////////////

void fraction::swap(fraction &sec)
{
    sec.top ^= this->top;
    this->top ^= sec.top;
    sec.top ^= this->top;

    sec.bot ^= this->bot;
    this->bot ^= sec.bot;
    sec.bot ^= this->bot;

    sec.sign ^= this->sign;
    this->sign ^= sec.sign;
    sec.sign ^= this->sign;
}

///////////////////////////////////////////

fraction::operator long double() const
{
    if (sign)
        return -1.0L * ((long double) top) / ((long double)bot);
    return ((long double) top) / ((long double)bot);
}

///////////////////////////////////////////

bool fraction::operator==(const fraction& sec) const
{
	if (this->sign == sec.sign && this->top == sec.top && this->bot == sec.bot)
		return true;
	else
		return false;
}

bool fraction::operator<(const fraction& sec) const
{
	if (this->sign != 0 ^ sec.sign != 0)
	{
		return this->sign > sec.sign;
	}
	else
	{
		unsigned long long left = this->top/gcd(this->top, sec.top);
		left *= sec.bot/gcd(this->bot, sec.bot);

		unsigned long long right = this->bot/gcd(this->bot, sec.bot);
		left *= sec.top/gcd(this->top, sec.top);

		if (this->sign)
			return left > right;
		else
			return left < right;
	}
}

bool fraction::operator<=(const fraction& sec) const
{
	return (*this < sec) || (*this == sec);
}

bool fraction::operator>(const fraction& sec) const
{
	return sec < *this;
}

bool fraction::operator>=(const fraction& sec) const
{
	return sec <= *this;
}

///////////////////////////////////////////

bool what_sign(long long x, long long y)
{
    if ((x == 0) || ((x > 0) && (y > 0)) || ((x < 0) && (y < 0)))
        return false;
    else
        return true;
}

unsigned long long gcd(unsigned long long a, unsigned long long b)
{
    unsigned long long nod = 1;
    unsigned long long tmp;
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    if (a == b)
        return a;
    if (a == 1 || b == 1)
        return 1;
    while (a != 0 && b != 0)
    {
        if (((a & 1) | (b & 1)) == 0)
        {
            nod <<= 1;
            a >>= 1;
            b >>= 1;
            continue;
        }
        if (((a & 1) == 0) && (b & 1))
        {
            a >>= 1LL;
            continue;
        }
        if ((a & 1) && ((b & 1) == 0))
        {
            b >>= 1;
            continue;
        }
        if (a > b)
        {
            tmp = a;
            a = b;
            b = tmp;
        }
        tmp = a;
        a = (b - a) >> 1;
        b = tmp;
    }
    if (a == 0)
        return nod * b;
    else
        return nod * a;
}

unsigned long long pow(unsigned long long x, unsigned long long y)
{
    unsigned long long res = 1;
    for (int i = 0; i < y; ++i)
        res *= x;
    return res;
}
}
#endif
