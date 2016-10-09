#ifndef tutorial_Database_declared
#define tutorial_Database_declared

#include <cassert>
#include <cstdint>
#include <string>
#include <vector>

#include "Database.h"
#include "Dummy_Listener.h"
#include "File.h"
#include "Freedom_Keeper.h"
#include "Journal_File.h"

namespace tutorial {
class Database;

class city_container;

class city_t {
   friend class Database;
   friend class person_t;
   friend class transaction_t;
   friend class account_type_t;
   friend class account_t;
   friend class adjustment_t;
   friend class city_container;

private:
   record_id_t id;

public:
   explicit city_t(record_id_t id)
      : id(id) {}

   city_t()
      : id(0) {}

   bool
   is_null() const {
      return id == 0;
   }

   record_id_t
   get_id() const {
      return id;
   }

   bool
   operator==(const city_t city) const {
      return id == city.id;
   }
};

struct city_data : public joedb::EmptyRecord {
   city_data() {}

   city_data(bool f)
      : joedb::EmptyRecord(f) {}

   std::string name;
};

class person_container;

class person_t {
   friend class Database;
   friend class city_t;
   friend class transaction_t;
   friend class account_type_t;
   friend class account_t;
   friend class adjustment_t;
   friend class person_container;

private:
   record_id_t id;

public:
   explicit person_t(record_id_t id)
      : id(id) {}
   person_t()
      : id(0) {}
   bool
   is_null() const {
      return id == 0;
   }
   record_id_t
   get_id() const {
      return id;
   }
   bool
   operator==(const person_t person) const {
      return id == person.id;
   }
};

struct person_data : public joedb::EmptyRecord {
   person_data() {}
   person_data(bool f)
      : joedb::EmptyRecord(f) {}
   std::string name;
   city_t home;
};

class transaction_container;

class transaction_t {
   friend class Database;
   friend class city_t;
   friend class person_t;
   friend class account_type_t;
   friend class account_t;
   friend class adjustment_t;
   friend class transaction_container;

private:
   record_id_t id;

public:
   explicit transaction_t(record_id_t id)
      : id(id) {}
   transaction_t()
      : id(0) {}
   bool
   is_null() const {
      return id == 0;
   }
   record_id_t
   get_id() const {
      return id;
   }
   bool
   operator==(const transaction_t transaction) const {
      return id == transaction.id;
   }
};

struct transaction_data : public joedb::EmptyRecord {
   transaction_data() {}
   transaction_data(bool f)
      : joedb::EmptyRecord(f) {}
   std::string date;
   std::string memo;
};

class account_type_container;

class account_type_t {
   friend class Database;
   friend class city_t;
   friend class person_t;
   friend class transaction_t;
   friend class account_t;
   friend class adjustment_t;
   friend class account_type_container;

private:
   record_id_t id;

public:
   explicit account_type_t(record_id_t id)
      : id(id) {}
   account_type_t()
      : id(0) {}
   bool
   is_null() const {
      return id == 0;
   }
   record_id_t
   get_id() const {
      return id;
   }
   bool
   operator==(const account_type_t account_type) const {
      return id == account_type.id;
   }
};

struct account_type_data : public joedb::EmptyRecord {
   account_type_data() {}
   account_type_data(bool f)
      : joedb::EmptyRecord(f) {}
   std::string name;
};

class account_container;

class account_t {
   friend class Database;
   friend class city_t;
   friend class person_t;
   friend class transaction_t;
   friend class account_type_t;
   friend class adjustment_t;
   friend class account_container;

private:
   record_id_t id;

public:
   explicit account_t(record_id_t id)
      : id(id) {}
   account_t()
      : id(0) {}
   bool
   is_null() const {
      return id == 0;
   }
   record_id_t
   get_id() const {
      return id;
   }
   bool
   operator==(const account_t account) const {
      return id == account.id;
   }
};

struct account_data : public joedb::EmptyRecord {
   account_data() {}
   account_data(bool f)
      : joedb::EmptyRecord(f) {}
   std::string name;
   account_type_t type;
};

class adjustment_container;

class adjustment_t {
   friend class Database;
   friend class city_t;
   friend class person_t;
   friend class transaction_t;
   friend class account_type_t;
   friend class account_t;
   friend class adjustment_container;

private:
   record_id_t id;

public:
   explicit adjustment_t(record_id_t id)
      : id(id) {}
   adjustment_t()
      : id(0) {}
   bool
   is_null() const {
      return id == 0;
   }
   record_id_t
   get_id() const {
      return id;
   }
   bool
   operator==(const adjustment_t adjustment) const {
      return id == adjustment.id;
   }
};

struct adjustment_data : public joedb::EmptyRecord {
   adjustment_data() {}
   adjustment_data(bool f)
      : joedb::EmptyRecord(f) {}
   std::string name;
   account_t account;
   transaction_t transaction;
};

class Database : public joedb::Listener {
   friend class city_t;
   friend class city_container;
   friend class person_t;
   friend class person_container;
   friend class transaction_t;
   friend class transaction_container;
   friend class account_type_t;
   friend class account_type_container;
   friend class account_t;
   friend class account_container;
   friend class adjustment_t;
   friend class adjustment_container;

private:
   joedb::Dummy_Listener dummy_listener;
   joedb::Listener* listener;

