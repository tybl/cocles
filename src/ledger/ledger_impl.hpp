#ifndef COCLES_LEDGER_LEDGERIMPL_HPP
#define COCLES_LEDGER_LEDGERIMPL_HPP

#include "internal/account_table.hpp"
#include "internal/adjustment_table.hpp"
#include "transaction.hpp"

#include <vector>

namespace ledger {
   struct ledger_t::ledger_impl_t {
      std::vector<transaction_t> transactions;
      internal::account_table_t accounts;
      internal::adjustment_table_t adjustments;
   };
} // namespace ledger
#endif // COCLES_LEDGER_LEDGERIMPL_HPP
