#include "ledger.hpp"

#include "account.hpp"
#include "transaction.hpp"
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

   ledger_t&
   ledger_t::operator += (const account_t& account) {
      impl->accounts.emplace_back(std::make_unique<internal::account_t>(account.name, internal::EQUITY));
      return *this;
   }

   ledger_t&
   ledger_t::operator += (const transaction_t& transaction) {
      impl->transactions.emplace_back(std::make_unique<internal::transaction_t>(transaction));
      //internal::transaction_t& new_transaction = *impl->transactions.back().get();
      for (auto adjust : transaction.adjustments) {
         auto acnt_ptr = get_account_ptr(adjust.account.name);
         if (nullptr == acnt_ptr) {
            impl->accounts.emplace_back(std::make_unique<internal::account_t>(adjust.account.name, internal::EQUITY));
            acnt_ptr = impl->accounts.back().get();
         }
         impl->adjustments.emplace_back(std::make_unique<internal::adjustment_t>());
         impl->adjustments.back()->amount = adjust.amount;
         impl->adjustments.back()->account_ptr = acnt_ptr;
         impl->adjustments.back()->transaction_ptr = impl->transactions.back().get();
      }
      return *this;
   }

   money_t
   ledger_t::get_account_balance(std::string account_name) const {
      money_t result(0.0);
      if (impl) {
         const auto& adjustments = impl->adjustments;
         // find account object
         auto acnt_ptr = get_account_ptr(account_name);
         // sum adjustment amounts for adjustments pointing to account
         if (nullptr != acnt_ptr) {
            for (size_t i = 0; i < adjustments.size(); ++i) {
               if (adjustments[i] && adjustments[i]->account_ptr == acnt_ptr) {
                  result += adjustments[i]->amount;
               }
            }
         }
      }
      return result;
   }

   internal::account_t*
   ledger_t::get_account_ptr(std::string account_name) const {
      const auto& accounts = impl->accounts;
      auto acnt_iter = std::lower_bound(accounts.begin(), accounts.end(), account_name,
                                        [] (const std::unique_ptr<internal::account_t> &a, const std::string &s) -> bool {
                                           return a->name < s;
                                        });
      if (accounts.end() == acnt_iter) {
         return nullptr;
      }
      return acnt_iter->get();
   }
}
