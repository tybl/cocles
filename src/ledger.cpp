#include "ledger.hpp"

#include "json/json.hpp"
#include <algorithm>
#include <iostream>

void ledger_t::UpdateWithEvent(std::string event) {
   static_cast<void>(event);
}

void ledger_t::AddTransaction(std::string trans) {
   auto json_trans = nlohmann::json::parse(trans);
   for (auto json_adjust : json_trans["adjustments"]) {
      adjustments.AddAdjustment(json_adjust);
   }
}

amount_t ledger_t::GetBalance(std::string account_name) {
   identifier_t account_id = accounts.GetIdForAccount(account_name);
   return adjustments.GetBalanceForAccount(account_id);
}
