#ifndef COCLES_LEDGER_INTERNAL_RECORDKEEPER_HPP
#define COCLES_LEDGER_INTERNAL_RECORDKEEPER_HPP

#include "Record.hpp"

namespace ledger {

namespace internal {

template<typename TYPE = Record> // TODO: Does this template need a default value?
struct RecordKeeper {
   RecordKeeper();

   TYPE& get_record(size_t index);

   const TYPE& get_record(size_t index) const;

   bool is_empty() const;

   size_t get_used_count() const;

   size_t size() const;

   size_t get_first_free() const; // TODO: Check the return type

   size_t get_first_used() const;

   size_t get_next(size_t index) const; // TODO: Check the parameter type

   size_t get_prev(size_t index) const;

   bool is_free(size_t index) const;

   bool is_used(size_t index) const;

   void use(size_t index);

   void free(size_t index);

   size_t allocate(); // TODO: determine if this should be public

   void push_back(); // TODO: determine if this should be public

private:
   struct ListNode {
      TYPE data;
      size_t next_index;
      size_t prev_index;
      // TODO: Figure out the interface if this included m_is_available instead of having it in Record
   };
   size_t used_count;
   std::vector<ListNode> records;
   static constexpr size_t used_index = 0;
   static constexpr size_t free_index = 1;
};

template<typename TYPE>
RecordKeeper<TYPE>::RecordKeeper()
   : used_count(0)
   , records(2)
{
   records[used_index].data.set_available(false);
   records[used_index].next = used_index;
   records[used_index].prev = used_index;

   records[free_index].data.set_available(true);
   records[free_index].next = free_index;
   records[free_index].prev = free_index;
}

template<typename TYPE>
TYPE& RecordKeeper<TYPE>::get_record(size_t index) {
   return records[index].data;
}

template<typename TYPE>
const TYPE& RecordKeeper<TYPE>::get_record(size_t index) const {
   return records[index].data;
}

template<typename TYPE>
bool RecordKeeper<TYPE>::is_empty() const {
   return (0 == used_count);
}

template<typename TYPE>
size_t RecordKeeper<TYPE>::get_used_count() const {
   return used_count;
}

template<typename TYPE>
size_t RecordKeeper<TYPE>::size() const {
   return records.size() - 2; // First two used for bookkeeping
}

template<typename TYPE>
size_t RecordKeeper<TYPE>::get_first_free() const {
   return records[free_index].next;
}

template<typename TYPE>
size_t RecordKeeper<TYPE>::get_first_used() const {
   return records[used_index].next;
}

template<typename TYPE>
size_t RecordKeeper<TYPE>::get_next(size_t index) const {
   return records[index].next;
}

template<typename TYPE>
size_t RecordKeeper<TYPE>::get_prev(size_t index) const {
   return records[index].prev;
}

template<typename TYPE>
bool RecordKeeper<TYPE>::is_free(size_t index) const {
   return records[index].data.is_available();
}

template<typename TYPE>
bool RecordKeeper<TYPE>::is_used(size_t index) const {
   return (1 < index) && (index < records.size()) && !records[index].data.is_available();
}

template<typename TYPE>
size_t RecordKeeper<TYPE>::allocate() {
   size_t result = records[free_index].next;
   if (result == free_index) {
      push_back();
      result = records[free_index].next;
   }
   use(result);
   return result;
}

template<typename TYPE>
void RecordKeeper<TYPE>::push_back() {
   const size_t index = records.size();
   records.push_back( { true, records[free_index].next, 1 } );

   records[records[free_index].next].prev = index;
   records[free_index].next = index;
}

template<typename TYPE>
void RecordKeeper<TYPE>::use(size_t index) {
   assert(1 < index); // Cannot be bookkeeping indices
   assert(index < records.size()); // Must be within table
   assert(records[index].data.is_available()); // Must be available

   ListNode& record_being_used = records[index];
   record_being_used.data.set_available(false); // It is no longer available

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

template<typename TYPE>
void RecordKeeper<TYPE>::free(size_t index) {
   assert(1 < index);
   assert(index < records.size());
   assert(!records[index].data.is_free());

   Record &record_being_freed = records[index];
   record_being_freed.data.set_free(true);

   records[record_being_freed.prev].next = record_being_freed.next;
   records[record_being_freed.next].prev = record_being_freed.prev;

   record_being_freed.next = records[free_list].next;
   record_being_freed.prev= 1;

   records[records[free_list].next].prev = index;
   records[free_list].next = index;

   used_count--;
}
} // namespace internal

} // namespace ledger

#endif // COCLES_LEDGER_INTERNAL_RECORDKEEPER_HPP
