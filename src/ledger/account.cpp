#include "account.hpp"

namespace ledger {
   account_t::account_t(unsigned long new_id,
                        std::string new_name,
                        account_type_t new_type)
      : id(new_id),
      name(new_name),
      type(new_type)
   {
   }

   const std::string&
   account_t::Name(void) const {
      return name;
   }

   const identifier_t&
   account_t::ID(void) const {
      return id;
   }

   const account_t::account_type_t&
   account_t::Type(void) const {
      return type;
   }
} // namespace ledger
