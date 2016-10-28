#ifndef COCLES_LEDGER_INTERNAL_IDENTIFIER_HPP
#define COCLES_LEDGER_INTERNAL_IDENTIFIER_HPP

#include <cstddef> // size_t

namespace ledger {

namespace internal {

template <typename TYPE>
struct Identifier {

   constexpr explicit Identifier(size_t value) noexcept
      : m_value(value) {}

   bool operator==(const Identifier& other) const {
      return (m_value == other.m_value);
   }

   bool operator!=(const Identifier& other) const {
      return !operator==(other);
   }

   explicit operator size_t() const {
      return m_value;
   }

private:
   size_t m_value;
}; // struct Identifier

} // namespace internal

} // namespace ledger

#endif // COCLES_LEDGER_INTERNAL_IDENTIFIER_HPP
