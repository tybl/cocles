#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

#include <algorithm>
#include <chrono>

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

struct event_t {

   event_t() noexcept
      : m_time(std::chrono::high_resolution_clock::now()) {}

private:
   std::chrono::high_resolution_clock::time_point m_time;
};

enum class account_type_t {
   INCOME_EXPENSE,
   BUDGET_CATEGORY,
   BUDGETED_ACCOUNT,
   UNBUDGETED_ACCOUNT
};

struct account_t {

   account_t(std::string name, account_type_t type)
      : m_type(type)
      , m_name(name) {}

   std::string name() const { return m_name; }

   account_type_t type() const { return m_type; }

private:
   account_type_t m_type;
   std::string m_name;
}; // struct account_t

struct adjustment_t {};
struct transaction_t {

   transaction_t(std::string date)
      : m_date(date) {}

   const std::string& date() const {
      return m_date;
   }

private:
   std::string m_date;
   std::string m_memo;
}; // struct transaction_t

template <typename TYPE>
struct table_t {
   struct iterator_t {
   };
private:
   
}; // struct table_t

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

struct ledger_impl_t {

   ledger_impl_t(std::string filename) {
      static_cast<void>(filename);
   }

   ~ledger_impl_t() noexcept {}

   void append_event(const add_account_event_t &event) {
      replay_event(event);
   }

   void replay_event(const add_account_event_t &event) {
      auto account_ptr = std::make_unique<account_t>(event.name(), event.type());
      auto iter = std::upper_bound(m_accounts.cbegin(), m_accounts.cend(), account_ptr, [](const std::unique_ptr<account_t> &a, const std::unique_ptr<account_t> &b) -> bool { return a->name() < b->name(); });
      if (m_accounts.cend() == iter || (*iter)->name() != event.name()) {
         m_accounts.insert(iter, std::move(account_ptr));
      }
   }

   std::pair<std::vector<std::unique_ptr<account_t>>::const_iterator, std::vector<std::unique_ptr<account_t>>::const_iterator> get_accounts_starting_with(const std::string &prefix) const {
      const auto& begin = std::lower_bound(m_accounts.cbegin(), m_accounts.cend(), prefix, [](const std::unique_ptr<account_t> &acnt_ptr, const std::string &str) -> bool { return str < acnt_ptr->name(); });
      const auto& end = std::upper_bound(m_accounts.cbegin(), m_accounts.cend(), prefix, [](const std::string &str, const std::unique_ptr<account_t> &acnt_ptr) -> bool { return str < acnt_ptr->name(); });
      return std::make_pair(begin, end);
   }

   account_t* find_account(const std::string &name) const {
      auto iter = std::upper_bound(m_accounts.cbegin(), m_accounts.cend(), name, [](const std::string &a, const std::unique_ptr<account_t> &b) -> bool { return a < b->name(); });
      if (m_accounts.cend() == iter || (name != (*iter)->name())) {
         return nullptr;
      }
      return iter->get();
   }

private:
   std::vector<std::unique_ptr<account_t>> m_accounts;
   std::vector<adjustment_t> m_adjustments;
   std::vector<transaction_t> m_transactions;
}; // struct ledger_impl_t

struct ledger_t {

   explicit ledger_t(std::string filename)
      : m_impl(std::make_unique<ledger_impl_t>(filename)) {}

   ~ledger_t() noexcept {}

   void add_account(const std::string &name) {
      m_impl->append_event(add_account_event_t(name, account_type_t::INCOME_EXPENSE));
   }

private:
   std::unique_ptr<ledger_impl_t> m_impl;
}; // struct ledger_t

extern "C" int main(int argc, const char* argv[]) {
   int unit_test_results = run_unit_tests(argc, argv);

   ledger_t ledger("cocles.log");
   ledger.add_account("Checking");

   return unit_test_results; // the result from doctest is propagated here as well
}
