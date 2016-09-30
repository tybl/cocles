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
         money_t sum_adjustments_from_account(std::string account) {
            money_t result(0.0);
            for (size_t i = 0; i < accounts.size(); ++i) {
               if (accounts[i] && accounts[i]->name == account) {
                  const auto& adjusts = accounts[i]->adjustments;
                  for (size_t j = 0; j < adjusts.size(); ++j) {
                     result += adjusts[j]->amount;
                  }
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
