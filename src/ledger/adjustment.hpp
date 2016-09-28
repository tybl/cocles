#ifndef COCLES_LEDGER_ADJUSTMENT_HPP
#define COCLES_LEDGER_ADJUSTMENT_HPP

#include "identifier.hpp"
#include "money.hpp"

namespace ledger {
   struct adjustment_t {
      adjustment_t(identifier_t new_id,
                   money_t new_amount,
                   unsigned long new_account_id,
                   unsigned long new_transaction_id);
      identifier_t id;
      money_t amount;
      identifier_t account_id;
      unsigned long transaction_id;
   };
} // namespace ledger
#endif // COCLES_LEDGER_ADJUSTMENT_HPP
