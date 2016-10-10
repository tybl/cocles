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

   TYPE& get_record(Identifier<TYPE> id);

   const TYPE& get_record(Identifier<TYPE> id) const;

   bool is_empty() const;

   size_t get_used_count() const;

   size_t size() const;

   Identifier<TYPE> get_first_free() const; // TODO: Check the return type

   Identifier<TYPE> get_first_used() const;

   Identifier<TYPE> get_next(Identifier<TYPE> id) const;

   Identifier<TYPE> get_prev(Identifier<TYPE> id) const;

   bool is_free(Identifier<TYPE> id) const;

   bool is_used(Identifier<TYPE> id) const;

   void use(Identifier<TYPE> id);

   void free(Identifier<TYPE> id);

   Identifier<TYPE> allocate();

   void push_back(); // TODO: determine if this should be public

private:
   ListNode<TYPE>& at(Identifier<TYPE> id);
   const ListNode<TYPE>& at(Identifier<TYPE> id) const;
private:
   std::vector<ListNode<TYPE>> records;
   size_t used_count;
   static constexpr Identifier<TYPE> used_id{0};
   static constexpr Identifier<TYPE> free_id{1};
}; // struct RecordKeeper

////////////////// Implementation Details //////////////////

template <typename TYPE>
constexpr Identifier<TYPE> RecordKeeper<TYPE>::used_id;

template <typename TYPE>
constexpr Identifier<TYPE> RecordKeeper<TYPE>::free_id;

template <typename TYPE>
RecordKeeper<TYPE>::RecordKeeper()
   : records({ ListNode<TYPE>(used_id, used_id, false), ListNode<TYPE>(free_id, free_id, true) })
   , used_count(0) {}

template <typename TYPE>
TYPE& RecordKeeper<TYPE>::get_record(Identifier<TYPE> id) {
   return at(id).data();
}

template <typename TYPE>
const TYPE& RecordKeeper<TYPE>::get_record(Identifier<TYPE> id) const {
   return at(id).data();
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
Identifier<TYPE> RecordKeeper<TYPE>::get_first_free() const {
   return at(free_id).next();
}

template <typename TYPE>
Identifier<TYPE> RecordKeeper<TYPE>::get_first_used() const {
   return at(used_id).next();
}

template <typename TYPE>
Identifier<TYPE> RecordKeeper<TYPE>::get_next(Identifier<TYPE> id) const {
   return at(id).next();
}

template <typename TYPE>
Identifier<TYPE> RecordKeeper<TYPE>::get_prev(Identifier<TYPE> id) const {
   return at(id).prev();
}

template <typename TYPE>
bool RecordKeeper<TYPE>::is_free(Identifier<TYPE> id) const {
   return at(id).get_free();
}

template <typename TYPE>
bool RecordKeeper<TYPE>::is_used(Identifier<TYPE> id) const {
   return (1 < static_cast<size_t>(id)) &&
          (static_cast<size_t>(id) < records.size()) &&
          !at(id).get_free();
}

template <typename TYPE>
Identifier<TYPE> RecordKeeper<TYPE>::allocate() {
   auto id = get_first_free();
   if (id == free_id) {
      push_back();
      id = at(free_id).next();
   }
   use(id);
   return id;
}

template <typename TYPE>
void RecordKeeper<TYPE>::push_back() {
   Identifier<TYPE> id(records.size());
   records.emplace_back(at(free_id).next(), free_id, true);

   at(at(free_id).next()).set_prev(id);
   at(free_id).next() = id;
}

template <typename TYPE>
void RecordKeeper<TYPE>::use(Identifier<TYPE> id) {
   ListNode<TYPE>& record_being_used = at(id);
   record_being_used.set_free(false); // It is no longer available

   // The record used to point to available nodes with next and prev,
   // now the available nodes at next and prev need to point to each other
   at(record_being_used.get_prev()).next() = record_being_used.next();
   at(record_being_used.next()).set_prev(record_being_used.get_prev());

   // The record needs to point to elements in the used list
   // I think this inserts the record at the beginning of the list...
   // TODO: Determine if values assigned to next and prev should be swapped
   record_being_used.next() = at(used_id).next();
   record_being_used.set_prev(used_id);

   // The used list needs to point to the record
   at(at(used_id).next()).set_prev(id);
   at(used_id).next() = id;

   used_count++;
}

template <typename TYPE>
void RecordKeeper<TYPE>::free(Identifier<TYPE> id) {
   ListNode<TYPE>& record_being_freed = at(id);
   record_being_freed.set_free(true);

   at(record_being_freed.get_prev()).next() = record_being_freed.next();
   at(record_being_freed.next()).set_prev(record_being_freed.get_prev());

   record_being_freed.next() = at(free_id).next();
   record_being_freed.set_prev(free_id);

   at(at(free_id).next()).set_prev(id);
   at(free_id).next() = id;

   used_count--;
}

template <typename TYPE>
ListNode<TYPE>& RecordKeeper<TYPE>::at(Identifier<TYPE> id) {
   return records.at(static_cast<size_t>(id));
}

template <typename TYPE>
const ListNode<TYPE>& RecordKeeper<TYPE>::at(Identifier<TYPE> id) const {
   return records.at(static_cast<size_t>(id));
}

} // namespace internal

} // namespace ledger

#endif // COCLES_LEDGER_INTERNAL_RECORDKEEPER_HPP
