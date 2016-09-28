#ifndef COCLES_ADJUSTMENTTABLE_HPP
#define COCLES_ADJUSTMENTTABLE_HPP

#include "adjustment.hpp"
#include "money.hpp"
#include "identifier.hpp"

#include "rapidjson/document.h"

#include <vector>

namespace ledger {
   struct adjustment_table_t {
      money_t
      GetBalanceForAccount(identifier_t account_id);

      void
      AddAdjustment(const rapidjson::Value &json_adjust);

   private:
      std::vector<adjustment_t> adjustments;
   };
} // namespace ledger
#endif // COCLES_ADJUSTMENTTABLE_HPP
