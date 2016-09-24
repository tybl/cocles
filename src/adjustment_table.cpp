#include "adjustment_table.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>

struct sum_t {
   sum_t(identifier_t account_id)
      : m_total(0),
      m_account_id(account_id)
   {
      std::cerr << "sum_t(identifier_t account_id)\n";
   }

   sum_t(const sum_t &other)
      : m_total(other.m_total),
      m_account_id(other.m_account_id)
   {
      std::cerr << "sum_t(const sum_t &other)\n";
   }

   ~sum_t(void) {
      std::cerr << "~sum_t(void)\n";
   }

   void operator () (const adjustment_table_t::adjustment_t &a) {
      if (a.account_id == m_account_id) {
         m_total += a.amount;
      }
   }
   amount_t Total(void) const {
      return m_total;
   }
private:
   amount_t m_total;
   identifier_t m_account_id;
};

amount_t adjustment_table_t::GetBalanceForAccount(identifier_t account_id) {
   return std::accumulate(adjustments.begin(),
                          adjustments.end(),
                          amount_t(0.0),
                          [account_id] (const amount_t &amt, const adjustment_t &adj) -> amount_t {
                             return amt + ((adj.account_id == account_id) ? adj.amount : amount_t(0.0));
                          });
}

void adjustment_table_t::AddAdjustment(const rapidjson::Value &json_adjust) {
   adjustments.emplace_back(adjustments.size(),
                            amount_t(json_adjust["amount"].GetDouble()),
                            0ul,
                            0ul);
   for (auto a : adjustments) {
      std::cout << a.id << " " << a.amount << " " << a.account_id << " " << a.transaction_id << std::endl;
   }
}

adjustment_table_t::adjustment_t::adjustment_t(identifier_t new_id,
                                               amount_t new_amount,
                                               unsigned long new_account_id,
                                               unsigned long new_transaction_id)
   : id(new_id),
   amount(new_amount),
   account_id(new_account_id),
   transaction_id(new_transaction_id)
{
   // Intentionally left blank
}
