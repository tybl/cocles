#include "adjustment_table.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>

namespace ledger {
   money_t
   adjustment_table_t::GetBalanceForAccount(identifier_t account_id) {
      return std::accumulate(adjustments.begin(),
                             adjustments.end(),
                             money_t(0.0),
                             [account_id] (const money_t &amt, const adjustment_t &adj) -> money_t {
                                return amt + ((adj.account_id == account_id) ? adj.amount : money_t(0.0));
                             });
   }

   void
   adjustment_table_t::AddAdjustment(const rapidjson::Value &json_adjust) {
      adjustments.emplace_back(adjustments.size(),
                               money_t(json_adjust["amount"].GetDouble()),
                               0ul,
                               0ul);
      for (auto a : adjustments) {
         std::cout << a.id << " " << a.amount << " " << a.account_id << " " << a.transaction_id << std::endl;
      }
   }
} // namespace ledger
