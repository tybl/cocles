#include "Database.hpp"

#include "TableView.hpp"

// Methods for interacting with AccountTypes
TableView<AccountType> Database::get_account_type_table() const {
   return TableView<AccountType>(account_type_table);
}

AccountTypeEntry Database::new_account_type() {
   return AccountTypeEntry(account_type_table.allocate());
}

AccountTypeEntry Database::new_account_type(const std::string& name) {
   AccountTypeEntry result(account_type_table.allocate());
   account_type_table.get_record(result.get_id()).name = name;
   return result;
}

void Database::clear_account_type_table() {
   while (!get_account_type_table().is_empty()) {
      delete_account_type(*get_account_type_table().begin());
   }
}

void Database::delete_account_type(AccountTypeEntry record) {
   account_type_table.free(record.get_id());
}

const std::string& Database::get_name(AccountTypeEntry record) const {
   return account_type_table.get_record(record.get_id()).name;
}

void Database::set_name(AccountTypeEntry record, const std::string& name) {
   account_type_table.get_record(record.get_id()).name = name;
}

AccountTypeEntry Database::find_account_type_by_name(const std::string& name) const {
   for (auto account_type : get_account_type_table()) {
      if (get_name(account_type) == name) {
         return account_type;
      }
   }
   return AccountTypeEntry(ledger::internal::Identifier<AccountType>(0));
}

// Methods for interacting with Accounts
TableView<Account> Database::get_account_table() const {
   return TableView<Account>(account_table);
}

AccountEntry Database::new_account() {
   return AccountEntry(account_table.allocate());
}

AccountEntry Database::new_account(const std::string& name, AccountTypeEntry type) {
   AccountEntry result(account_table.allocate());
   account_table.get_record(result.get_id()).name = name;
   account_table.get_record(result.get_id()).type = type;
   return result;
}

void Database::clear_account_table() {
   while (!get_account_table().is_empty()) {
      delete_account(*get_account_table().begin());
   }
}

void Database::delete_account(AccountEntry record) {
   account_table.free(record.get_id());
}

const std::string& Database::get_name(AccountEntry record) const {
   return account_table.get_record(record.get_id()).name;
}

void Database::set_name(AccountEntry record, const std::string& name) {
   account_table.get_record(record.get_id()).name = name;
}

AccountEntry Database::find_account_by_name(const std::string& name) const {
   for (auto account : get_account_table()) {
      if (get_name(account) == name) {
         return account;
      }
   }
   return AccountEntry(ledger::internal::Identifier<Account>(0));
}

AccountTypeEntry Database::get_type(AccountEntry record) const {
   return account_table.get_record(record.get_id()).type;
}

void Database::set_type(AccountEntry record, AccountTypeEntry type) {
   account_table.get_record(record.get_id()).type = type;
}

AccountEntry Database::find_account_by_type(AccountTypeEntry type) const {
   for (auto account : get_account_table()) {
      if (get_type(account) == type) {
         return account;
      }
   }
   return AccountEntry(ledger::internal::Identifier<Account>(0));
}

// Methods for interacting with Transactions
TableView<Transaction> Database::get_transaction_table() const {
   return TableView<Transaction>(transaction_table);
}

TransactionEntry Database::new_transaction() {
   return TransactionEntry(transaction_table.allocate());
}

TransactionEntry Database::new_transaction(const date::year_month_day& date, const std::string& memo) {
   TransactionEntry result(transaction_table.allocate());
   transaction_table.get_record(result.get_id()).date = date;
   transaction_table.get_record(result.get_id()).memo = memo;
   return result;
}

void Database::clear_transaction_table() {
   while (!get_transaction_table().is_empty()) {
      delete_transaction(*get_transaction_table().begin());
   }
}

void Database::delete_transaction(TransactionEntry record) {
   transaction_table.free(record.get_id());
}

const date::year_month_day Database::get_date(TransactionEntry record) const {
   //assert(!record.is_null());
   return transaction_table.get_record(record.get_id()).date;
}

void Database::set_date(TransactionEntry record, const date::year_month_day& date) {
   //assert(!record.is_null());
   transaction_table.get_record(record.get_id()).date = date;
}

const std::string& Database::get_memo(TransactionEntry record) const {
   //assert(!record.is_null());
   return transaction_table.get_record(record.get_id()).memo;
}

void Database::set_memo(TransactionEntry record, const std::string& memo) {
   //assert(!record.is_null());
   transaction_table.get_record(record.get_id()).memo = memo;
}

// Methods for interacting with Adjustments
TableView<Adjustment> Database::get_adjustment_table() const {
   return TableView<Adjustment>(adjustment_table);
}

AdjustmentEntry Database::new_adjustment() {
   return AdjustmentEntry(adjustment_table.allocate());
}

AdjustmentEntry Database::new_adjustment(AccountEntry account, TransactionEntry transaction) {
   AdjustmentEntry result(adjustment_table.allocate());
   adjustment_table.get_record(result.get_id()).account = account;
   adjustment_table.get_record(result.get_id()).transaction = transaction;
   return result;
}

void Database::clear_adjustment_table() {
   while (!get_adjustment_table().is_empty()) {
      delete_adjustment(*get_adjustment_table().begin());
   }
}

void Database::delete_adjustment(AdjustmentEntry record) {
   adjustment_table.free(record.get_id());
}

AccountEntry Database::get_account(AdjustmentEntry record) const {
   return adjustment_table.get_record(record.get_id()).account;
}

void Database::set_account(AdjustmentEntry record, AccountEntry account) {
   adjustment_table.get_record(record.get_id()).account = account;
}

AdjustmentEntry Database::find_adjustment_by_account(AccountEntry account) const {
   for (auto adjustment : get_adjustment_table()) {
      if (get_account(adjustment) == account) {
         return adjustment;
      }
   }
   return AdjustmentEntry(ledger::internal::Identifier<Adjustment>(0));
}

TransactionEntry Database::get_transaction(AdjustmentEntry record) const {
   return adjustment_table.get_record(record.get_id()).transaction;
}

void Database::set_transaction(AdjustmentEntry record, TransactionEntry transaction) {
   adjustment_table.get_record(record.get_id()).transaction = transaction;
}

AdjustmentEntry Database::find_adjustment_by_transaction(TransactionEntry transaction) const {
   for (auto adjustment : get_adjustment_table()) {
      if (get_transaction(adjustment) == transaction) {
         return adjustment;
      }
   }
   return AdjustmentEntry(ledger::internal::Identifier<Adjustment>(0));
}

// Template function specializations
template <>
const ledger::internal::RecordKeeper<Account>& Database::get_record_keeper<Account>() const {
   return account_table;
}

template <>
const ledger::internal::RecordKeeper<Adjustment>& Database::get_record_keeper<Adjustment>() const {
   return adjustment_table;
}

template <>
const ledger::internal::RecordKeeper<Transaction>& Database::get_record_keeper<Transaction>() const {
   return transaction_table;
}

template <>
const ledger::internal::RecordKeeper<AccountType>& Database::get_record_keeper<AccountType>() const {
   return account_type_table;
}

// Test cases
#include "doctest/doctest.h"

TEST_CASE("Database::transaction::memo dogfood") {
   Database db;
   auto first_trans = db.new_transaction();
   std::string input = "Hello world!";
   db.set_memo(first_trans, input);
   CHECK(input == db.get_memo(first_trans));
}
