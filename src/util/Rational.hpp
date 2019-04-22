/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* ISC License
*
* Copyright (c) 2019, Timothy Lyons
*
* Permission to use, copy, modify, and/or distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
* REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
* AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
* INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
* LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
* OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
* PERFORMANCE OF THIS SOFTWARE.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef COCLES_UTIL_RATIONAL_HPP
#define COCLES_UTIL_RATIONAL_HPP

#include <iosfwd>
#include <stdexcept>

namespace util {

struct Rational {
   long long m_numerator;
   long long m_denominator;

   constexpr Rational& simplify();

public:
   template<typename T> constexpr Rational(T p, T q = 1);
   constexpr Rational(unsigned long long p = 0, unsigned long long q = 1);
   constexpr Rational(const Rational&);

   // assignment operators
   constexpr Rational& operator=(const Rational&);
   constexpr Rational& operator+=(const Rational&);
   constexpr Rational& operator-=(const Rational&);
   constexpr Rational& operator*=(const Rational&);
   constexpr Rational& operator/=(const Rational&);

   // arithmetic operators
   constexpr Rational operator+(const Rational&) const;
   constexpr Rational operator-(const Rational&) const;
   constexpr Rational operator*(const Rational&) const;
   constexpr Rational operator/(const Rational&) const;
   constexpr Rational operator-() const;
   constexpr Rational operator+() const;

   // comparison operators
   constexpr bool operator==(const Rational&) const;
   constexpr bool operator<(const Rational&) const;

   // increment and decrement operators
   constexpr Rational operator++(int);
   constexpr Rational operator--(int);
   constexpr Rational& operator++();
   constexpr Rational& operator--();

   // type conversion
   constexpr explicit operator double();

   // stream operators
   friend std::ostream& operator<<(std::ostream&, const Rational&);
   friend std::istream& operator>>(std::istream&, Rational&);

   // arithmetic functions
   constexpr Rational pow(unsigned exp) const;
   constexpr Rational inverse() const;
};


template<typename T>
constexpr Rational::Rational(T p, T q)
   : m_numerator{p}
   , m_denominator{q}
{
   if (m_denominator == 0) {
      throw std::domain_error{"zero Denominator"};
   }
   simplify();
}

template<typename T>
constexpr Rational operator+(T a, Rational b) {
   return Rational{a} + b;
}

template<typename T>
constexpr Rational operator-(T a, Rational b) {
   return Rational{a} - b;
}

template<typename T>
constexpr Rational operator*(T a, Rational b) {
   return Rational{a} * b;
}

template<typename T>
constexpr Rational operator/(T a, Rational b) {
   return Rational{a} / b;
}

template<typename T>
constexpr bool operator==(T a, Rational b) {
   return Rational{a} == b;
}

template<typename T>
constexpr bool operator<(T a, Rational b) {
   return Rational{a} < b;
}

} // namespace util

#endif // COCLES_UTIL_RATIONAL_HPP
