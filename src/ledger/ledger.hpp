#ifndef COCLES_LEDGER_LEDGER_HPP
#define COCLES_LEDGER_LEDGER_HPP

#include "money.hpp"

#include <memory>
#include <string>

namespace ledger {
   namespace internal { struct ledger_impl_t; }

   struct ledger_t {
      ledger_t(void);
      ledger_t(ledger_t &&) noexcept;
      ~ledger_t(void);
      ledger_t& operator = (ledger_t &&) noexcept;
      money_t get_account_balance(std::string account_name) const;
   private:
      std::unique_ptr<internal::ledger_impl_t> impl;
   };
} // namespace ledger
#endif // COCLES_LEDGER_LEDGER_HPP
