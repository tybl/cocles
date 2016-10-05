#include "ledger/account.hpp"
#include "ledger/ledger.hpp"
#include "ledger/transaction.hpp"

#include "gtest/gtest.h"

TEST(ledger_t, get_account_balance) {
   ledger::ledger_t ledger;
   EXPECT_EQ(ledger::money_t(0.0), ledger.get_account_balance("Credit Card"));
}

TEST(ledger_t, insert_account) {
   ledger::ledger_t ledger;
   ledger::account_t a;
   a.name = "Credit Card";
   ledger += a;
   EXPECT_EQ(ledger::money_t(0.0), ledger.get_account_balance("Credit Card"));
}

TEST(ledger_t, insert_transaction) {
   ledger::ledger_t ledger;
   ledger::transaction_t trans;
   trans.date = date::year(2016)/10/2;
   trans.memo = "Test";
   ledger::adjustment_t adjust;
   adjust.account.name = "Credit Card";
   adjust.amount = ledger::money_t(5.00);
   trans.adjustments.push_back(adjust);
   ledger += trans;
   EXPECT_EQ(ledger.get_account_balance("Credit Card"), ledger::money_t(5.00));
}
