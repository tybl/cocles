#ifndef COCLES_LEDGER_INTERNAL_LISTNODE_HPP
#define COCLES_LEDGER_INTERNAL_LISTNODE_HPP

#include "Identifier.hpp"

#include <cstddef> // size_t
#include <stdexcept>

namespace ledger {

namespace internal {

template <typename TYPE>
struct ListNode {

   constexpr ListNode()
      : m_next(0)
      , m_prev(0)
      , m_data() {}

   constexpr ListNode(Identifier<TYPE> next, Identifier<TYPE> prev, bool p_free)
      : m_next(next)
      , m_prev((static_cast<size_t>(prev) << 1) | (p_free & 1))
      , m_data() {}

   void set_free(bool free) {
      m_prev |= 1 & free;
   }

   bool get_free() const {
      return m_prev & 1;
   }

   Identifier<TYPE>& next() {
      return m_next;
   }

   const Identifier<TYPE>& next() const {
      return m_next;
   }

   void set_prev(Identifier<TYPE> id) {
      size_t temp = static_cast<size_t>(id);
      // TODO: Figure out how to eliminate this check and thrown exception
      if (std::numeric_limits<int64_t>::max() < temp) {
         throw std::overflow_error("Identifier is too large");
      }
      m_prev = (temp << 1) | (m_prev & 1);
   }

   const Identifier<TYPE> get_prev() const {
      return Identifier<TYPE>(m_prev >> 1);
   }

   TYPE& data() {
      return m_data;
   }

   const TYPE& data() const {
      return m_data;
   }

private:
   Identifier<TYPE> m_next;
   size_t m_prev;
   TYPE m_data;
}; // struct ListNode

} // namespace internal

} // namespace ledger

#endif // COCLES_LEDGER_INTERNAL_LISTNODE_HPP
