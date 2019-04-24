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

#include "util/Money.hpp"

#include "doctest/doctest.h"

#include <sstream>

using namespace util;

TEST_CASE("Money::Money(),Money::Money(int64_t),Money::operator==(Money const&)") {
   CHECK(Money() == Money(0));
}

TEST_CASE("Money::Money(),Money::Money(std::string const&),Money::operator==(Money const&)") {
   CHECK(Money() == Money("0"));
}

TEST_CASE("Money::Money(),Money::operator*=(int64_t),Money::operator==(Money const&)") {
   CHECK((Money() *= 4) == Money());
}

TEST_CASE("Money::Money(int64_t),Money::operator*=(int64_t),Money::operator==(Money const&)") {
   CHECK((Money(16) *= 4) == Money(64));
}

TEST_CASE("Money::Money(int64_t),Money::operator*=(int64_t),Money::operator!=(Money const&)") {
   CHECK(!((Money(16) *= 4) != Money(64)));
   CHECK((Money(16) *= 4) != Money());
}

TEST_CASE("Money::Money(int64_t),Money::operator/=(int64_t),Money::operator<=(Money const&)") {
   CHECK((Money(16) /= 4) <= Money(4));
}

TEST_CASE("std::ostream& operator<<(std::ostream&,Money const&)") {
   const std::string s = "1234";
   std::stringstream ss;
   ss << Money(s);
   CHECK(ss.str() == s);
}

TEST_CASE("std::istream& operator>>(std::istream&, Money&)") {
   std::stringstream ss("1234");
   Money m;
   ss >> m;
   CHECK(m.get_money_type() == "1234");
}
