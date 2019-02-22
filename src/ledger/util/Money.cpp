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

#include "Money.hpp"

#include <iomanip>
#include <sstream>

namespace util {

Money::Money()
   : m_value(0) {}

Money::Money(std::string const& new_value)
   : m_value(0) {
   auto temp = 0.0L;
   std::istringstream value_stream(new_value, std::ios_base::in);
   value_stream >> std::get_money(temp, false);
   m_value = static_cast<int64_t>(temp);
}

std::string Money::to_string() const {
   std::ostringstream value_stream(std::ios_base::out);
   value_stream << std::put_money(m_value, false);
   return value_stream.str();
}

bool Money::operator==(Money const& other) const {
   return m_value == other.m_value;
}

Money& Money::operator+=(Money const& other) {
   m_value += other.m_value;
   return *this;
}

Money& Money::operator-=(Money const& other) {
   m_value -= other.m_value;
   return *this;
}

//Money& operator %= (Money const& other);
//Money& operator /= (Money const& other);

Money& Money::operator*=(int64_t other) {
   m_value *= other;
   return *this;
}

Money& Money::operator%=(int64_t other) {
   m_value %= other;
   return *this;
}

Money& Money::operator/=(int64_t other) {
   m_value /= other;
   return *this;
}

void swap(Money& first, Money& second) {
   using std::swap;
   swap(first.m_value, second.m_value);
}

} // namespace util