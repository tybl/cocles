#include "ledger.hpp"

#include "rapidjson/document.h"
#include <algorithm>
#include <iostream>

namespace ledger {
   void
   ledger_t::UpdateWithEvent(std::string event) {
   }

   void
   ledger_t::AddTransaction(std::string trans) {
      rapidjson::Document json_trans;
      json_trans.Parse(trans.c_str());

      const rapidjson::Value &adjusts = json_trans["adjustments"];
      for (rapidjson::SizeType i = 0; i < adjusts.Size(); ++i) {
         adjustments.AddAdjustment(adjusts[i]);
      }
   }

   money_t
   ledger_t::GetBalance(std::string account_name) {
      identifier_t account_id = accounts.GetIdForAccount(account_name);
      return adjustments.GetBalanceForAccount(account_id);
   }
}
