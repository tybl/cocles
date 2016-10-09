#ifndef COCLES_LEDGER_INTERNAL_TRANSACTIONENTRY_HPP
#define COCLES_LEDGER_INTERNAL_TRANSACTIONENTRY_HPP

#include "EntryProxy.hpp"

#include "date/date.hpp"

#include <string>

struct Transaction {
   std::string memo;
   date::year_month_day date;
};

using TransactionEntry = ledger::internal::EntryProxy<Transaction>;

#endif // COCLES_LEDGER_INTERNAL_TRANSACTIONENTRY_HPP
