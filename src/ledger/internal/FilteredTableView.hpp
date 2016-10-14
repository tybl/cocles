#ifndef COCLES_LEDGER_INTERNAL_FILTEREDTABLEVIEW_HPP
#define COCLES_LEDGER_INTERNAL_FILTEREDTABLEVIEW_HPP

#include "TableView.hpp"

template<typename TYPE>
struct FilteredTableView {

   // TODO(tblyons): Add predicate function to determine which entries to make available
   explicit FilteredTableView(const ledger::internal::RecordKeeper<TYPE>& tab);

   struct Iterator {
      // TODO(tblyons): Add predicate function to determine which entries to make available
      explicit Iterator(const ledger::internal::RecordKeeper<TYPE>& tab);

      bool operator!=(const Iterator& other) const;

      Iterator& operator++();

      ledger::internal::EntryProxy<TYPE> operator*();

   private:
      const ledger::internal::RecordKeeper<TYPE>& table;
      ledger::internal::Identifier<TYPE> id;
   };

   Iterator begin();

   Iterator end();

   bool is_empty() const;

private:
   const ledger::internal::RecordKeeper<TYPE>& records;
};

#endif // COCLES_LEDGER_INTERNAL_FILTEREDTABLEVIEW_HPP
