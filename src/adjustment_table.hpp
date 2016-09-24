#ifndef COCLES_ADJUSTMENTTABLE_HPP
#define COCLES_ADJUSTMENTTABLE_HPP

#include "money.hpp"
#include "identifier.hpp"

#include "json/json.hpp"

struct adjustment_table_t {
   money_t GetBalanceForAccount(identifier_t account_id);

   void AddAdjustment(nlohmann::json json_adjust);

   struct adjustment_t {
      adjustment_t(identifier_t new_id,
                   money_t new_amount,
                   unsigned long new_account_id,
                   unsigned long new_transaction_id);
      identifier_t id;
      money_t amount;
      identifier_t account_id;
      unsigned long transaction_id;
   };
private:
   std::vector<adjustment_t> adjustments;
};
#endif // COCLES_ADJUSTMENTTABLE_HPP
