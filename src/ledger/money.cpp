#include "money.hpp"

#include <iostream>

namespace ledger {

money_t::money_t()
   : value(0) { }

money_t::money_t(const std::string& new_value) {
   int64_t whole, frac;
   int result = sscanf(new_value.c_str(), "%ld.%2ld", &whole, &frac);
   if (result > 0) {
      value = whole * 100;
      if (result > 1) {
         value += frac;
      }
   }
}

money_t::money_t(const money_t &other)
   : value(other.value) { }

std::string money_t::to_string() const {
   //TODO: Force frac to positive (whole should also be affected)
   int64_t whole = value / 100;
   int64_t frac = value % 100;
   char buffer[24];
   std::snprintf(buffer, 24, "%ld.%02ld", whole, frac);
   return std::string(buffer);
}

money_t& money_t::operator = (money_t other) {
   //TODO: This is not implemented in the standard copy-and-swap paradigm
   std::swap(value, other.value);
   return *this;
}

money_t& money_t::operator += (const money_t &other) {
   value += other.value;
   return *this;
}

bool money_t::operator == (const money_t &other) const {
   return value == other.value;
}

std::ostream& operator << (std::ostream &out, const money_t &a) {
   return out << a.to_string();
}

ledger::money_t operator + (money_t lhs, const money_t &rhs) {
   return lhs += rhs;
}

} // namespace ledger
