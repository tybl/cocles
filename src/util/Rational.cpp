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

#include "Rational.hpp"

#include <iostream>
#include <limits>

namespace util {

#if 0
namespace {
   constexpr long long gcd(long long p, long long q) {
      return q ? gcd(q, (p % q)) : p;
   }
}

constexpr Rational::Rational(unsigned long long p, unsigned long long q)
   : Rational{static_cast<long long>(p), static_cast<long long>(q)}
{
   // Retrospectively justify static_cast<> above
   constexpr unsigned long long max_ll = std::numeric_limits<long long>::max();
   if (p > max_ll || q > max_ll) {
      throw std::domain_error{"value out of range"};
   }
}

constexpr Rational::Rational(const Rational& rat)
   : Rational{rat.m_numerator, rat.m_denominator} { }

constexpr Rational& Rational::simplify() {
   // Fix negative denominators
   if (m_denominator < 0) {
       m_numerator = -m_numerator;
       m_denominator = -m_denominator;
   }

   // Reduce by greatest common divisor
   const auto denom = gcd(m_numerator, m_denominator);
   m_numerator /= denom;
   m_denominator /= denom;

   return *this;
}

constexpr Rational& Rational::operator=(const Rational& rat) = default;

constexpr Rational& Rational::operator+=(const Rational& rat) {
   m_numerator = m_numerator * rat.m_denominator + m_denominator * rat.m_numerator;
   m_denominator *= rat.m_denominator;
   return simplify();
}

constexpr Rational& Rational::operator-=(const Rational& rat) {
   m_numerator = m_numerator * rat.m_denominator - m_denominator * rat.m_numerator;
   m_denominator *= rat.m_denominator;
   return simplify();
}

constexpr Rational& Rational::operator*=(const Rational& rat) {
    m_numerator *= rat.m_numerator;
    m_denominator *= rat.m_denominator;
    return simplify();
}

constexpr Rational& Rational::operator/=(const Rational& rat) {
   if (rat.m_numerator == 0) {
      throw std::domain_error{"Division by zero not allowed"};
   }
   return *this *= rat.inverse();
}

constexpr Rational Rational::operator+(const Rational& rat) const {
   return Rational{*this} += rat;
}

constexpr Rational Rational::operator-(const Rational& rat) const {
   return Rational{*this} -= rat;
}

constexpr Rational Rational::operator*(const Rational& rat) const {
   Rational result(*this);

   result *= rat;
   result.simplify();

   return result;
}

constexpr Rational Rational::operator/(const Rational& rat) const {
   Rational result(*this);

   result /= rat;
   result.simplify();

   return result;
}

constexpr Rational Rational::operator-() const {
   return 0 - *this;
}

constexpr Rational Rational::operator+() const {
   return *this;
}


constexpr bool Rational::operator==(const Rational& rat) const {
   return m_numerator == rat.m_numerator && m_denominator == rat.m_denominator;
}

constexpr bool Rational::operator<(const Rational& rat) const {
   return m_numerator * rat.m_denominator  <  m_denominator * rat.m_numerator;
}


constexpr Rational Rational::operator++(int) { // Postfix
   Rational temp{*this};
   m_numerator += m_denominator;
   return temp;
}

constexpr Rational Rational::operator--(int) { // Postfix
   Rational temp{*this};
   m_numerator -= m_denominator;
   return temp;
}

constexpr Rational& Rational::operator++() {
   return *this += 1;
}

constexpr Rational& Rational::operator--() {
   return *this -= 1;
}

constexpr Rational::operator double() {
   return static_cast<double>(m_numerator) / m_denominator;
}


std::ostream& operator<<(std::ostream& os, const Rational& rat) {
   return os << rat.m_numerator << ":" << rat.m_denominator;
}

std::istream& operator>>(std::istream& is, Rational& rat) {
   long long p, q;
   char sep;
   if (is >> p >> sep >> q && sep == ':') {
      rat = {p, q};
   }
   return is;
}

constexpr Rational Rational::pow(unsigned exp) const {
   auto x = *this;
   Rational r{1};
   for (;  exp;  exp /= 2) {
      if (exp%2) {
         r *= x;
      }
      x *= x;
   }
   return r;
}

constexpr Rational Rational::inverse() const {
   return {m_denominator, m_numerator};
}

#endif
} // namespace util
