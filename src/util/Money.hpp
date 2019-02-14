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

struct Money {

   Money(void);

   explicit Money(std::string const& value);

   Money(Money const& other);

   std::string to_string(void) const;

   Money& operator=(Money other);

   bool operator==(Money const& other) const;

   Money& operator+=(Money const& other);

   Money& operator-=(Money const& other);

   //Money& operator %= (Money const& other);
   //Money& operator /= (Money const& other);

   Money& operator*=(int64_t other);

   Money& operator%=(int64_t other);
   Money& operator/=(int64_t other);

   friend void swap(Money& first, Money& second);

private:
   int64_t m_value;
}; // struct Money

} // namespace util

#endif // COCLES_UTIL_MONEY_HPP
