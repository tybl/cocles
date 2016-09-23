#include "ledger.hpp"

#include "json/json.hpp"
#include <algorithm>
#include <iostream>

void ledger_t::UpdateWithEvent(std::string event) {
   static_cast<void>(event);
}

void ledger_t::AddTransaction(std::string trans) {
   std::vector<adjustment_t> new_adjusts;
   auto json_trans = nlohmann::json::parse(trans);
   for (auto json_adjust : json_trans["adjustments"]) {
      size_t new_id = adjustments.size() + new_adjusts.size();
      size_t account_id = accounts.GetIdForAccount(json_adjust["account"].get<std::string>());
      long amount = static_cast<long>(json_adjust["amount"].get<double>() * 100);
      new_adjusts.emplace_back(new_id,
                               amount,
                               account_id,
                               transactions.size());
   }
   // TODO: verify transaction balances
   adjustments.insert(adjustments.end(), new_adjusts.begin(), new_adjusts.end());
}

struct Sum {
   Sum(unsigned long new_account_id)
      : account_id(new_account_id),
      total(0)
   {
      // Intentionally left blank
   }
   void operator()(const adjustment_t &a) { if (a.id == account_id) { total += a.amount; } }
   const unsigned long account_id;
   long total;
};

long ledger_t::GetBalance(std::string account_name) {
   unsigned long account_id = accounts.GetIdForAccount(account_name);
   return std::for_each(adjustments.begin(), adjustments.end(), Sum(account_id)).total;
}
