#ifndef COCLES_LEDGER_INTERNAL_TRANSACTION_HPP
#define COCLES_LEDGER_INTERNAL_TRANSACTION_HPP

#include "ledger/identifier.hpp"

#include "date/date.hpp"

#include <string>

namespace ledger {
   namespace internal {
      struct transaction_t {
         identifier_t id;
         std::string memo;
         date::year_month_day date;
      }; // transaction_t
   } // namespace internal
} // namespace ledger
#endif // COCLES_LEDGER_INTERNAL_TRANSACTION_HPP
