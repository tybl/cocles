#ifndef COCLES_LEDGER_ACCOUNT_HPP
#define COCLES_LEDGER_ACCOUNT_HPP

#include "identifier.hpp"
#include <string>

namespace ledger {
   struct account_t {
      account_t(unsigned long new_id,
                std::string new_name/*,
                account_type_t new_type*/);
      const std::string& Name(void) const;
      const identifier_t& ID(void) const;
   private:
      identifier_t id;
      std::string name;
      std::string memo;

#if 0
   enum account_type_t {
      EQUITY,
      INCOME_EXPENSE,
      ASSET_LIABILITY,
      BUDGET_CATEGORY
   };
#endif
      //account_type_t type;
   };
} // namespace ledger
#endif // COCLES_LEDGER_ACCOUNT_HPP