   joedb::Freedom_Keeper<city_data> city_FK;
   joedb::Freedom_Keeper<person_data> person_FK;
   joedb::Freedom_Keeper<transaction_data> transaction_FK;
   joedb::Freedom_Keeper<account_type_data> account_type_FK;
   joedb::Freedom_Keeper<account_data> account_FK;
   joedb::Freedom_Keeper<adjustment_data> adjustment_FK;

   void
   after_delete(table_id_t table_id, record_id_t record_id) override {
      if (table_id == 1)
         city_FK.free(record_id + 1);
      else if (table_id == 2)
         person_FK.free(record_id + 1);
      else if (table_id == 3)
         transaction_FK.free(record_id + 1);
      else if (table_id == 4)
         account_type_FK.free(record_id + 1);
      else if (table_id == 5)
         account_FK.free(record_id + 1);
      else if (table_id == 6)
         adjustment_FK.free(record_id + 1);
   }

   void
   after_insert(table_id_t table_id, record_id_t record_id) override {
      if (table_id == 1) {
         while (city_FK.size() < record_id)
            city_FK.push_back();
         city_FK.use(record_id + 1);
      } else if (table_id == 2) {
         while (person_FK.size() < record_id)
            person_FK.push_back();
         person_FK.use(record_id + 1);
      } else if (table_id == 3) {
         while (transaction_FK.size() < record_id)
            transaction_FK.push_back();
         transaction_FK.use(record_id + 1);
      } else if (table_id == 4) {
         while (account_type_FK.size() < record_id)
            account_type_FK.push_back();
         account_type_FK.use(record_id + 1);
      } else if (table_id == 5) {
         while (account_FK.size() < record_id)
            account_FK.push_back();
         account_FK.use(record_id + 1);
      } else if (table_id == 6) {
         while (adjustment_FK.size() < record_id)
            adjustment_FK.push_back();
         adjustment_FK.use(record_id + 1);
      }
   }

   void
   after_update_string(table_id_t table_id, record_id_t record_id,
                       field_id_t field_id, const std::string& value) override {
      if (table_id == 1) {
         if (field_id == 1) {
            city_FK.get_record(record_id + 1).name = value;
            return;
         }
         return;
      }
      if (table_id == 2) {
         if (field_id == 1) {
            person_FK.get_record(record_id + 1).name = value;
            return;
         }
         return;
      }
      if (table_id == 3) {
         if (field_id == 1) {
            transaction_FK.get_record(record_id + 1).date = value;
            return;
         }
         if (field_id == 2) {
            transaction_FK.get_record(record_id + 1).memo = value;
            return;
         }
         return;
      }
      if (table_id == 4) {
         if (field_id == 1) {
            account_type_FK.get_record(record_id + 1).name = value;
            return;
         }
         return;
      }
      if (table_id == 5) {
         if (field_id == 1) {
            account_FK.get_record(record_id + 1).name = value;
            return;
         }
         return;
      }
      if (table_id == 6) {
         if (field_id == 1) {
            adjustment_FK.get_record(record_id + 1).name = value;
            return;
         }
         return;
      }
   }

