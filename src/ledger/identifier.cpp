#include "identifier.hpp"

#include <cstdint>
#include <string>

namespace ledger {

identifier_t::identifier_t(uint64_t new_value)
   : value(new_value) {}

std::string identifier_t::to_string() const {
   return std::to_string(value);
}

uint64_t identifier_t::operator () () const {
   return value;
}

bool identifier_t::operator == (const identifier_t &other) const {
   return value == other.value;
}

std::ostream& operator << (std::ostream &out, const ledger::identifier_t &id) {
   return out << id.to_string();
}

} // namespace ledger

// Test cases
#include "doctest/doctest.h"
#include <random>

TEST_CASE("identifier_t::operator()") {
   std::random_device rd;
   for (size_t i = 0; i < 10000; ++i) {
      const uint64_t seed = (static_cast<uint64_t>(rd()) << 32) | rd();
      ledger::identifier_t a(seed);
      CHECK(seed == a());
   }
}

TEST_CASE("identifier_t::to_string") {
   std::random_device rd;
   for (size_t i = 0; i < 10000; ++i) {
      const uint64_t seed = (static_cast<uint64_t>(rd()) << 32) | rd();
      ledger::identifier_t a(seed);
      CHECK(std::to_string(seed) == a.to_string());
   }
}

TEST_CASE("identifier_t::operator==") {
   std::random_device rd;
   for (size_t i = 0; i < 10000; ++i) {
      const uint64_t seed = (static_cast<uint64_t>(rd()) << 32) | rd();
      ledger::identifier_t a(seed);
      ledger::identifier_t b(seed);
      CHECK(a == b);
   }
}
