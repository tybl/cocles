#ifndef COCLES_LEDGER_INTERNAL_ADJUSTMENT_HPP
#define COCLES_LEDGER_INTERNAL_ADJUSTMENT_HPP

#include "ledger/identifier.hpp"
#include "ledger/money.hpp"

namespace ledger {
   namespace internal {
      struct adjustment_t {
         adjustment_t(identifier_t new_id,
                      money_t new_amount,
                      unsigned long new_account_id,
                      unsigned long new_transaction_id);
         identifier_t id;
         money_t amount;
         identifier_t account_id;
         identifier_t transaction_id;
      }; // struct adjustment_t
   } // namespace internal
} // namespace ledger
#endif // COCLES_LEDGER_INTERNAL_ADJUSTMENT_HPP
