#include "account_table.hpp"

namespace ledger {
   namespace internal {
      const identifier_t&
      account_table_t::GetIdForAccount(std::string account_name) {
         auto pos = std::lower_bound(accounts.begin(), accounts.end(), account_name, cmp);
         if (accounts.end() == pos || pos->Name() != account_name) {
            // TODO: Need to know account type to create it...
            pos = accounts.emplace(pos, accounts.size(), account_name, account_t::EQUITY);
         }
         for (auto a : accounts) {
            std::cout << a.ID() << " " << a.Name() << std::endl;
         }
         std::cout << std::endl;
         return pos->ID();
      }

      const std::string&
      account_table_t::GetNameForAccount(identifier_t id) {
         return accounts.at(id_index.at(id())).Name();
      }

      bool
      account_table_t::cmp(const account_t &a, const std::string &s) {
         return a.Name() < s;
      }
   } // namespace internal
} // namespace ledger
