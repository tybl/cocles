#ifndef COCLES_LEDGER_INTERNAL_LISTNODE_HPP
#define COCLES_LEDGER_INTERNAL_LISTNODE_HPP

#include <cstddef> // size_t

namespace ledger {

namespace internal {

template <typename TYPE>
struct ListNode {

   ListNode();

   ListNode(size_t p_next, size_t p_prev, bool p_free);

public:
   size_t next;
   size_t prev;
   TYPE data;
   bool free;
}; // struct ListNode

////////////////// Implementation Details //////////////////

template <typename TYPE>
ListNode<TYPE>::ListNode()
   : next(0)
   , prev(0)
   , data()
   , free(false) {}

template <typename TYPE>
ListNode<TYPE>::ListNode(size_t p_next, size_t p_prev, bool p_free)
   : next(p_next)
   , prev(p_prev)
   , data()
   , free(p_free) {}

} // namespace internal

} // namespace ledger

#endif // COCLES_LEDGER_INTERNAL_LISTNODE_HPP
