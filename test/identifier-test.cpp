#include "ledger/identifier.hpp"

#include "gtest/gtest.h"

#include <random>

TEST(identifier_t, binary_dogfood) {
   std::random_device rd;
   for (size_t i = 0; i < 10000; ++i) {
      const unsigned long seed = (static_cast<unsigned long>(rd()) << 32) | rd();
      ledger::identifier_t a(seed);
      EXPECT_EQ(seed, a());
   }
}

TEST(identifier_t, ascii_dogfood) {
   std::random_device rd;
   for (size_t i = 0; i < 10000; ++i) {
      const unsigned long seed = (static_cast<unsigned long>(rd()) << 32) | rd();
      ledger::identifier_t a(seed);
      EXPECT_EQ(std::to_string(seed), a.ToString());
   }
}

TEST(identifier_t, equivalence) {
   std::random_device rd;
   for (size_t i = 0; i < 10000; ++i) {
      const unsigned long seed = (static_cast<unsigned long>(rd()) << 32) | rd();
      ledger::identifier_t a(seed);
      ledger::identifier_t b(seed);
      EXPECT_EQ(a, b);
   }
}
