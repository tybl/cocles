#ifndef COCLES_LEDGER_ADJUSTMENTTABLE_HPP
#define COCLES_LEDGER_ADJUSTMENTTABLE_HPP

#include "ledger/adjustment.hpp"
#include "money.hpp"
#include "ledger/identifier.hpp"

#include "rapidjson/document.h"

#include <vector>

namespace ledger {
   namespace internal {
      struct adjustment_table_t {
         money_t
         GetBalanceForAccount(identifier_t account_id);

         void
         AddAdjustment(const rapidjson::Value &json_adjust);

      private:
         std::vector<adjustment_t> adjustments;
      }; // struct adjustment_table_t
   } // namespace internal
} // namespace ledger
#endif // COCLES_LEDGER_ADJUSTMENTTABLE_HPP
