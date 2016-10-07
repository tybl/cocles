#include "TransactionTable.hpp"

#include "Database.hpp"
#include "RecordKeeper.hpp"
#include "TransactionEntry.hpp"

TransactionTable::TransactionTable(const Database& database)
   : db(database) {}

TransactionTable::Iterator::Iterator(const ledger::internal::RecordKeeper<Transaction>& t)
      : table(t)
      , id(0) {}

bool TransactionTable::Iterator::operator!=(const Iterator& other) const {
   return !(id == other.id);
}

TransactionTable::Iterator& TransactionTable::Iterator::operator++() {
   id = table.get_next(id);
   return *this;
}

TransactionEntry TransactionTable::Iterator::operator*() {
   return TransactionEntry(id);
}

TransactionTable::Iterator TransactionTable::begin() {
   return ++Iterator(db.transaction_table);
}

bool TransactionTable::is_empty() const {
   return db.transaction_table.is_empty();
}