   void
   after_update_int32(table_id_t table_id, record_id_t record_id,
                      field_id_t field_id, int32_t value) override {}

   void
   after_update_int64(table_id_t table_id, record_id_t record_id,
                      field_id_t field_id, int64_t value) override {}

   void
   after_update_reference(table_id_t table_id, record_id_t record_id,
                          field_id_t field_id, record_id_t value) override {
      if (table_id == 2) {
         if (field_id == 2) {
            person_FK.get_record(record_id + 1).home = city_t(value);
            return;
         }
         return;
      }
      if (table_id == 5) {
         if (field_id == 2) {
            account_FK.get_record(record_id + 1).type = account_type_t(value);
            return;
         }
         return;
      }
      if (table_id == 6) {
         if (field_id == 2) {
            adjustment_FK.get_record(record_id + 1).account = account_t(value);
            return;
         }
         if (field_id == 3) {
            adjustment_FK.get_record(record_id + 1).transaction =
                transaction_t(value);
            return;
         }
         return;
      }
   }

   void
   after_update_boolean(table_id_t table_id, record_id_t record_id,
                        field_id_t field_id, bool value) override {}

   void
   after_update_float32(table_id_t table_id, record_id_t record_id,
                        field_id_t field_id, float value) override {}

   void
   after_update_float64(table_id_t table_id, record_id_t record_id,
                        field_id_t field_id, double value) override {}

public:
   Database()
      : listener(&dummy_listener) {}

   void set_listener(Listener& new_listener) {
      listener = &new_listener;
   }

   void clear_listener() {
      listener = &dummy_listener;
   }

   void after_create_table(const std::string& name) override {}

   void after_drop_table(table_id_t table_id) override {}

   void after_add_field(table_id_t table_id, const std::string& name, joedb::Type type) override {}

   void after_drop_field(table_id_t table_id, field_id_t field_id) override {}

   city_container get_city_table() const;

   city_t new_city() {
      city_t result(city_FK.allocate() - 1);
      listener->after_insert(1, result.id);
      return result;
   }

   void clear_city_table();

   city_t new_city(const std::string& name) {
      city_t result(city_FK.allocate() - 1);
      listener->after_insert(1, result.id);
      city_FK.get_record(result.id + 1).name = name;
      listener->after_update_string(1, result.id, 1, name);
      return result;
   }

   void delete_city(city_t record) {
      city_FK.free(record.id + 1);
      listener->after_delete(1, record.id);
   }

   const std::string& get_name(city_t record) const {
      assert(!record.is_null());
      return city_FK.get_record(record.id + 1).name;
   }

   void set_name(city_t record, const std::string& name) {
      assert(!record.is_null());
      city_FK.get_record(record.id + 1).name = name;
      listener->after_update_string(1, record.id, 1, name);
   }

   city_t find_city_by_name(const std::string& name) const;

   person_container get_person_table() const;

   person_t new_person() {
      person_t result(person_FK.allocate() - 1);
      listener->after_insert(2, result.id);
      return result;
   }

   void clear_person_table();

   person_t new_person(const std::string& name, city_t home) {
      person_t result(person_FK.allocate() - 1);
      listener->after_insert(2, result.id);
      person_FK.get_record(result.id + 1).name = name;
      listener->after_update_string(2, result.id, 1, name);
      person_FK.get_record(result.id + 1).home = home;
      listener->after_update_reference(2, result.id, 2, home.id);
      return result;
   }

   void delete_person(person_t record) {
      person_FK.free(record.id + 1);
      listener->after_delete(2, record.id);
   }

