#ifndef COCLES_LEDGER_INTERNAL_ENTRYPROXY_HPP
#define COCLES_LEDGER_INTERNAL_ENTRYPROXY_HPP

#include "Identifier.hpp"

#include <utility>

namespace ledger {

namespace internal {

template <typename TYPE>
struct EntryProxy {

   explicit EntryProxy(Identifier<TYPE> id);

   EntryProxy();

   bool is_null();

   Identifier<TYPE> get_id() const;

   bool operator==(const EntryProxy& other) const;

private:
   Identifier<TYPE> m_id;
}; // struct EntryProxy

////////////////// Implementation Details //////////////////

template <typename TYPE>
EntryProxy<TYPE>::EntryProxy(Identifier<TYPE> id)
   : m_id(std::move(id)) {}

template <typename TYPE>
EntryProxy<TYPE>::EntryProxy()
   : m_id(0) {}

template <typename TYPE>
bool EntryProxy<TYPE>::is_null() {
   return (0 == static_cast<size_t>(m_id));
}

template <typename TYPE>
Identifier<TYPE> EntryProxy<TYPE>::get_id() const {
   return m_id;
}

template <typename TYPE>
bool EntryProxy<TYPE>::operator==(const EntryProxy& other) const {
   return (m_id == other.m_id);
}

} // namespace internal

} // namespace ledger
#endif // COCLES_LEDGER_INTERNAL_ENTRYPROXY_HPP
