#include "integer.hpp"

namespace tbl {

integer_t::integer_t(long value)
   : mantissa_length(static_cast<size_t>(value * ((0 <= value) ? 1 : -1))) {}

bool integer_t::operator==(const integer_t& other) const {
   return mantissa_length == other.mantissa_length;
}

integer_t& integer_t::operator+=(integer_t ) {
   return *this;
}

integer_t& integer_t::operator-=(integer_t ) {
   return *this;
}

integer_t& integer_t::operator*=(integer_t ) {
   return *this;
}

integer_t& integer_t::operator/=(integer_t ) {
   return *this;
}

bool integer_t::is_negative() const {
   return false;// (0 > size);
}

} // namespace tbl

#include "doctest/doctest.h"

TEST_CASE("tbl::integer_t: integer_t(long), operator==(integer_t)") {
   CHECK(tbl::integer_t(0) == tbl::integer_t(0));
}

TEST_CASE("tbl::integer_t: integer_t(string)") {
   tbl::integer_t num1a("1");
   CHECK(num1a.buffer_length == 1);
   tbl::integer_t num1b("1234");
   CHECK(num1b.buffer_length == 1);
   tbl::integer_t num1c("4294967295");
   CHECK(num1c.buffer_length == 1);
   tbl::integer_t num2a("4294967296");
   CHECK(num2a.buffer_length == 2);
   tbl::integer_t num2b("18446744073709551615");
   CHECK(num2b.buffer_length == 2);
   tbl::integer_t num("123456789012345678901234567890");
   CHECK(num.buffer_length == 4);
}

TEST_CASE("tbl::basic_unsigned_integer constructor") {
   uint24_t a;
   uint24_t b;
   uint24_t c(4);
   uint24_t d(c);
   uint24_t e("512");
   CHECK(a == b);
   CHECK(c == d);
   CHECK(!(c == b));
   c = a;
   CHECK(c == b);
   CHECK(!(c == d));
}

TEST_CASE("tbl::basic_unsigned_integer::operator+=") {
   uint24_t a(24);
   uint24_t b(24);
   a += b;
   uint24_t c(48);
   CHECK(a == c);
}
