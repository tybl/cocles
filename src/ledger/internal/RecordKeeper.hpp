#ifndef COCLES_LEDGER_INTERNAL_RECORDKEEPER_HPP
#define COCLES_LEDGER_INTERNAL_RECORDKEEPER_HPP

#include "Identifier.hpp"
#include "ListNode.hpp"
#include "Record.hpp"

//#include <cassert>
#include <vector>

namespace ledger {

namespace internal {

template <typename TYPE>
struct RecordKeeper {

   RecordKeeper();

   TYPE& get_record(Identifier<TYPE> index);

   const TYPE& get_record(Identifier<TYPE> index) const;

   bool is_empty() const;

   size_t get_used_count() const;

   size_t size() const;

   size_t get_first_free() const; // TODO: Check the return type

   size_t get_first_used() const;

   Identifier<TYPE> get_next(Identifier<TYPE> index) const;

   size_t get_prev(size_t index) const;

   bool is_free(size_t index) const;

   bool is_used(size_t index) const;

   void use(size_t index);

   void free(Identifier<TYPE> id);

   Identifier<TYPE> allocate();

   void push_back(); // TODO: determine if this should be public

private:
   size_t used_count;
   std::vector<ListNode<TYPE>> records;
   static constexpr size_t used_index = 0;
   static constexpr size_t free_index = 1;
}; // struct RecordKeeper

////////////////// Implementation Details //////////////////

template <typename TYPE>
constexpr size_t RecordKeeper<TYPE>::used_index;

template <typename TYPE>
constexpr size_t RecordKeeper<TYPE>::free_index;

template <typename TYPE>
RecordKeeper<TYPE>::RecordKeeper()
   : used_count(0)
   , records(2)
{
   records[used_index].free = false;
   records[used_index].next = used_index;
   records[used_index].prev = used_index;

   records[free_index].free = true;
   records[free_index].next = free_index;
   records[free_index].prev = free_index;
}

template <typename TYPE>
TYPE& RecordKeeper<TYPE>::get_record(Identifier<TYPE> index) {
   return records[static_cast<size_t>(index)].data;
}

template <typename TYPE>
const TYPE& RecordKeeper<TYPE>::get_record(Identifier<TYPE> index) const {
   return records[static_cast<size_t>(index)].data;
}

template <typename TYPE>
bool RecordKeeper<TYPE>::is_empty() const {
   return (0 == used_count);
}

template <typename TYPE>
size_t RecordKeeper<TYPE>::get_used_count() const {
   return used_count;
}

template <typename TYPE>
size_t RecordKeeper<TYPE>::size() const {
   return records.size() - 2; // First two used for bookkeeping
}

template <typename TYPE>
size_t RecordKeeper<TYPE>::get_first_free() const {
   return records[free_index].next;
}

template <typename TYPE>
size_t RecordKeeper<TYPE>::get_first_used() const {
   return records[used_index].next;
}

template <typename TYPE>
Identifier<TYPE> RecordKeeper<TYPE>::get_next(Identifier<TYPE> index) const {
   return Identifier<TYPE>(records[static_cast<size_t>(index)].next);
}

template <typename TYPE>
size_t RecordKeeper<TYPE>::get_prev(size_t index) const {
   return records[index].prev;
}

template <typename TYPE>
bool RecordKeeper<TYPE>::is_free(size_t index) const {
   return records[index].free;
}

template <typename TYPE>
bool RecordKeeper<TYPE>::is_used(size_t index) const {
   return 1 < index && index < records.size() && !records[index].free;
}

template <typename TYPE>
Identifier<TYPE> RecordKeeper<TYPE>::allocate() {
   size_t result = records[free_index].next;
   if (result == free_index) {
      push_back();
      result = records[free_index].next;
   }
   use(result);
   return Identifier<TYPE>(result);
}

template <typename TYPE>
void RecordKeeper<TYPE>::push_back() {
   const size_t index = records.size();
   records.emplace_back(records[free_index].next, free_index, true);

   records[records[free_index].next].prev = index;
   records[free_index].next = index;
}

template <typename TYPE>
void RecordKeeper<TYPE>::use(size_t index) {
   //assert(1 < index); // Cannot be bookkeeping indices
   //assert(index < records.size()); // Must be within table
   //assert(records[index].free); // Must be available

   ListNode<TYPE>& record_being_used = records[index];
   record_being_used.free = false; // It is no longer available

   // The record used to point to available nodes with next and prev,
   // now the available nodes at next and prev need to point to each other
   records[record_being_used.prev].next = record_being_used.next;
   records[record_being_used.next].prev = record_being_used.prev;

   // The record needs to point to elements in the used list
   // I think this inserts the record at the beginning of the list...
   // TODO: Determine if values assigned to next and prev should be swapped
   record_being_used.next = records[used_index].next;
   record_being_used.prev = used_index;

   // The used list needs to point to the record
   records[records[used_index].next].prev = index;
   records[used_index].next = index;

   used_count++;
}

template <typename TYPE>
void RecordKeeper<TYPE>::free(Identifier<TYPE> id) {
   const auto index = static_cast<size_t>(id);
   //assert(1 < index);
   //assert(index < records.size());
   //assert(!records[index].free);

   ListNode<TYPE>& record_being_freed = records[index];
   record_being_freed.free = true;

   records[record_being_freed.prev].next = record_being_freed.next;
   records[record_being_freed.next].prev = record_being_freed.prev;

   record_being_freed.next = records[free_index].next;
   record_being_freed.prev = free_index;

   records[records[free_index].next].prev = index;
   records[free_index].next = index;

   used_count--;
}

} // namespace internal

} // namespace ledger

#endif // COCLES_LEDGER_INTERNAL_RECORDKEEPER_HPP
