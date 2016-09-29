#include "ledger.hpp"

#include "ledger_impl.hpp"
#include "rapidjson/document.h"

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
      rapidjson::Document json_trans;
      json_trans.Parse(trans.c_str());

      const rapidjson::Value &adjusts = json_trans["adjustments"];
      for (rapidjson::SizeType i = 0; i < adjusts.Size(); ++i) {
         impl->adjustments.AddAdjustment(adjusts[i]);
      }
   }

   money_t
   ledger_t::GetBalance(std::string account_name) {
      identifier_t account_id = impl->accounts.GetIdForAccount(account_name);
      return impl->adjustments.GetBalanceForAccount(account_id);
   }
}
