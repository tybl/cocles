#ifndef COCLES_LEDGER_TRANSACTION_HPP
#define COCLES_LEDGER_TRANSACTION_HPP

#include "adjustment.hpp"

#include "date/date.hpp"

#include <string>
#include <vector>

namespace ledger {
   struct transaction_t {
      date::year_month_day date;
      std::string memo;
      std::vector<adjustment_t> adjustments;
   }; // struct transaction_t
} // namespace ledger

#endif // COCLES_LEDGER_TRANSACTION_HPP
