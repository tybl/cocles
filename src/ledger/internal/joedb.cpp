
#include "RecordKeeper.hpp"

template <typename TYPE>
constexpr size_t ledger::internal::RecordKeeper<TYPE>::used_index;

template <typename TYPE>
constexpr size_t ledger::internal::RecordKeeper<TYPE>::free_index;

#include <string>

template <typename TYPE>
struct EntryProxy {
   explicit EntryProxy(Identifier<TYPE> id) : m_id(id) {}
   EntryProxy() : m_id(0) {}
   bool is_null() { return (0 == static_cast<size_t>(m_id)); }
   Identifier<TYPE> get_id() const { return m_id; }
   bool operator==(const EntryProxy& other) const { return (m_id == other.m_id); }
private:
   Identifier<TYPE> m_id;
};

#include "date/date.hpp"

struct Transaction {
   std::string memo;
   date::year_month_day date;
};
using TransactionEntry = EntryProxy<Transaction>;

struct AccountType {
   std::string name;
};
using AccountTypeEntry = EntryProxy<AccountType>;

struct Account {
   std::string name;
   AccountTypeEntry type;
};
using AccountEntry = EntryProxy<Account>;

struct Adjustment {
   AccountEntry account;
   TransactionEntry transaction;
};
using AdjustmentEntry = EntryProxy<Adjustment>;

struct TransactionTable;

struct Database {
   friend TransactionTable;

   TransactionTable get_transaction_table() const;

   TransactionEntry new_transaction() {
      return TransactionEntry(transaction_table.allocate());
   }

   TransactionEntry new_transaction(const date::year_month_day& date, const std::string& memo) {
      TransactionEntry result(transaction_table.allocate());
      transaction_table.get_record(result.get_id()).date = date;
      transaction_table.get_record(result.get_id()).memo = memo;
      return result;
   }

   void clear_transaction_table();

   void delete_transaction(TransactionEntry record) {
      transaction_table.free(record.get_id());
   }

   const date::year_month_day get_date(TransactionEntry record) const {
      assert(!record.is_null());
      return transaction_table.get_record(record.get_id()).date;
   }

   void set_date(TransactionEntry record, const date::year_month_day& date) {
      assert(!record.is_null());
      transaction_table.get_record(record.get_id()).date = date;
   }

   const std::string& get_memo(TransactionEntry record) const {
      assert(!record.is_null());
      return transaction_table.get_record(record.get_id()).memo;
   }

   void set_memo(TransactionEntry record, const std::string& memo) {
      assert(!record.is_null());
      transaction_table.get_record(record.get_id()).memo = memo;
   }

private:
   ledger::internal::RecordKeeper<AccountType> account_type_table;
   ledger::internal::RecordKeeper<Account> account_table;
   ledger::internal::RecordKeeper<Adjustment> adjustment_table;
   ledger::internal::RecordKeeper<Transaction> transaction_table;
};

struct TransactionTable {
   TransactionTable(const Database& database)
      : db(database) {}

   struct Iterator {
      Iterator(const ledger::internal::RecordKeeper<Transaction>& t)
         : table(t)
         , id(0) {}

      bool operator!=(const Iterator& other) const {
         return !(id == other.id);
      }

      Iterator& operator++() {
         id = table.get_next(id);
         return *this;
      }

      TransactionEntry operator*() {
         return TransactionEntry(id);
      }
   private:
      const ledger::internal::RecordKeeper<Transaction>& table;
      Identifier<Transaction> id;
      //size_t index;
   }; // class Iterator

   Iterator begin() {
      return ++Iterator(db.transaction_table);
   }

   bool is_empty() const {
      return db.transaction_table.is_empty();
   }
private:
   const Database& db;
};

TransactionTable Database::get_transaction_table() const {
   return TransactionTable(*this);
}

void Database::clear_transaction_table() {
   while (!get_transaction_table().is_empty()) {
      delete_transaction(*get_transaction_table().begin());
   }
}

#include <iostream>

int main () {
   Database db;
   auto first_trans = db.new_transaction();
   db.set_memo(first_trans, "Hello world!");
   std::cout << db.get_memo(first_trans) << std::endl;
}
