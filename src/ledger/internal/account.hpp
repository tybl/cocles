#ifndef COCLES_LEDGER_INTERNAL_ACCOUNT_HPP
#define COCLES_LEDGER_INTERNAL_ACCOUNT_HPP

#include <string>
#include <vector>

namespace ledger {
   namespace internal {
      struct adjustment_t;
      enum account_type_t {
         EQUITY,
         INCOME_EXPENSE,
         ASSET_LIABILITY,
         BUDGET_CATEGORY
      };
      struct account_t {
         account_t(std::string p_name, account_type_t p_type);
         std::string name;
         std::string memo;
         account_type_t type;
         std::vector<adjustment_t*> adjustments;
      }; // struct account_t
   } // namespace internal
} // namespace ledger
#endif // COCLES_LEDGER_INTERNAL_ACCOUNT_HPP
