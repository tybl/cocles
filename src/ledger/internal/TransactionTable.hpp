#ifndef COCLES_LEDGER_INTERNAL_TABLE_HPP
#define COCLES_LEDGER_INTERNAL_TABLE_HPP

#include "EntryProxy.hpp"
#include "Identifier.hpp"

struct Database;
namespace ledger {
   namespace internal {
      template <typename TYPE>
      struct RecordKeeper;
   } // namespace internal
} // namespace ledger

template <typename TYPE>
struct Table {

   explicit Table(const Database& database);

   struct Iterator {
      explicit Iterator(const ledger::internal::RecordKeeper<TYPE>& t);

      bool operator!=(const Iterator& other) const;

      Iterator& operator++();

      ledger::internal::EntryProxy<TYPE> operator*();

   private:
      const ledger::internal::RecordKeeper<TYPE>& table;
      ledger::internal::Identifier<TYPE> id;
   }; // class Iterator

   Iterator begin();

   Iterator end();

   bool is_empty() const;

private:
   const Database& db;
}; // struct Table

template <typename TYPE>
Table<TYPE>::Table(const Database& database)
   : db(database) {}

template <typename TYPE>
Table<TYPE>::Iterator::Iterator(const ledger::internal::RecordKeeper<TYPE>& t)
      : table(t)
      , id(0) {}

template <typename TYPE>
bool Table<TYPE>::Iterator::operator!=(const Iterator& other) const {
   return !(id == other.id);
}

template <typename TYPE>
typename Table<TYPE>::Iterator& Table<TYPE>::Iterator::operator++() {
   id = table.get_next(id);
   return *this;
}

template <typename TYPE>
ledger::internal::EntryProxy<TYPE> Table<TYPE>::Iterator::operator*() {
   return ledger::internal::EntryProxy<TYPE>(id);
}

template <typename TYPE>
typename Table<TYPE>::Iterator Table<TYPE>::begin() {
   return ++Iterator(db.get_record_keeper<TYPE>());
}

template <typename TYPE>
typename Table<TYPE>::Iterator Table<TYPE>::end() {
   return Iterator(db.get_record_keeper<TYPE>());
}

template <typename TYPE>
bool Table<TYPE>::is_empty() const {
   return db.get_record_keeper<TYPE>().is_empty();
}
#endif // COCLES_LEDGER_INTERNAL_TABLE_HPP
