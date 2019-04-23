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

#include "Hapenny.hpp"

#include <iomanip>
#include <sstream>

t   b   m   t
123,456,789,012,345

namespace util {

Hapenny::Hapenny()
   : m_value(0)
{}

Hapenny::Hapenny(std::string const& new_value)
   : m_value(0)
{
#if 0
   auto temp = 0.0L;
   std::istringstream value_stream(new_value, std::ios_base::in);
   value_stream >> std::get_money(temp, false);
   std::cout << "Hapenny(\"" << new_value << "\") = " << temp << "\n";
   m_value = static_cast<int64_t>(temp);
#endif
}

std::string Hapenny::to_string() const {
   return std::to_string(m_value / 200) + "." + std::to_string((m_value % 200) * 5);
}

bool Hapenny::operator==(Hapenny const& o) const {
   return m_value == o.m_value;
}

Hapenny& Hapenny::operator+=(Hapenny const& o) {
   m_value += o.m_value;
   return *this;
}

Hapenny& Hapenny::operator-=(Hapenny const& o) {
   m_value -= o.m_value;
   return *this;
}

//Hapenny& operator %= (Hapenny const& o);
//Hapenny& operator /= (Hapenny const& o);

Hapenny& Hapenny::operator*=(int64_t o) {
   m_value *= o;
   return *this;
}

Hapenny& Hapenny::operator%=(int64_t o) {
   m_value %= o;
   return *this;
}

Hapenny& Hapenny::operator/=(int64_t o) {
   m_value /= o;
   return *this;
}

void swap(Hapenny& a, Hapenny& b) {
   using std::swap;
   swap(a.m_value, b.m_value);
}

Hapenny operator+(Hapenny a, Hapenny const& b) {
   return a += b;
}

std::ostream& operator<<(std::ostream& s, Hapenny const& m) {
    return s << m.to_string();
}

} // namespace util
