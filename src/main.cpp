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
