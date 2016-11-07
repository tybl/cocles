#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

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

struct event_t {};
struct account_t {};
struct adjustment_t {};
struct transaction_t {};

struct ledger_impl_t {

   ledger_impl_t(std::string filename);

   ~ledger_impl_t() noexcept;

   void append_event(event_t event);

   void replay_event(event_t event);

private:
   std::vector<account_t> m_accounts;
   std::vector<adjustment_t> m_adjustments;
   std::vector<transaction_t> m_transactions;
};

struct ledger_t {

   explicit ledger_t(std::string filename);

   ~ledger_t() noexcept;

private:
   std::unique_ptr<ledger_impl_t> m_impl;
};

extern "C" int main(int argc, const char* argv[]) {
   int unit_test_results = run_unit_tests(argc, argv);



   return unit_test_results; // the result from doctest is propagated here as well
}
