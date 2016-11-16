#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include "date/date.h"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <iostream>
#include <map>

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
std::ostream& operator<<(std::ostream& out, const identifier_t<TYPE>& id) {
   return out << static_cast<std::size_t>(id);
}

template <typename TYPE>
struct table_t {

   using container_type = std::map<identifier_t<TYPE>, TYPE>;
   using mapped_type    = typename container_type::mapped_type;
   using key_type       = typename container_type::key_type;
   using size_type      = typename container_type::size_type;
   using value_type     = typename container_type::value_type;
   using reference      = typename container_type::reference;
   using const_reference = typename container_type::const_reference;
   using iterator       = typename container_type::iterator;
   using const_iterator = typename container_type::const_iterator;

   table_t()
      : m_max_id() {}

   key_type insert(TYPE entry) {
      key_type ret_val(++m_max_id);
      m_entries.insert(std::make_pair(ret_val, entry));
      return ret_val;
   }

   void remove(key_type key) noexcept {
      const auto count = m_entries.erase(key);
      assert(1 == count);
   }

   size_type size() const noexcept {
      return m_entries.size();
   }

   mapped_type& at(const key_type& key) {
      return m_entries.at(key);
   }

   const mapped_type& at(const key_type& key) const {
      return m_entries.at(key);
   }

   size_type count(const key_type& key) const {
      return m_entries.count(key);
   }

   iterator begin() noexcept {
      return m_entries.begin();
   }

   const_iterator cbegin() const noexcept {
      return m_entries.cbegin();
   }

   iterator end() noexcept {
      return m_entries.end();
   }

   const_iterator cend() const noexcept {
      return m_entries.cend();
   }

private:
   container_type m_entries;
   std::size_t m_max_id;
}; // struct table_t

enum class account_type_t {
   INCOME_EXPENSE,
   BUDGET_CATEGORY,
   BUDGETED_ACCOUNT,
   UNBUDGETED_ACCOUNT
}; // enum class account_type_t

struct account_t {

   account_t(std::string name, account_type_t type)
      : m_name(name)
      , m_type(type) {}

   const std::string& name() const noexcept {
      return m_name;
   }

   account_type_t type() const noexcept {
      return m_type;
   }

private:
   std::string m_name;
   account_type_t m_type;
}; // struct account_t

struct transaction_t {

   transaction_t(const date::year_month_day& date, const std::string& memo = "")
      : m_date(date)
      , m_memo(memo) {}

   const date::year_month_day& date() const noexcept {
      return m_date;
   }

   const std::string& memo() const noexcept {
      return m_memo;
   }

private:
   date::year_month_day m_date;
   std::string m_memo;
}; // struct transaction_t

struct adjustment_t {
   using transaction_id_t = identifier_t<transaction_t>;
   using account_id_t = identifier_t<account_t>;

   adjustment_t(transaction_id_t transaction_id, account_id_t account_id, const std::string& amount)
      : m_transaction_id(transaction_id)
      , m_account_id(account_id)
      , m_amount(amount) {}

   const std::string& amount() const {
      return m_amount;
   }

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
   using namespace std::literals;
   int unit_test_results = run_unit_tests(argc, argv);

   ledger_t ledger;
   ledger.account_table.insert({"Checking", account_type_t::BUDGETED_ACCOUNT});

   // TODO(tblyons): Add information about event type
   auto input = "1479263536123456\t2016-11-15\"Starting Balances\"1\t501318\t100"s;
   //auto input = "2016-11-15\"Starting Balances\"1\t501318\t100"s;
   std::size_t start = 0;
   std::size_t end = input.find('\t', start);
   std::chrono::system_clock::time_point time(std::chrono::microseconds(std::stoull(input.substr(start, end - start))));
   start = end + 1;
   end = input.find('-', start);
   date::year year = date::year(std::stoi(input.substr(start, end - start)));
   start = end + 1;
   end = input.find('-', start);
   date::month month = date::month(static_cast<uint32_t>(std::stoul(input.substr(start, end - start))));
   start = end + 1;
   end = input.find('"', start);
   int day = std::stoi(input.substr(start, end - start));
   start = end + 1;
   end = input.find('"', start);
   std::string memo = input.substr(start, end - start);
   start = end + 1;
   end = input.find('\t', start);
   account_t account = ledger.account_table.at(identifier_t<account_t>(std::stoull(input.substr(start, end - start))));
   start = end + 1;
   end = input.find('\t', start);
   double amount = std::stoll(input.substr(start, end - start));
   start = end + 1;
   end = input.find('\t', start);
   double denom = std::stoull(input.substr(start, end - start));

   std::cout << std::chrono::duration<double, std::ratio<1,1>>(time.time_since_epoch()).count() << " " << year << "-" << month << "-" << day << " \"" << memo << "\", account: " << account.name() << ": " << amount / denom << std::endl;

   auto aid001 = ledger.account_table.insert({"Credit Card", account_type_t::BUDGETED_ACCOUNT});
   auto aid002 = ledger.account_table.insert({"Groceries", account_type_t::BUDGET_CATEGORY});
   auto aid003 = ledger.account_table.insert({"Wegmans", account_type_t::INCOME_EXPENSE});
   auto tid001 = ledger.transaction_table.insert({date::year{2016}/11/14});
   ledger.adjustment_table.insert({tid001, aid001, "-20.00"});
   ledger.adjustment_table.insert({tid001, aid002, "-20.00"});
   ledger.adjustment_table.insert({tid001, aid003, "20.00"});

   std::cout << ledger.account_table.size() << std::endl;
   std::cout << ledger.adjustment_table.size() << std::endl;
   std::cout << ledger.transaction_table.size() << std::endl;

   for (const auto pr : ledger.account_table) {
      std::cout << pr.first << ": " << pr.second.name() << std::endl;
   }

   return unit_test_results; // the result from doctest is propagated here as well
}