   const std::string& get_name(person_t record) const {
      assert(!record.is_null());
      return person_FK.get_record(record.id + 1).name;
   }

   void set_name(person_t record, const std::string& name) {
      assert(!record.is_null());
      person_FK.get_record(record.id + 1).name = name;
      listener->after_update_string(2, record.id, 1, name);
   }

   person_t find_person_by_name(const std::string& name) const;

   city_t get_home(person_t record) const {
      assert(!record.is_null());
      return person_FK.get_record(record.id + 1).home;
   }

   void set_home(person_t record, city_t home) {
      assert(!record.is_null());
      person_FK.get_record(record.id + 1).home = home;
      listener->after_update_reference(2, record.id, 2, home.id);
   }

   person_t find_person_by_home(city_t home) const;

   transaction_container get_transaction_table() const;

   transaction_t new_transaction() {
      transaction_t result(transaction_FK.allocate() - 1);
      listener->after_insert(3, result.id);
      return result;
   }

   void clear_transaction_table();

   transaction_t new_transaction(const std::string& date, const std::string& memo) {
      transaction_t result(transaction_FK.allocate() - 1);
      listener->after_insert(3, result.id);
      transaction_FK.get_record(result.id + 1).date = date;
      listener->after_update_string(3, result.id, 1, date);
      transaction_FK.get_record(result.id + 1).memo = memo;
      listener->after_update_string(3, result.id, 2, memo);
      return result;
   }

   void
   delete_transaction(transaction_t record) {
      transaction_FK.free(record.id + 1);
      listener->after_delete(3, record.id);
   }

   const std::string& get_date(transaction_t record) const {
      assert(!record.is_null());
      return transaction_FK.get_record(record.id + 1).date;
   }

   void set_date(transaction_t record, const std::string& date) {
      assert(!record.is_null());
      transaction_FK.get_record(record.id + 1).date = date;
      listener->after_update_string(3, record.id, 1, date);
   }

   transaction_t find_transaction_by_date(const std::string& date) const;

   const std::string& get_memo(transaction_t record) const {
      assert(!record.is_null());
      return transaction_FK.get_record(record.id + 1).memo;
   }

   void set_memo(transaction_t record, const std::string& memo) {
      assert(!record.is_null());
      transaction_FK.get_record(record.id + 1).memo = memo;
      listener->after_update_string(3, record.id, 2, memo);
   }

   transaction_t find_transaction_by_memo(const std::string& memo) const;

   account_type_container get_account_type_table() const;

   account_type_t new_account_type() {
      account_type_t result(account_type_FK.allocate() - 1);
      listener->after_insert(4, result.id);
      return result;
   }

   void clear_account_type_table();

   account_type_t new_account_type(const std::string& name) {
      account_type_t result(account_type_FK.allocate() - 1);
      listener->after_insert(4, result.id);
      account_type_FK.get_record(result.id + 1).name = name;
      listener->after_update_string(4, result.id, 1, name);
      return result;
   }

   void
   delete_account_type(account_type_t record) {
      account_type_FK.free(record.id + 1);
      listener->after_delete(4, record.id);
   }

   const std::string& get_name(account_type_t record) const {
      assert(!record.is_null());
      return account_type_FK.get_record(record.id + 1).name;
   }

   void set_name(account_type_t record, const std::string& name) {
      assert(!record.is_null());
      account_type_FK.get_record(record.id + 1).name = name;
      listener->after_update_string(4, record.id, 1, name);
   }

   account_type_t find_account_type_by_name(const std::string& name) const;

   account_container get_account_table() const;

   account_t new_account() {
      account_t result(account_FK.allocate() - 1);
      listener->after_insert(5, result.id);
      return result;
   }

   void clear_account_table();

   account_t new_account(const std::string& name, account_type_t type) {
      account_t result(account_FK.allocate() - 1);
      listener->after_insert(5, result.id);
      account_FK.get_record(result.id + 1).name = name;
      listener->after_update_string(5, result.id, 1, name);
      account_FK.get_record(result.id + 1).type = type;
      listener->after_update_reference(5, result.id, 2, type.id);
      return result;
   }

