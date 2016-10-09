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

extern "C" int main(int argc, const char* argv[]) {
   doctest::Context context; // initialize

   // defaults
   context.addFilter("test-case-exclude", "*math*"); // exclude test cases with "math" in their name
   context.setOption("abort-after", 5);              // stop test execution after 5 failed assertions
   context.setOption("sort", "name");                // sort the test cases by their name

   context.applyCommandLine(argc, argv);

   // overrides
   context.setOption("no-breaks", true);             // don't break in the debugger when assertions fail

   int res = context.run(); // run

   if (context.shouldExit()) // important - query flags (and --exit) rely on the user doing this
      return res;          // propagate the result of the tests

   int client_stuff_return_code = 0;
   // your program - if the testing framework is integrated in your production code

   return res + client_stuff_return_code; // the result from doctest is propagated here as well
}
