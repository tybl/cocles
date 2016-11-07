#if 0
#include "ledger/internal/Database.hpp"

#include <iostream>

extern "C" int main(int argc, const char * argv[]) {
   Database db;
   auto first_trans = db.new_transaction();
   std::string input = "Hello world!";
   db.set_memo(first_trans, input);
   std::cout << db.get_memo(first_trans) << std::endl;
   return 0;
}
#endif

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

   if (context.shouldExit()) {          // important // query flags (and --exit) rely on the user doing this
      exit(result);                                  // propagate the result of the tests
   }
   return result;
}

extern "C" int main(int argc, const char* argv[]) {
   int unit_test_results = run_unit_tests(argc, argv);



   return unit_test_results; // the result from doctest is propagated here as well
}
