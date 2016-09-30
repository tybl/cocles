#ifndef COCLES_LEDGER_ACCOUNTTABLE_HPP
#define COCLES_LEDGER_ACCOUNTTABLE_HPP

#include "account.hpp"
#include "ledger/identifier.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace ledger {
   namespace internal {
      struct account_table_t {
         const identifier_t&
         GetIdForAccount(std::string account_name);

         const std::string&
         GetNameForAccount(identifier_t id);

      private:
         static bool cmp(const account_t &a, const std::string &s);

      private:
         std::vector<account_t> accounts;
         std::map<unsigned long, size_t> id_index;
      }; // struct account_table_t
   } // namespace internal
} // namespace ledger
#endif // COCLES_LEDGER_ACCOUNTTABLE_HPP
