#ifndef COCLES_LEDGER_INTERNAL_TRANSACTIONTABLE_HPP
#define COCLES_LEDGER_INTERNAL_TRANSACTIONTABLE_HPP

#include "Identifier.hpp"
#include "TransactionEntry.hpp"

struct Database;
namespace ledger {
   namespace internal {
      template <typename TYPE>
      struct RecordKeeper;
   } // namespace internal
} // namespace ledger

struct TransactionTable {

   explicit TransactionTable(const Database& database);

   struct Iterator {
      explicit Iterator(const ledger::internal::RecordKeeper<Transaction>& t);

      bool operator!=(const Iterator& other) const;

      Iterator& operator++();

      TransactionEntry operator*();

   private:
      const ledger::internal::RecordKeeper<Transaction>& table;
      ledger::internal::Identifier<Transaction> id;
   }; // class Iterator

   Iterator begin();

   bool is_empty() const;

private:
   const Database& db;
}; // struct TransactionTable

#endif // COCLES_LEDGER_INTERNAL_TRANSACTIONTABLE_HPP
