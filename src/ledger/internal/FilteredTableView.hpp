#ifndef COCLES_LEDGER_INTERNAL_FILTEREDTABLEVIEW_HPP
#define COCLES_LEDGER_INTERNAL_FILTEREDTABLEVIEW_HPP

#include "TableView.hpp"

template<typename TYPE>
struct FilteredTableView {

   // TODO(tblyons): Add predicate function to determine which entries to make available
   explicit FilteredTableView(const ledger::internal::RecordKeeper<TYPE>& tab, std::function<bool(const TYPE&)> p)
      : records(tab)
      , pred(p) { }

   struct Iterator {
      // TODO(tblyons): Add predicate function to determine which entries to make available
      explicit Iterator(const ledger::internal::RecordKeeper<TYPE>& tab, std::function<bool(const TYPE&)> p)
         : table(tab)
         , id(tab.used_id)
         , pred(p) { }

      bool operator!=(const Iterator& other) const {
         return !(id == other.id);
      }

      Iterator& operator++() {
         while (id != table.used_id && !pred(table.get_record(id))) {
            id = table.get_next(id);
         }
         return this;
      }

      ledger::internal::EntryProxy<TYPE> operator*() {
         return ledger::internal::EntryProxy<TYPE>(id);
      }

   private:
      const ledger::internal::RecordKeeper<TYPE>& table;
      ledger::internal::Identifier<TYPE> id;
      std::function<bool(const TYPE&)> pred;
   };

   Iterator begin() {
      return ++Iterator(records, pred);
   }

   Iterator end() {
      return Iterator(records, pred);
   }

   bool is_empty() const {
      return records.is_empty();
   }

private:
   const ledger::internal::RecordKeeper<TYPE>& records;
   std::function<bool(const TYPE&)> pred;
};

#endif // COCLES_LEDGER_INTERNAL_FILTEREDTABLEVIEW_HPP