   void delete_account(account_t record) {
      account_FK.free(record.id + 1);
      listener->after_delete(5, record.id);
   }

   const std::string& get_name(account_t record) const {
      assert(!record.is_null());
      return account_FK.get_record(record.id + 1).name;
   }

   void set_name(account_t record, const std::string& name) {
      assert(!record.is_null());
      account_FK.get_record(record.id + 1).name = name;
      listener->after_update_string(5, record.id, 1, name);
   }

   account_t find_account_by_name(const std::string& name) const;

   account_type_t get_type(account_t record) const {
      assert(!record.is_null());
      return account_FK.get_record(record.id + 1).type;
   }

   void set_type(account_t record, account_type_t type) {
      assert(!record.is_null());
      account_FK.get_record(record.id + 1).type = type;
      listener->after_update_reference(5, record.id, 2, type.id);
   }

   account_t find_account_by_type(account_type_t type) const;

   adjustment_container
   get_adjustment_table() const;
   adjustment_t
   new_adjustment() {
      adjustment_t result(adjustment_FK.allocate() - 1);
      listener->after_insert(6, result.id);
      return result;
   }

   void clear_adjustment_table();

   adjustment_t new_adjustment(const std::string& name, account_t account, transaction_t transaction) {
      adjustment_t result(adjustment_FK.allocate() - 1);
      listener->after_insert(6, result.id);
      adjustment_FK.get_record(result.id + 1).name = name;
      listener->after_update_string(6, result.id, 1, name);
      adjustment_FK.get_record(result.id + 1).account = account;
      listener->after_update_reference(6, result.id, 2, account.id);
      adjustment_FK.get_record(result.id + 1).transaction = transaction;
      listener->after_update_reference(6, result.id, 3, transaction.id);
      return result;
   }

   void delete_adjustment(adjustment_t record) {
      adjustment_FK.free(record.id + 1);
      listener->after_delete(6, record.id);
   }

   const std::string& get_name(adjustment_t record) const {
      assert(!record.is_null());
      return adjustment_FK.get_record(record.id + 1).name;
   }

   void set_name(adjustment_t record, const std::string& name) {
      assert(!record.is_null());
      adjustment_FK.get_record(record.id + 1).name = name;
      listener->after_update_string(6, record.id, 1, name);
   }

   adjustment_t find_adjustment_by_name(const std::string& name) const;

   account_t get_account(adjustment_t record) const {
      assert(!record.is_null());
      return adjustment_FK.get_record(record.id + 1).account;
   }

   void set_account(adjustment_t record, account_t account) {
      assert(!record.is_null());
      adjustment_FK.get_record(record.id + 1).account = account;
      listener->after_update_reference(6, record.id, 2, account.id);
   }

   adjustment_t find_adjustment_by_account(account_t account) const;

   transaction_t get_transaction(adjustment_t record) const {
      assert(!record.is_null());
      return adjustment_FK.get_record(record.id + 1).transaction;
   }

   void set_transaction(adjustment_t record, transaction_t transaction) {
      assert(!record.is_null());
      adjustment_FK.get_record(record.id + 1).transaction = transaction;
      listener->after_update_reference(6, record.id, 3, transaction.id);
   }

