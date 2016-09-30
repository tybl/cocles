#include "account_table.hpp"

namespace ledger {
   namespace internal {
      account_t*
      account_table_t::GetIdForAccount(std::string account_name) {
         auto pos = std::lower_bound(accounts.begin(), accounts.end(), account_name, cmp);
         if (accounts.end() == pos || pos->name != account_name) {
            // TODO: Need to know account type to create it...
            pos = accounts.emplace(pos, account_name, EQUITY);
         }
         for (auto a : accounts) {
            std::cout << a.name << std::endl;
         }
         std::cout << std::endl;
         return &(*pos);
      }

      bool
      account_table_t::cmp(const account_t &a, const std::string &s) {
         return a.name < s;
      }
   } // namespace internal
} // namespace ledger
