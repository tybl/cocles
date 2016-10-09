#include "Record.hpp"

namespace ledger {

namespace internal {

Record::Record()
   : m_is_available(false) {}

Record::Record(bool available)
   : m_is_available(available) {}

void Record::set_available(bool available) {
   m_is_available = available;
}

bool Record::is_available() const {
   return m_is_available;
}

} // namespace internal

} // namespace ledger
