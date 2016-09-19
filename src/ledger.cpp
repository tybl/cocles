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
      std::string account_name = json_adjust["account"].get<std::string>();
      auto account_iter = std::find_if(accounts.begin(), accounts.end(), [account_name](const account_t &a) -> bool { return a.name == account_name; });
      if (accounts.end() == account_iter) {
         unsigned long new_account_id = accounts.size();
         accounts.emplace_back(new_account_id, account_name, EQUITY);
         account_iter = std::find_if(accounts.begin(), accounts.end(), [account_name](const account_t &a) -> bool { return a.name == account_name; });
      }
      long amount = static_cast<long>(json_adjust["amount"].get<double>() * 100);
      unsigned long id = account_iter->id;
      new_adjusts.emplace_back(new_id,
                               amount,
                               id,
                               transactions.size());
   }
   // TODO: verify transaction balances
   adjustments.insert(adjustments.end(), new_adjusts.begin(), new_adjusts.end());
   std::cout << json_trans["date"].get<std::string>() << std::endl;
}

struct Sum {
   Sum(unsigned long new_account_id)
      : account_id(new_account_id),
      sum(0)
   {
      // Intentionally left blank
   }
   void operator()(const adjustment_t &a) { if (a.id == account_id) { sum += a.amount; } }
   const unsigned long account_id;
   long sum;
};

long ledger_t::GetBalance(std::string account_name) {
   auto account = std::find_if(accounts.begin(), accounts.end(), [account_name](const account_t &a) -> bool { return a.name == account_name; });
   Sum s = std::for_each(adjustments.begin(), adjustments.end(), Sum(account->id));
   return s.sum;
}
