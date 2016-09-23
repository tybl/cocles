#include "account_table.hpp"

unsigned long
account_table_t::GetIdForAccount(std::string account_name) {
   auto pos = std::lower_bound(accounts.begin(), accounts.end(), account_name, cmp);
   if (accounts.end() == pos || pos->Name() != account_name) {
      pos = accounts.emplace(pos, accounts.size(), account_name);
   }
   for (auto a : accounts) {
      std::cout << a.ID() << " " << a.Name() << std::endl;
   }
   std::cout << std::endl;
   return pos->ID();
}

std::string
account_table_t::GetNameForAccount(unsigned long id) {
   return accounts.at(id_index.at(id)).Name();
}

bool
account_table_t::cmp(const account_t &a, const std::string &s) {
   return a.Name() < s;
}

account_table_t::account_t::account_t(unsigned long new_id,
                                      std::string new_name/*,
                                      AccountType new_type*/)
   : id(new_id),
   name(new_name)/*,
   type(new_type)*/
{
}

std::string
account_table_t::account_t::Name(void) const { return name; }

unsigned long
account_table_t::account_t::ID(void) const { return id; }
