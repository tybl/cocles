#include "adjustment.hpp"

namespace ledger {
   namespace internal {
      adjustment_t::adjustment_t(identifier_t new_id,
                                 money_t new_amount,
                                 unsigned long new_account_id,
                                 unsigned long new_transaction_id)
         : id(new_id),
         amount(new_amount),
         account_id(new_account_id),
         transaction_id(new_transaction_id)
      {
         // Intentionally left blank
      }
   } // namespace internal
} // namespace ledger
