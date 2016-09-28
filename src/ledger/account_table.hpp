#ifndef COCLES_ACCOUNTTABLE_HPP
#define COCLES_ACCOUNTTABLE_HPP

#include "account.hpp"
#include "identifier.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace ledger {
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
   };
} // namespace ledger
#endif // COCLES_ACCOUNTTABLE_HPP
