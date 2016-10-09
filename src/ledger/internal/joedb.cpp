#include <iostream>

int main () {
   Database db;
   auto first_trans = db.new_transaction();
   db.set_memo(first_trans, "Hello world!");
   std::cout << db.get_memo(first_trans) << std::endl;
}
