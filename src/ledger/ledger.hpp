#ifndef COCLES_LEDGER_LEDGER_HPP
#define COCLES_LEDGER_LEDGER_HPP

#include "account_table.hpp"
#include "adjustment_table.hpp"
#include "transaction.hpp"
#include "event.hpp"

#include <string>
#include <vector>

// Possible events:
// insert transaction
// modify transaction
//    insert adjustment
//    modify adjustment
//    remove adjustment
// remove transaction
// insert account
// modify account
// remove account

namespace ledger {
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
} // namespace ledger
#endif // COCLES_LEDGER_LEDGER_HPP
