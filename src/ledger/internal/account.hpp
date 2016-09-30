#ifndef COCLES_LEDGER_ACCOUNT_HPP
#define COCLES_LEDGER_ACCOUNT_HPP

#include "ledger/identifier.hpp"
#include <string>

namespace ledger {
   namespace internal {
      struct account_t {
         enum account_type_t {
            EQUITY,
            INCOME_EXPENSE,
            ASSET_LIABILITY,
            BUDGET_CATEGORY
         };
         account_t(unsigned long new_id,
                   std::string new_name,
                   account_type_t new_type);
         const std::string& Name(void) const;
         const identifier_t& ID(void) const;
         const account_type_t& Type(void) const;
      private:
         identifier_t id;
         std::string name;
         std::string memo;
         account_type_t type;
      }; // struct account_t
   } // namespace internal
} // namespace ledger
#endif // COCLES_LEDGER_ACCOUNT_HPP