   adjustment_t find_adjustment_by_transaction(transaction_t transaction) const;
};

class File_Database : public Database {
private:
   joedb::File file;
   joedb::Journal_File journal;

public:
   File_Database(const char* file_name, bool read_only = false)
      : file(file_name, read_only ? joedb::File::mode_t::read_existing
                                  : joedb::File::mode_t::write_existing)
      , journal(file) {
      if (is_good())
         journal.replay_log(*this);
      else if (file.get_status() == joedb::File::status_t::failure &&
               !read_only) {
         file.open(file_name, joedb::File::mode_t::create_new);
         if (file.get_status() == joedb::File::status_t::success) {
            journal.~Journal_File();
            new (&journal) joedb::Journal_File(file);
            journal.after_create_table("city");
            journal.after_add_field(1, "name", joedb::Type::string());
            journal.after_create_table("person");
            journal.after_add_field(2, "name", joedb::Type::string());
            journal.after_add_field(2, "home", joedb::Type::reference(1));
            journal.after_create_table("transaction");
            journal.after_add_field(3, "date", joedb::Type::string());
            journal.after_add_field(3, "memo", joedb::Type::string());
            journal.after_create_table("account_type");
            journal.after_add_field(4, "name", joedb::Type::string());
            journal.after_create_table("account");
            journal.after_add_field(5, "name", joedb::Type::string());
            journal.after_add_field(5, "type", joedb::Type::reference(4));
            journal.after_create_table("adjustment");
            journal.after_add_field(6, "name", joedb::Type::string());
            journal.after_add_field(6, "account", joedb::Type::reference(5));
            journal.after_add_field(6,
                                    "transaction",
                                    joedb::Type::reference(3));
         }
      }
      set_listener(journal);
   }

   joedb::Journal_File::state_t
   get_journal_state() const {
      return journal.get_state();
   }

   void
   commit() {
      file.commit();
   }
   void
   checkpoint() {
      journal.checkpoint();
   }
   void
   safe_commit() {
      file.commit();
      journal.checkpoint();
      file.commit();
   }
   bool
   is_good() const {
      return file.get_status() == joedb::File::status_t::success &&
             journal.get_state() == joedb::Journal_File::state_t::no_error;
   }
};

class city_container {
   friend class Database;

private:
   const Database& db;
   city_container(const Database& db)
      : db(db) {}

public:
   class iterator {
      friend class city_container;

   private:
      const joedb::Freedom_Keeper<city_data>& fk;
      size_t index;
      iterator(const joedb::Freedom_Keeper<city_data>& fk)
         : fk(fk)
         , index(0) {}

   public:
      bool
      operator!=(const iterator& i) const {
         return index != i.index;
      }
      iterator& operator++() {
         index = fk.get_next(index);
         return *this;
      }
      city_t operator*() { return city_t(index - 1); }
   };

   iterator
   begin() {
      return ++iterator(db.city_FK);
   }
   iterator
   end() {
      return iterator(db.city_FK);
   }
   bool
   is_empty() const {
      return db.city_FK.is_empty();
   }
   size_t
   get_size() const {
      return db.city_FK.get_used_count();
   }
   static city_t
   get_at(size_t i) {
      return city_t(i);
   }
   bool
   is_valid_at(size_t i) {
      return db.city_FK.is_used(i + 1);
   }
};

inline city_container
Database::get_city_table() const {
   return city_container(*this);
}

inline void
Database::clear_city_table() {
   while (!get_city_table().is_empty())
      delete_city(*get_city_table().begin());
}

inline city_t
Database::find_city_by_name(const std::string& name) const {
   for (auto city : get_city_table())
      if (get_name(city) == name)
         return city;
   return city_t(0);
}

class person_container {
   friend class Database;

private:
   const Database& db;
   person_container(const Database& db)
      : db(db) {}

public:
   class iterator {
      friend class person_container;

   private:
      const joedb::Freedom_Keeper<person_data>& fk;
      size_t index;
      iterator(const joedb::Freedom_Keeper<person_data>& fk)
         : fk(fk)
         , index(0) {}

   public:
      bool
      operator!=(const iterator& i) const {
         return index != i.index;
      }
      iterator& operator++() {
         index = fk.get_next(index);
         return *this;
      }
      person_t operator*() { return person_t(index - 1); }
   };

