#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include "date/date.h"

#include <algorithm>
#include <atomic>
#include <cassert>
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

inline constexpr int64_t pow10(uint32_t exponent) {
   return (exponent == 0) ? 1 : (10 * pow10(exponent - 1));
}

template <uint32_t DECIMAL_PLACES>
struct fixed_point_t {

   static constexpr int64_t exponent = pow10(DECIMAL_PLACES);

   constexpr fixed_point_t()
      : m_value() {}

   constexpr fixed_point_t(double value)
      : m_value(static_cast<int64_t>(value * exponent)) {}

   fixed_point_t& operator+=(const fixed_point_t& other) {
      m_value += other.m_value;
      return *this;
   }

   fixed_point_t& operator-=(const fixed_point_t& other) {
      m_value -= other.m_value;
      return *this;
   }

   int64_t whole_number() const {
      return m_value / exponent;
   }

private:
   int64_t m_value;
}; // struct fixed_point_t

TEST_CASE("fixed_point_t") {
   fixed_point_t<4> fp(10.1234);
   CHECK(fp.whole_number() == 10);
}

TEST_CASE("fixed_point_t::operator+=()") {
   fixed_point_t<4> a(1.2345);
   fixed_point_t<4> b(5.4321);
   CHECK(a.whole_number() == 1);
   CHECK(b.whole_number() == 5);
   a += b;
   CHECK(a.whole_number() == 6);
   CHECK(b.whole_number() == 5);
}

template <typename TYPE>
struct identifier_t {

   constexpr explicit identifier_t(uint64_t value) noexcept
      : m_value(value) {}

   bool operator==(const identifier_t& other) const noexcept {
      return (m_value == other.m_value);
   }

   bool operator!=(const identifier_t& other) const noexcept {
      return !operator==(other);
   }

   explicit operator uint64_t() const noexcept {
      return m_value;
   }

   bool operator<(const identifier_t& other) const noexcept {
      return (m_value < other.m_value);
   }

private:
   uint64_t m_value;
};

template <typename TYPE>
std::ostream& operator<<(std::ostream& out, const identifier_t<TYPE>& id) {
   return out << static_cast<uint64_t>(id);
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
   uint64_t m_max_id;
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

struct rational_t {

   rational_t()
      : m_numerator()
      , m_denominator() {}

//private:
   int64_t m_numerator;
   uint64_t m_denominator;
};

struct decimal_t {

};

struct adjustment_t {
   using transaction_id_t = identifier_t<transaction_t>;
   using account_id_t = identifier_t<account_t>;

   adjustment_t(transaction_id_t transaction_id, account_id_t account_id, const rational_t& amount)
      : m_transaction_id(transaction_id)
      , m_account_id(account_id)
      , m_amount(amount) {}

   const rational_t& amount() const {
      return m_amount;
   }

private:
   transaction_id_t m_transaction_id;
   account_id_t m_account_id;
   rational_t m_amount;
}; // struct adjustment_t

struct add_adjustment_event_t {
   add_adjustment_event_t()
      : account_id(0) {}

   identifier_t<account_t> account_id;
   std::string memo;
   rational_t amount;
};

struct add_transaction_event_t {

   add_transaction_event_t() = default;

   add_transaction_event_t(const std::string& input) {
      deserialize(input);
   }

   void deserialize(const std::string& input) {

      std::size_t start = 0;
      std::size_t end = input.find('\t', start);
      assert(2 == std::stoi(input.substr(start, end - start)));
      start = end + 1;
      end = input.find('\t', start);
      time = std::chrono::system_clock::time_point(std::chrono::microseconds(std::stoull(input.substr(start, end - start))));

      start = end + 1;
      end = input.find('\t', start);
      date = date::sys_days(date::days(std::stoi(input.substr(start, end - start))));

      start = end + 1;
      end = input.find('\t', start);
      memo = input.substr(start, end - start);

      while (std::string::npos != end) {
         add_adjustment_event_t adjustment;
         start = end + 1;
         end = input.find('\t', start);
         adjustment.account_id = identifier_t<account_t>(std::stoull(input.substr(start, end - start)));
         start = end + 1;
         end = input.find('\t', start);
         adjustment.memo = input.substr(start, end - start);
         start = end + 1;
         end = input.find('\t', start);
         adjustment.amount.m_numerator = std::stoll(input.substr(start, end - start));
         start = end + 1;
         end = input.find('\t', start);
         adjustment.amount.m_denominator = std::stoull(input.substr(start, end - start));
         adjustments.push_back(adjustment);
      }
   }

   std::string serialize() const {
      std::string result;
      //return               std::to_string(1) + '\t' + std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(time.time_since_epoch()).count()) + '\t' + name + '\t' + std::to_string(static_cast<int>(type));
      result += std::to_string(2) + '\t';
      result += std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(time.time_since_epoch()).count()) + '\t';
      result += std::to_string(date.time_since_epoch().count()) + '\t';
      result += memo;
      for (auto adj : adjustments) {
         result += '\t' + std::to_string(static_cast<uint64_t>(adj.account_id));
         result += '\t' + adj.memo;
         result += '\t' + std::to_string(adj.amount.m_numerator);
         result += '\t' + std::to_string(adj.amount.m_denominator);
      }
      return result;
   }

   std::chrono::system_clock::time_point time;
   date::sys_days date;
   std::string memo;
   std::vector<add_adjustment_event_t> adjustments;
};

