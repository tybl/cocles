#ifndef COCLES_LEDGER_INTERNAL_ENTRYPROXY_HPP
#define COCLES_LEDGER_INTERNAL_ENTRYPROXY_HPP

#include "Identifier.hpp"

#include <utility> // std::move()

namespace ledger {

namespace internal {

template <typename TYPE>
struct EntryProxy {

   constexpr explicit EntryProxy(Identifier<TYPE> id)
      : m_id(std::move(id)) {}

   constexpr EntryProxy()
      : m_id(0) {}

   bool is_null() const {
      return (0 == static_cast<size_t>(m_id));
   }

   Identifier<TYPE> get_id() const {
      return m_id;
   }

   bool operator==(const EntryProxy& other) const {
      return (m_id == other.m_id);
   }

private:
   Identifier<TYPE> m_id;
}; // struct EntryProxy

} // namespace internal

} // namespace ledger

#endif // COCLES_LEDGER_INTERNAL_ENTRYPROXY_HPP
