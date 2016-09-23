#ifndef COCLES_LEDGER_HPP
#define COCLES_LEDGER_HPP

#include "account_table.hpp"

#include "date/date.hpp"

#include <string>
#include <vector>

struct adjustment_t {
   adjustment_t(unsigned long new_id,
                long new_amount,
                unsigned long new_account_id,
                unsigned long new_transaction_id)
      : id(new_id),
      amount(new_amount),
      account_id(new_account_id),
      transaction_id(new_transaction_id)
   {
      // Intentionally left blank
   }
   unsigned long id;
   long amount;
   unsigned long account_id;
   unsigned long transaction_id;
};

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
   long GetBalance(std::string account);
   void AddTransaction(std::string trans);
private:
   unsigned long GetUnusedAdjustmentId(void) const;
   std::vector<transaction_t> transactions;
   //std::vector<account_t> accounts;
   account_table_t accounts;
   std::vector<adjustment_t> adjustments;
};

#endif // COCLES_LEDGER_HPP
