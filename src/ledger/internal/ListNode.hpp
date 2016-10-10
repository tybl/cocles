#ifndef COCLES_LEDGER_INTERNAL_LISTNODE_HPP
#define COCLES_LEDGER_INTERNAL_LISTNODE_HPP

#include "Identifier.hpp"

#include <cstddef> // size_t
#include <stdexcept>

namespace ledger {

namespace internal {

template <typename TYPE>
struct ListNode {

   ListNode();

   ListNode(Identifier<TYPE> p_next, Identifier<TYPE> p_prev, bool p_free);

   void set_free(bool free);
   bool get_free() const;

   Identifier<TYPE>& next();
   const Identifier<TYPE> next() const;

   void set_prev(Identifier<TYPE> id);
   const Identifier<TYPE> get_prev() const;

   TYPE& data();
   const TYPE& data() const;

private:
   Identifier<TYPE> m_next;
   size_t m_prev;
   TYPE m_data;
}; // struct ListNode

////////////////// Implementation Details //////////////////

template <typename TYPE>
ListNode<TYPE>::ListNode()
   : m_next(0)
   , m_prev(0)
   , m_data() {}

template <typename TYPE>
ListNode<TYPE>::ListNode(Identifier<TYPE> p_next, Identifier<TYPE> p_prev, bool p_free)
   : m_next(p_next)
   , m_prev((static_cast<size_t>(p_prev) << 1) | (p_free & 1))
   , m_data() {}

template <typename TYPE>
void ListNode<TYPE>::set_free(bool free) {
   m_prev |= 1 & free;
}

template <typename TYPE>
bool ListNode<TYPE>::get_free() const {
   return m_prev & 1;
}

template <typename TYPE>
Identifier<TYPE>& ListNode<TYPE>::next() {
   return m_next;
}

template <typename TYPE>
const Identifier<TYPE> ListNode<TYPE>::next() const {
   return m_next;
}

template <typename TYPE>
void ListNode<TYPE>::set_prev(Identifier<TYPE> id) {
   size_t temp = static_cast<size_t>(id);
   if (temp >> 63) {
      throw std::overflow_error("Identifier is too large");
   }
   m_prev = (temp << 1) | (m_prev & 1);
}

template <typename TYPE>
const Identifier<TYPE> ListNode<TYPE>::get_prev() const {
   return Identifier<TYPE>(m_prev >> 1);
}

template <typename TYPE>
TYPE& ListNode<TYPE>::data() {
   return m_data;
}

template <typename TYPE>
const TYPE& ListNode<TYPE>::data() const {
   return m_data;
}

} // namespace internal

} // namespace ledger

#endif // COCLES_LEDGER_INTERNAL_LISTNODE_HPP