TEST_CASE("add_account_event dogfood") {
   using namespace std::literals;
   auto input = "2\t1479263536123456\t17121\tStarting Balances\t1\t\t501318\t100"s;
   add_transaction_event_t transaction(input);
   CHECK(transaction.serialize() == input);
}

struct add_account_event_t {

   add_account_event_t() = default;

   add_account_event_t(const std::string& input) {
      deserialize(input);
   }

   void deserialize(const std::string& input) {
      std::size_t start = 0;
      std::size_t end = input.find('\t', start);
      assert(1 == std::stoi(input.substr(start, end - start)));
      start = end + 1;
      end = input.find('\t', start);
      time = std::chrono::system_clock::time_point(std::chrono::microseconds(std::stoull(input.substr(start, end - start))));

      start = end + 1;
      end = input.find('\t', start);
      name = input.substr(start, end - start);

      start = end + 1;
      end = input.find('\t', start);
      type = static_cast<account_type_t>(std::stoi(input.substr(start, end - start)));
   }

   std::string serialize() const {
      return std::to_string(1) + '\t' +
             std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(time.time_since_epoch()).count()) + '\t' +
             name + '\t' +
             std::to_string(static_cast<int>(type));
   }

   std::chrono::system_clock::time_point time;
   std::string name;
   account_type_t type;
};

TEST_CASE("add_account_event dogfood") {
   using namespace std::literals;
   auto account_input = "1\t1479263530123456\tChecking\t2"s;
   add_account_event_t a(account_input);
   CHECK(a.serialize() == account_input);
}

struct ledger_t {

   void replay_event(const add_transaction_event_t& event) {
      identifier_t<transaction_t> tid = transaction_table.insert({event.date, event.memo});
      for (auto adj : event.adjustments) {
         // TODO(tblyons): throw exception if adjustment already exists
         adjustment_table.insert({tid, adj.account_id, adj.amount});
      }
   }

   void replay_event(const add_account_event_t& event) {
      account_t account(event.name, event.type);
      // TODO(tblyons): throw exception if account already exists
      account_table.insert(account);
   }

   table_t<transaction_t> transaction_table;
   table_t<account_t>         account_table;
   table_t<adjustment_t>   adjustment_table;
};

extern "C" int main(int argc, const char* argv[]) {
   using namespace std::literals;
   int unit_test_results = run_unit_tests(argc, argv);

   ledger_t ledger;
   add_account_event_t account("1\t1479263530123456\tChecking\t2");
   ledger.replay_event(account);

   // TODO(tblyons): Add information about event type
   auto transaction_input = "2\t1479263536123456\t17121\tStarting Balances\t1\t\t501318\t100"s;

   add_transaction_event_t e;
   e.deserialize(transaction_input);

#if 0
   auto aid001 = ledger.account_table.insert({"Credit Card", account_type_t::BUDGETED_ACCOUNT});
   auto aid002 = ledger.account_table.insert({"Groceries", account_type_t::BUDGET_CATEGORY});
   auto aid003 = ledger.account_table.insert({"Wegmans", account_type_t::INCOME_EXPENSE});
   auto tid001 = ledger.transaction_table.insert({date::year{2016}/11/14});
   ledger.adjustment_table.insert({tid001, aid001, "-20.00"});
   ledger.adjustment_table.insert({tid001, aid002, "-20.00"});
   ledger.adjustment_table.insert({tid001, aid003, "20.00"});
#endif

   std::cout << ledger.account_table.size() << std::endl;
   std::cout << ledger.adjustment_table.size() << std::endl;
   std::cout << ledger.transaction_table.size() << std::endl;

   for (const auto pr : ledger.account_table) {
      std::cout << pr.first << ": " << pr.second.name() << std::endl;
   }

   return unit_test_results; // the result from doctest is propagated here as well
}
