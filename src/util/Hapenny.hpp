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

#ifndef COCLES_UTIL_HAPENNY_HPP
#define COCLES_UTIL_HAPENNY_HPP

///////////////////////////////////////////////////////////////////////////////
// Defines class to represent money to half a cent
//
// Only represent up to 5,000,000,000,000,000.00
//
// Use cases:
// - Sum up amounts from each adjustment for a specific account
// - Convert to a string for display
///////////////////////////////////////////////////////////////////////////////

#include <string>

namespace util {

struct Hapenny {

   Hapenny();

   explicit Hapenny(std::string const& value);

   explicit Hapenny(int64_t value) : m_value(value) { }

   [[nodiscard]] std::string to_string() const;

   bool operator==(Hapenny const& other) const;

   Hapenny& operator+=(Hapenny const& other);

   Hapenny& operator-=(Hapenny const& other);

   //Hapenny& operator %= (Hapenny const& other);
   //Hapenny& operator /= (Hapenny const& other);

   Hapenny& operator*=(int64_t other);

   Hapenny& operator%=(int64_t other);
   Hapenny& operator/=(int64_t other);

   friend void swap(Hapenny& first, Hapenny& second);

private:
   int64_t m_value{0};
}; // struct Hapenny

Hapenny operator+(Hapenny a, Hapenny const& b);

std::ostream& operator<<(std::ostream& s, Hapenny const& m);

} // namespace util

#endif // COCLES_UTIL_HAPENNY_HPP
