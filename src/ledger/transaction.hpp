#ifndef COCLES_LEDGER_TRANSACTION_HPP
#define COCLES_LEDGER_TRANSACTION_HPP

#include "date/date.hpp"

#include <string>

struct transaction_t {
   unsigned long id;
   std::string memo;
   date::year_month_day date;
};

#endif // COCLES_LEDGER_TRANSACTION_HPP
