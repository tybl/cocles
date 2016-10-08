#ifndef COCLES_LEDGER_INTERNAL_DATABASE_HPP
#define COCLES_LEDGER_INTERNAL_DATABASE_HPP

#include "RecordKeeper.hpp"
#include "AccountEntry.hpp"
#include "AccountTypeEntry.hpp"
#include "AdjustmentEntry.hpp"
#include "TransactionEntry.hpp"

template <typename TYPE> struct Table;

struct Database {
   template <typename TYPE>
   friend struct Table;

   // Methods for interacting with AccountTypes
   Table<AccountType> get_account_type_table() const;

   AccountTypeEntry new_account_type();

   void clear_account_type_table();

   AccountTypeEntry new_account_type(const std::string& name);

   void delete_account_type(AccountTypeEntry record);

   const std::string& get_name(AccountTypeEntry record) const;

   void set_name(AccountTypeEntry record, const std::string& name);

   AccountTypeEntry find_account_type_by_name(const std::string& name) const;

   // Methods for interacting with Accounts
   Table<Account> get_account_table() const;

   AccountEntry new_account();

   AccountEntry new_account(const std::string& name, AccountTypeEntry type);

   void clear_account_table();

   void delete_account(AccountEntry record);

   const std::string& get_name(AccountEntry record) const;

   void set_name(AccountEntry record, const std::string& name);

   AccountEntry find_account_by_name(const std::string& name) const;

   AccountTypeEntry get_type(AccountEntry record) const;

   void set_type(AccountEntry record, AccountTypeEntry type);

   AccountEntry find_account_by_type(AccountTypeEntry type) const;

   // Methods for interacting with Transactions
   Table<Transaction> get_transaction_table() const;

   TransactionEntry new_transaction();

   TransactionEntry new_transaction(const date::year_month_day& date, const std::string& memo);

   void clear_transaction_table();

   void delete_transaction(TransactionEntry record);

   const date::year_month_day get_date(TransactionEntry record) const;

   void set_date(TransactionEntry record, const date::year_month_day& date);

   TransactionEntry find_transaction_by_date(const date::year_month_day& date) const;

   const std::string& get_memo(TransactionEntry record) const;

   void set_memo(TransactionEntry record, const std::string& memo);

   TransactionEntry find_transaction_by_memo(const std::string& memo) const;
private:
   template <typename TYPE>
   const ledger::internal::RecordKeeper<TYPE>& get_record_keeper() const;
private:
   ledger::internal::RecordKeeper<Account> account_table;
   ledger::internal::RecordKeeper<AccountType> account_type_table;
   ledger::internal::RecordKeeper<Adjustment> adjustment_table;
   ledger::internal::RecordKeeper<Transaction> transaction_table;
};

#endif // COCLES_LEDGER_INTERNAL_DATABASE_HPP
