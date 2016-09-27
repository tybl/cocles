#include "identifier.hpp"

#include "gtest/gtest.h"

TEST(identifier_t, dogfood) {
   const unsigned int seed = 123;
   identifier_t a(seed);
   EXPECT_EQ(seed, a());
}