   iterator
   begin() {
      return ++iterator(db.person_FK);
   }
   iterator
   end() {
      return iterator(db.person_FK);
   }
   bool
   is_empty() const {
      return db.person_FK.is_empty();
   }
   size_t
   get_size() const {
      return db.person_FK.get_used_count();
   }
   static person_t
   get_at(size_t i) {
      return person_t(i);
   }
   bool
   is_valid_at(size_t i) {
      return db.person_FK.is_used(i + 1);
   }
};

inline person_container
Database::get_person_table() const {
   return person_container(*this);
}

inline void
Database::clear_person_table() {
   while (!get_person_table().is_empty())
      delete_person(*get_person_table().begin());
}

inline person_t
Database::find_person_by_name(const std::string& name) const {
   for (auto person : get_person_table())
      if (get_name(person) == name)
         return person;
   return person_t(0);
}

inline person_t
Database::find_person_by_home(city_t home) const {
   for (auto person : get_person_table())
      if (get_home(person) == home)
         return person;
   return person_t(0);
}

class transaction_container {
   friend class Database;

private:
   const Database& db;
   transaction_container(const Database& db)
      : db(db) {}

public:
   class iterator {
      friend class transaction_container;

   private:
      const joedb::Freedom_Keeper<transaction_data>& fk;
      size_t index;
      iterator(const joedb::Freedom_Keeper<transaction_data>& fk)
         : fk(fk)
         , index(0) {}

   public:
      bool
      operator!=(const iterator& i) const {
         return index != i.index;
      }
      iterator& operator++() {
         index = fk.get_next(index);
         return *this;
      }
      transaction_t operator*() { return transaction_t(index - 1); }
   };

   iterator
   begin() {
      return ++iterator(db.transaction_FK);
   }
   iterator
   end() {
      return iterator(db.transaction_FK);
   }
   bool
   is_empty() const {
      return db.transaction_FK.is_empty();
   }
   size_t
   get_size() const {
      return db.transaction_FK.get_used_count();
   }
   static transaction_t
   get_at(size_t i) {
      return transaction_t(i);
   }
   bool
   is_valid_at(size_t i) {
      return db.transaction_FK.is_used(i + 1);
   }
};

inline transaction_container
Database::get_transaction_table() const {
   return transaction_container(*this);
}

inline void
Database::clear_transaction_table() {
   while (!get_transaction_table().is_empty())
      delete_transaction(*get_transaction_table().begin());
}

inline transaction_t
Database::find_transaction_by_date(const std::string& date) const {
   for (auto transaction : get_transaction_table())
      if (get_date(transaction) == date)
         return transaction;
   return transaction_t(0);
}

inline transaction_t
Database::find_transaction_by_memo(const std::string& memo) const {
   for (auto transaction : get_transaction_table())
      if (get_memo(transaction) == memo)
         return transaction;
   return transaction_t(0);
}

class account_type_container {
   friend class Database;

private:
   const Database& db;
   account_type_container(const Database& db)
      : db(db) {}

public:
   class iterator {
      friend class account_type_container;

   private:
      const joedb::Freedom_Keeper<account_type_data>& fk;
      size_t index;
      iterator(const joedb::Freedom_Keeper<account_type_data>& fk)
         : fk(fk)
         , index(0) {}

   public:
      bool
      operator!=(const iterator& i) const {
         return index != i.index;
      }
      iterator& operator++() {
         index = fk.get_next(index);
         return *this;
      }
      account_type_t operator*() { return account_type_t(index - 1); }
   };

   iterator
   begin() {
      return ++iterator(db.account_type_FK);
   }
   iterator
   end() {
      return iterator(db.account_type_FK);
   }
   bool
   is_empty() const {
      return db.account_type_FK.is_empty();
   }
   size_t
   get_size() const {
      return db.account_type_FK.get_used_count();
   }
   static account_type_t
   get_at(size_t i) {
      return account_type_t(i);
   }
   bool
   is_valid_at(size_t i) {
      return db.account_type_FK.is_used(i + 1);
   }
};

inline account_type_container
Database::get_account_type_table() const {
   return account_type_container(*this);
}

inline void
Database::clear_account_type_table() {
   while (!get_account_type_table().is_empty())
      delete_account_type(*get_account_type_table().begin());
}

inline account_type_t
Database::find_account_type_by_name(const std::string& name) const {
   for (auto account_type : get_account_type_table())
      if (get_name(account_type) == name)
         return account_type;
   return account_type_t(0);
}

class account_container {
   friend class Database;

private:
   const Database& db;
   account_container(const Database& db)
      : db(db) {}

public:
   class iterator {
      friend class account_container;

