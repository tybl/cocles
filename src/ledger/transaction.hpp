#ifndef COCLES_LEDGER_TRANSACTION_HPP
#define COCLES_LEDGER_TRANSACTION_HPP

#include "identifier.hpp"

#include "date/date.hpp"

#include <string>

namespace ledger {
   struct transaction_t {
      identifier_t id;
      std::string memo;
      date::year_month_day date;
   };
} // namespace ledger
#endif // COCLES_LEDGER_TRANSACTION_HPP
