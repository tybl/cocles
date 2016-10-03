#include "money.hpp"

#include <iostream>

namespace ledger {
   money_t::money_t(void) {
      mpz_init(value);
   }

   money_t::money_t(std::string new_value) {
      mpz_init(value);
   }

   money_t::money_t(double new_value) {
      mpz_init_set_d(value, new_value * 100);
   }

   money_t::money_t(const money_t &other) {
      mpz_init_set(value, other.value);
   }

   money_t::~money_t(void) {
      mpz_clear(value);
   }

   std::string money_t::ToString(void) const {
      mpz_t whole;
      mpz_init(whole);
      unsigned long fraction = mpz_tdiv_q_ui(whole, value, 100);
      int length = gmp_snprintf(nullptr, 0, "%Zd.%02lu", whole, fraction);
      length = (0 < length) ? length : 0;
      std::string result(static_cast<unsigned>(length), '\0');
      gmp_snprintf(&result[0], length + 1, "%Zd.%02lu", whole, fraction);
      mpz_clear(whole);
      return result;
   }

   money_t& money_t::operator = (money_t other) {
      mpz_swap(value, other.value);
      return *this;
   }

   money_t& money_t::operator += (const money_t &other) {
      mpz_add(value, value, other.value);
      return *this;
   }
   bool money_t::operator == (const money_t &other) const {
      return 0 == mpz_cmp(value, other.value);
   }
} // namespace ledger

std::ostream& operator << (std::ostream &out, const ledger::money_t &a) {
   return out << a.ToString();
}

ledger::money_t operator + (ledger::money_t lhs, const ledger::money_t &rhs) {
   return lhs += rhs;
}
