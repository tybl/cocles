#ifndef COCLES_LEDGER_IDENTIFIER_HPP
#define COCLES_LEDGER_IDENTIFIER_HPP

#include <ostream>
#include <string>

namespace ledger {

struct identifier_t {

   identifier_t(uint64_t new_value);

   std::string to_string(void) const;

   uint64_t operator () (void) const;

   bool operator == (const identifier_t &other) const;

private:
   unsigned long value;
}; // struct identifier_t

std::ostream& operator << (std::ostream &out, const ledger::identifier_t &id);

} // namespace ledger

#endif // COCLES_LEDGER_IDENTIFIER_HPP
