#include "integer.hpp"

namespace tbl {

integer_t::integer_t(long value)
   : size(value) {}

bool integer_t::operator==(const integer_t& other) const {
   return size == other.size;
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
   return (0 > size);
}

} // namespace tbl

#include "doctest/doctest.h"

TEST_CASE("tbl::integer_t: integer_t(long), operator==(integer_t)") {
   CHECK(tbl::integer_t(0) == tbl::integer_t(0));
}
