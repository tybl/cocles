#ifndef COCLES_ACCOUNTTABLE_HPP
#define COCLES_ACCOUNTTABLE_HPP

#include <iostream>
#include <map>
#include <string>
#include <vector>

#if 0
enum AccountType {
   EQUITY,
   INCOME_EXPENSE,
   ASSET_LIABILITY,
   BUDGET_CATEGORY
};
#endif

struct account_table_t {
   unsigned long GetIdForAccount(std::string account_name);
   std::string GetNameForAccount(unsigned long id);
private:
   struct account_t {
      account_t(unsigned long new_id,
                std::string new_name/*,
                AccountType new_type*/);
      std::string Name(void) const;
      unsigned long ID(void) const;
   private:
      unsigned long id;
      std::string name;
      //AccountType type;
   };

   static bool cmp(const account_t &a, const std::string &s);

   std::vector<account_t> accounts;
   std::map<unsigned long, size_t> id_index;
};
#endif // COCLES_ACCOUNTTABLE_HPP
