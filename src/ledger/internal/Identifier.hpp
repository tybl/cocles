#ifndef COCLES_LEDGER_INTERNAL_IDENTIFIER_HPP
#define COCLES_LEDGER_INTERNAL_IDENTIFIER_HPP

#include <cstddef>

namespace ledger {

namespace internal {

template <typename TYPE>
struct Identifier {

   explicit Identifier(size_t value);

   bool operator==(const Identifier& other) const;

   explicit operator size_t() const;

private:
   size_t m_value;
}; // struct Identifier

////////////////// Implementation Details //////////////////

template <typename TYPE>
Identifier<TYPE>::Identifier(size_t value)
   : m_value(value) {}

template <typename TYPE>
bool Identifier<TYPE>::operator==(const Identifier& other) const {
   return (m_value == other.m_value);
}

template <typename TYPE>
Identifier<TYPE>::operator size_t() const {
   return m_value;
}

} // namespace internal

} // namespace ledger

#endif // COCLES_LEDGER_INTERNAL_IDENTIFIER_HPP
