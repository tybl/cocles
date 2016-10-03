#ifndef COCLES_LEDGER_MONEY_HPP
#define COCLES_LEDGER_MONEY_HPP

#include <ostream>
#include <string>
#include <gmp.h>

namespace ledger {
   struct money_t {
      money_t(void);

      money_t(std::string new_value);

      money_t(double new_value);

      money_t(const money_t &other);

      ~money_t(void);

      std::string ToString(void) const;

      money_t& operator = (money_t other);

      money_t& operator += (const money_t &other);

      bool operator == (const money_t &other) const;
   private:
      mpz_t value;
   }; // struct money_t
} // namespace ledger

std::ostream& operator << (std::ostream &out, const ledger::money_t &a);

ledger::money_t operator + (ledger::money_t lhs, const ledger::money_t &rhs);
#endif // COCLES_LEDGER_MONEY_HPP
