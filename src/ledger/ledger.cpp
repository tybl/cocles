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

   void
   ledger_t::UpdateWithEvent(std::string event) {
   }

   void
   ledger_t::AddTransaction(std::string trans) {
   }

   money_t
   ledger_t::GetBalance(std::string account_name) {
      return money_t(0);
   }
}
