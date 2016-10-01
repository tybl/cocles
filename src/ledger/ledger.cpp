#include "ledger.hpp"

#include "internal/ledger_impl.hpp"

namespace ledger {
   ledger_t::ledger_t(void)
      : impl(std::make_unique<internal::ledger_impl_t>())
   {
   }

   ledger_t::ledger_t(ledger_t &&) noexcept = default;

   ledger_t::~ledger_t(void) = default;

   ledger_t&
   ledger_t::operator = (ledger_t &&) noexcept = default;

   money_t
   ledger_t::get_account_balance(std::string account_name) const {
      money_t result(0.0);
      if (impl) {
         const auto& accounts = impl->accounts;
         const auto& adjustments = impl->adjustments;
         // find account object
         auto acnt_iter = std::lower_bound(accounts.begin(), accounts.end(), account_name,
                                           [] (const std::unique_ptr<internal::account_t> &a, const std::string &s) -> bool {
                                              return a->name < s;
                                           });
         // sum adjustment amounts for adjustments pointing to account
         if (accounts.end() != acnt_iter) {
            for (size_t i = 0; i < adjustments.size(); ++i) {
               if (adjustments[i] && adjustments[i]->account_ptr == acnt_iter->get()) {
                  result += adjustments[i]->amount;
               }
            }
         }
      }
      return result;
   }
}
