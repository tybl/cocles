#ifndef COCLES_LEDGER_LEDGERIMPL_HPP
#define COCLES_LEDGER_LEDGERIMPL_HPP

#include "account_table.hpp"
#include "adjustment_table.hpp"
#include "transaction.hpp"

#include <vector>

namespace ledger {
   struct ledger_t::ledger_impl_t {
      std::vector<transaction_t> transactions;
      account_table_t accounts;
      adjustment_table_t adjustments;
   };
} // namespace ledger
#endif // COCLES_LEDGER_LEDGERIMPL_HPP
