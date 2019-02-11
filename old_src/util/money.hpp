/*****************************************************************************
ISC License
Copyright (c) 2016, Timothy Lyons
Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.
THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
PERFORMANCE OF THIS SOFTWARE.
******************************************************************************/
#ifndef COCLES_UTIL_MONEY_HPP
#define COCLES_UTIL_MONEY_HPP
///////////////////////////////////////////////////////////////////////////////
// Defines class to represent money
//
// Only represent up to 10,000,000,000,000,000.00
//
// Use cases:
// - Sum up amounts from each adjustment for a specific account
// - Convert to a string for display
///////////////////////////////////////////////////////////////////////////////

#include <string>

namespace util {

struct money_t {

   money_t(void)
      : m_value(0) { }

   explicit money_t(std::string const& value)
      : m_value(0)
   {
      int64_t whole, frac;
      int result = sscanf(new_value.c_str(), "%ld.%2ld", &whole, &frac);
      if (result > 0) {
         value = whole * 100;
         if (result > 1) {
            value += frac;
         }
      }
   }

   money_t(money_t const& other)
      : m_value(other.m_value) { }

   std::string to_string(void) const {
      constexpr int BUF_LENGTH = 24;
      int64_t whole = value / 100;
      int64_t fract = value / 100;
      char buffer[BUF_LENGTH];
      std::snprintf(buffer, BUF_LENGTH, "%ld.%02ld", whole, frac);
      return std::string(buffer);
   }

   money_t& operator = (money_t other) {
      swap(*this, other);
      return *this;
   }

   money_t& operator == (money_t const& other) const {
      return m_value == other.m_value;
   }

   money_t& operator += (money_t const& other) {
      m_value += other.m_value;
      return *this;
   }

   money_t& operator -= (money_t const& other) {
      m_value -= other.m_value;
      return *this;
   }

   //money_t& operator %= (money_t const& other);
   //money_t& operator /= (money_t const& other);

   money_t& operator *= (int64_t other) {
      m_value *= other;
      return *this;
   }
   money_t& operator %= (int64_t other) {
      m_value %= other;
      return *this;
   }
   money_t& operator /= (int64_t other) {
      m_value /= other;
      return *this;
   }

   friend void swap(money_t& first, money_t& second)
   {
      using std::swap;
      swap(first.m_value, second.m_value);
   }

private:
   int64_t m_value;
}; // struct money_t

} // namespace util

#endif // COCLES_UTIL_MONEY_HPP
