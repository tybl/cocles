#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

#include <algorithm>
#include <chrono>
#include <iostream>

static int run_unit_tests(int argc, const char* argv[]) {
   doctest::Context context; // initialize

   // defaults
   context.addFilter("test-case-exclude", "*math*"); // exclude test cases with "math" in their name
   context.setOption("abort-after", 5);              // stop test execution after 5 failed assertions
   context.setOption("sort", "name");                // sort the test cases by their name

   context.applyCommandLine(argc, argv);

   // overrides
   context.setOption("no-breaks", true);             // don't break in the debugger when assertions fail

   int result = context.run();                       // run

   if (context.shouldExit()) {          // important !! query flags (and --exit) rely on the user doing this
      exit(result);                                  // propagate the result of the tests
   }
   return result;
}

#if 0
struct event_t {

   event_t() noexcept
      : m_time(std::chrono::high_resolution_clock::now()) {}

private:
   std::chrono::high_resolution_clock::time_point m_time;
};

struct add_account_event_t
   : public event_t
   , public account_t
{

   add_account_event_t(const std::string &name, account_type_t type)
      : event_t()
      , account_t(name, type) {}

}; // struct add_account_event_t

struct add_transaction_event_t
   : public event_t
   , public transaction_t
{

   add_transaction_event_t(const std::string &date)
      : event_t()
      , transaction_t(date) {}

}; // add_transaction_event_t
#endif

template <typename TYPE>
struct identifier_t {

   constexpr explicit identifier_t(std::size_t value) noexcept
      : m_value(value) {}

   bool operator==(const identifier_t& other) const noexcept {
      return (m_value == other.m_value);
   }

   bool operator!=(const identifier_t& other) const noexcept {
      return !operator==(other);
   }

   explicit operator std::size_t() const noexcept {
      return m_value;
   }

   bool operator<(const identifier_t& other) const noexcept {
      return (m_value < other.m_value);
   }

private:
   std::size_t m_value;
};

template <typename TYPE>
struct table_t {

   using identifier_type = identifier_t<TYPE>;
   using value_type = TYPE;
   using container_type = std::vector<TYPE>;
   using size_type = typename std::vector<TYPE>::size_type;

   identifier_type insert(TYPE entry) {
      size_type pos = m_entries.size();
      m_entries.push_back(entry);
      return identifier_type(pos);
   }

   TYPE remove(identifier_type id) {
      size_type index = static_cast<size_type>(id);
      TYPE result = m_entries.at(index);
      m_entries.erase(m_entries.begin() + index);
      return result;
   }

   size_type size() const {
      return m_entries.size();
   }

private:
   std::vector<TYPE> m_entries;
}; // struct table_t

enum class account_type_t {
   INCOME_EXPENSE,
   BUDGET_CATEGORY,
   BUDGETED_ACCOUNT,
   UNBUDGETED_ACCOUNT
};

struct account_t {

   account_t(std::string name, account_type_t type)
      : m_name(name)
      , m_type(type) {}

   const std::string& name() const {
      return m_name;
   }

   account_type_t type() const {
      return m_type;
   }

   bool operator<(const account_t& other) const {
      return (m_name < other.m_name);
   }

private:
   std::string m_name;
   account_type_t m_type;
}; // struct account_t

struct transaction_t {

   transaction_t(const std::string& date, const std::string& memo = "")
      : transaction_t(identifier_t<transaction_t>(++max_id), date, memo) {}

   transaction_t(identifier_t<transaction_t> id, const std::string& date, const std::string& memo)
      : m_id(id)
      , m_date(date)
      , m_memo(memo) {}

   const std::string& date() const {
      return m_date;
   }

   bool operator<(const transaction_t& other) const noexcept {
      return (m_id < other.m_id);
   }

private:
   identifier_t<transaction_t> m_id;
   std::string m_date;
   std::string m_memo;
   static std::size_t max_id;
}; // struct transaction_t

std::size_t transaction_t::max_id = 0;

struct adjustment_t {
   using transaction_id_t = table_t<transaction_t>::identifier_type;
   using account_id_t = table_t<account_t>::identifier_type;

   adjustment_t(transaction_id_t transaction_id, account_id_t account_id)
      : m_transaction_id(transaction_id)
      , m_account_id(account_id) {}

private:
   transaction_id_t m_transaction_id;
   account_id_t m_account_id;
   std::string m_amount;
}; // struct adjustment_t

struct ledger_t {
   table_t<transaction_t> transaction_table;
   table_t<account_t>         account_table;
   table_t<adjustment_t>   adjustment_table;

#if 0
   template <typename ... TYPES>
   std::vector<std::tuple<TYPES...>> select(std::function<std::tuple<TYPES...>(const stable_table_t<transaction_t>& transactions,
                                                                               const stable_table_t<account_t>& accounts,
                                                                               const table_t<adjustment_t>& adjustments))
#endif
};

extern "C" int main(int argc, const char* argv[]) {
   int unit_test_results = run_unit_tests(argc, argv);

   ledger_t ledger;
   ledger.account_table.insert({"Starting Balance", account_type_t::UNBUDGETED_ACCOUNT});
   auto aid001 = ledger.account_table.insert({"Checking", account_type_t::BUDGETED_ACCOUNT});
   ledger.account_table.insert({"Savings", account_type_t::BUDGETED_ACCOUNT});
   ledger.account_table.insert({"Groceries", account_type_t::BUDGET_CATEGORY});
   ledger.account_table.insert({"Wegmans", account_type_t::INCOME_EXPENSE});
   ledger.account_table.insert({"Walmart", account_type_t::INCOME_EXPENSE});
   auto tid001 = ledger.transaction_table.insert({"2016-11-14"});
   ledger.adjustment_table.insert({tid001, aid001});

   auto tid = ledger.transaction_table.insert({ "1999-12-31" });
   auto aid = ledger.account_table.insert({ "Checking", account_type_t::INCOME_EXPENSE });
   ledger.adjustment_table.insert({ tid, aid });
   std::cout << ledger.adjustment_table.size() << std::endl;
   return unit_test_results; // the result from doctest is propagated here as well
}