   private:
      const joedb::Freedom_Keeper<account_data>& fk;
      size_t index;
      iterator(const joedb::Freedom_Keeper<account_data>& fk)
         : fk(fk)
         , index(0) {}

   public:
      bool
      operator!=(const iterator& i) const {
         return index != i.index;
      }
      iterator& operator++() {
         index = fk.get_next(index);
         return *this;
      }
      account_t operator*() { return account_t(index - 1); }
   };

   iterator begin() {
      return ++iterator(db.account_FK);
   }
   iterator end() {
      return iterator(db.account_FK);
   }
   bool is_empty() const {
      return db.account_FK.is_empty();
   }
   size_t get_size() const {
      return db.account_FK.get_used_count();
   }
   static account_t get_at(size_t i) {
      return account_t(i);
   }
   bool is_valid_at(size_t i) {
      return db.account_FK.is_used(i + 1);
   }
};

inline account_container
Database::get_account_table() const {
   return account_container(*this);
}

inline void
Database::clear_account_table() {
   while (!get_account_table().is_empty())
      delete_account(*get_account_table().begin());
}

inline account_t
Database::find_account_by_name(const std::string& name) const {
   for (auto account : get_account_table())
      if (get_name(account) == name)
         return account;
   return account_t(0);
}

inline account_t
Database::find_account_by_type(account_type_t type) const {
   for (auto account : get_account_table())
      if (get_type(account) == type)
         return account;
   return account_t(0);
}

class adjustment_container {
   friend class Database;

private:
   const Database& db;
   adjustment_container(const Database& db)
      : db(db) {}

public:
   class iterator {
      friend class adjustment_container;

   private:
      const joedb::Freedom_Keeper<adjustment_data>& fk;
      size_t index;
      iterator(const joedb::Freedom_Keeper<adjustment_data>& fk)
         : fk(fk)
         , index(0) {}

   public:
      bool
      operator!=(const iterator& i) const {
         return index != i.index;
      }
      iterator& operator++() {
         index = fk.get_next(index);
         return *this;
      }
      adjustment_t operator*() { return adjustment_t(index - 1); }
   };

   iterator
   begin() {
      return ++iterator(db.adjustment_FK);
   }
   iterator
   end() {
      return iterator(db.adjustment_FK);
   }
   bool
   is_empty() const {
      return db.adjustment_FK.is_empty();
   }
   size_t
   get_size() const {
      return db.adjustment_FK.get_used_count();
   }
   static adjustment_t
   get_at(size_t i) {
      return adjustment_t(i);
   }
   bool
   is_valid_at(size_t i) {
      return db.adjustment_FK.is_used(i + 1);
   }
};

inline adjustment_container
Database::get_adjustment_table() const {
   return adjustment_container(*this);
}

inline void
Database::clear_adjustment_table() {
   while (!get_adjustment_table().is_empty())
      delete_adjustment(*get_adjustment_table().begin());
}

inline adjustment_t
Database::find_adjustment_by_name(const std::string& name) const {
   for (auto adjustment : get_adjustment_table())
      if (get_name(adjustment) == name)
         return adjustment;
   return adjustment_t(0);
}

inline adjustment_t
Database::find_adjustment_by_account(account_t account) const {
   for (auto adjustment : get_adjustment_table())
      if (get_account(adjustment) == account)
         return adjustment;
   return adjustment_t(0);
}

inline adjustment_t
Database::find_adjustment_by_transaction(transaction_t transaction) const {
   for (auto adjustment : get_adjustment_table())
      if (get_transaction(adjustment) == transaction)
         return adjustment;
   return adjustment_t(0);
}
}

#endif
