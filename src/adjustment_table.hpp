#ifndef COCLES_ADJUSTMENTTABLE_HPP
#define COCLES_ADJUSTMENTTABLE_HPP

#include "amount.hpp"
#include "identifier.hpp"

#include "json/json.hpp"

struct adjustment_table_t {
   amount_t GetBalanceForAccount(identifier_t account_id);

   void AddAdjustment(nlohmann::json json_adjust);

   struct adjustment_t {
      adjustment_t(identifier_t new_id,
                   amount_t new_amount,
                   unsigned long new_account_id,
                   unsigned long new_transaction_id);
      identifier_t id;
      amount_t amount;
      identifier_t account_id;
      unsigned long transaction_id;
   };
private:
   std::vector<adjustment_t> adjustments;
};
#endif // COCLES_ADJUSTMENTTABLE_HPP
