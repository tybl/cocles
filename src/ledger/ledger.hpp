#ifndef COCLES_LEDGER_LEDGER_HPP
#define COCLES_LEDGER_LEDGER_HPP

#include <string>

#include "money.hpp"

// Possible events:
// insert transaction
// modify transaction
//    insert adjustment
//    modify adjustment
//    remove adjustment
// remove transaction
// insert account
// modify account
// remove account

namespace ledger {
   namespace internal {
      struct ledger_impl_t;
   }

   struct ledger_t {
      ledger_t(void);

      ledger_t(ledger_t &&) noexcept;

      ~ledger_t(void);

      ledger_t&
      operator = (ledger_t &&) noexcept;

      void
      UpdateWithEvent(std::string event);

      money_t
      GetBalance(std::string account);

      void
      AddTransaction(std::string trans);

   private:
      std::unique_ptr<internal::ledger_impl_t> impl;
   };
} // namespace ledger
#endif // COCLES_LEDGER_LEDGER_HPP
