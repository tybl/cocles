#include "Database.hpp"

#include "TransactionTable.hpp"

TransactionTable Database::get_transaction_table() const {
   return TransactionTable(*this);
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

#if 0
TEST() {
   Database db;
   auto first_trans = db.new_transaction();
   std::string input = "Hello world!";
   db.set_memo(first_trans, input);
   std::cout << db.get_memo(first_trans) << std::endl;
}
#endif
