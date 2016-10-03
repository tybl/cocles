#include "decimal.hpp"
#include "gtest/gtest.h"

TEST(decimal_t, to_string) {
   const decimal_t num(5.1, 16);
   EXPECT_STREQ("5.1000000000000000", num.to_string().c_str());
}

TEST(decimal_t, round) {
   decimal_t price(29.99, 2);
   decimal_t tax(1.08, 2);
   price *= tax;
   EXPECT_STREQ("32.3892", price.to_string().c_str());
   price.round(2);
   EXPECT_STREQ("32.39", price.to_string().c_str());
}

TEST(decimal_t, addition) {
   decimal_t large(1234, 0);
   decimal_t small(0.5678, 4);
   decimal_t combined(1234.5678, 4);
   large += small;
   EXPECT_EQ(large, combined);
}
