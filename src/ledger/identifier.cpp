#include "identifier.hpp"

namespace ledger {
   identifier_t::identifier_t(unsigned long new_value)
      : value(new_value)
   {
   }

   std::string
   identifier_t::ToString(void) const {
      return std::to_string(value);
   }

   unsigned long
   identifier_t::operator () (void) const {
      return value;
   }

   bool
   identifier_t::operator == (const identifier_t &other) const {
      return value == other.value;
   }
} // namespace ledger

std::ostream&
operator << (std::ostream &out, const ledger::identifier_t &id) {
   return out << id.ToString();
}
