#include "ledger/ledger.hpp"

#include "gtest/gtest.h"

TEST(ledger_t, size) {
   ledger::ledger_t ledger;
   EXPECT_EQ(ledger::money_t(0.0), ledger.get_account_balance("Credit Card"));
}
