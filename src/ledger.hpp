#ifndef COCLES_LEDGER_HPP
#define COCLES_LEDGER_HPP

#include "account_table.hpp"
#include "adjustment_table.hpp"

#include "date/date.hpp"

#include <string>
#include <vector>

struct transaction_t {
   unsigned long id;
   std::string memo;
   date::year_month_day date;
};

// Possible events:
// add transaction
// edit transaction
//    add adjustment
//    edit adjustment
//    remove adjustment
// remove transaction
// add account
// edit account
// remove account

struct ledger_t {
   void UpdateWithEvent(std::string event);
   money_t GetBalance(std::string account);
   void AddTransaction(std::string trans);
private:
   unsigned long GetUnusedAdjustmentId(void) const;
   std::vector<transaction_t> transactions;
   account_table_t accounts;
   adjustment_table_t adjustments;
};

#endif // COCLES_LEDGER_HPP
