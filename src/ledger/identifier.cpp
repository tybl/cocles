#include "identifier.hpp"

namespace ledger {
   identifier_t::identifier_t(unsigned long new_value)
      : value(new_value)
   {
   }

   std::string
   identifier_t::ToString(void) const {
      return std::to_string(value);
   }

   unsigned long
   identifier_t::operator () (void) const {
      return value;
   }

   bool
   identifier_t::operator == (const identifier_t &other) const {
      return value == other.value;
   }
} // namespace ledger

std::ostream&
operator << (std::ostream &out, const ledger::identifier_t &id) {
   return out << id.ToString();
}

// Test cases
#include "doctest/doctest.h"
#include <random>

TEST_CASE("identifier_t::operator()") {
   std::random_device rd;
   for (size_t i = 0; i < 10000; ++i) {
      const unsigned long seed = (static_cast<unsigned long>(rd()) << 32) | rd();
      ledger::identifier_t a(seed);
      CHECK(seed == a());
   }
}

TEST_CASE("identifier_t::to_string") {
   std::random_device rd;
   for (size_t i = 0; i < 10000; ++i) {
      const unsigned long seed = (static_cast<unsigned long>(rd()) << 32) | rd();
      ledger::identifier_t a(seed);
      CHECK(std::to_string(seed) == a.ToString());
   }
}

TEST_CASE("identifier_t::operator==") {
   std::random_device rd;
   for (size_t i = 0; i < 10000; ++i) {
      const unsigned long seed = (static_cast<unsigned long>(rd()) << 32) | rd();
      ledger::identifier_t a(seed);
      ledger::identifier_t b(seed);
      CHECK(a == b);
   }
}
