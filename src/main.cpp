#include "ledger.hpp"

extern "C"
int
main(int , const char * []) {
   ledger_t ledger;
   ledger.AddTransaction("{ \"date\":\"2016-09-17\", \"adjustments\":[ {\"account\":\"Toys-R-Us\",\"amount\":77.89}, {\"account\":\"Spending\",\"amount\":-27.17}, {\"account\":\"Birthday\",\"amount\":-50.72}, {\"account\":\"Credit Card\",\"amount\":-77.89} ] }");
   return 0;
}
