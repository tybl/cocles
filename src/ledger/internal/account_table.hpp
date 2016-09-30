#ifndef COCLES_LEDGER_INTERNAL_ACCOUNTTABLE_HPP
#define COCLES_LEDGER_INTERNAL_ACCOUNTTABLE_HPP

#include "account.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace ledger {
   namespace internal {
      struct account_table_t {
         account_t*
         GetIdForAccount(std::string account_name);

      private:
         static bool cmp(const account_t &a, const std::string &s);

      private:
         std::vector<account_t> accounts;
      }; // struct account_table_t
   } // namespace internal
} // namespace ledger
#endif // COCLES_LEDGER_INTERNAL_ACCOUNTTABLE_HPP
