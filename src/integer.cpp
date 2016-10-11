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
   tbl::integer_t num("123456789012345678901234567890");
   CHECK(num.buffer_length == 30);
}
