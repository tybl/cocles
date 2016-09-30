#ifndef COCLES_LEDGER_INTERNAL_TRANSACTION_HPP
#define COCLES_LEDGER_INTERNAL_TRANSACTION_HPP

#include "date/date.hpp"
#include <string>
#include <vector>

namespace ledger {
   namespace internal {
      struct adjustment_t;

      struct transaction_t {
         std::string memo;
         date::year_month_day date;
         std::vector<adjustment_t*> adjustments;
      }; // transaction_t
   } // namespace internal
} // namespace ledger
#endif // COCLES_LEDGER_INTERNAL_TRANSACTION_HPP
