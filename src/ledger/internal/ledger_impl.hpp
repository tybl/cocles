#ifndef COCLES_LEDGER_INTERNAL_LEDGERIMPL_HPP
#define COCLES_LEDGER_INTERNAL_LEDGERIMPL_HPP

#include "account.hpp"
#include "adjustment.hpp"
#include "transaction.hpp"

#include <memory>
#include <vector>

namespace ledger {
   namespace internal {
      struct ledger_impl_t {
         money_t sum_adjustments_from_account(std::string account_name) {
            money_t result(0.0);
            for (size_t i = 0; i < adjustments.size(); ++i) {
               if (adjustments[i] && adjustments[i]->account_ptr && adjustments[i]->account_ptr->name == account_name) {
                  result += adjustments[i]->amount;
               }
            }
            return result;
         }
      private:
         std::vector<std::unique_ptr<account_t>> accounts;
         std::vector<std::unique_ptr<adjustment_t>> adjustments;
         std::vector<std::unique_ptr<transaction_t>> transactions;
      }; // struct ledger_impl_t
   } // namespace internal
} // namespace ledger
#endif // COCLES_LEDGER_INTERNAL_LEDGERIMPL_HPP
