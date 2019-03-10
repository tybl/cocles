/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* ISC License
*
* Copyright (c) 2019, Timothy Lyons
*
* Permission to use, copy, modify, and/or distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
* REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
* AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
* INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
* LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
* OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
* PERFORMANCE OF THIS SOFTWARE.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef COCLES_LEDGER_LEDGER_HPP
#define COCLES_LEDGER_LEDGER_HPP

#include "Account.hpp"
#include "Adjustment.hpp"
#include "Payee.hpp"
#include "util/transform_if.hpp"

#include <regex>
#include <vector>

namespace ledger {

struct Ledger {

   //void insert(Account a) { m_accounts.push_back(a); }
   //void insert(Payee p) { m_payees.push_back(p); }
   void insert(Adjustment a) { m_adjustments.push_back(a); }

   std::vector<Account> accounts(std::string re) {
      std::vector<Account> result;
      transform_if(m_adjustments.begin(),
                   m_adjustments.end(),
                   std::back_inserter(result),
                   [re](Adjustment const& adjustment) {
                      return std::regex_search(adjustment.account().name(), std::regex(re)); },
                   [](Adjustment const& adjustment) {
                      return adjustment.account(); });
      return result;
   }

#if 0
   std::vector<Payee> payees(std::string re) {
      std::vector<Payee> result;
      std::copy_if(m_payees.begin(),
                   m_payees.end(),
                   std::back_inserter(result),
                   [re](Payee const& payee) {
                      return std::regex_search(payee.name(), std::regex(re)); });
      return result;
   }
#endif
   std::vector<Payee> payees(std::string re) {
      std::vector<Payee> result;
      transform_if(m_adjustments.begin(),
                   m_adjustments.end(),
                   std::back_inserter(result),
                   [re](Adjustment const& adjustment) {
                      return std::regex_search(adjustment.transaction().payee().name(), std::regex(re)); },
                   [](Adjustment const& adjustment) {
                      return adjustment.transaction().payee().name(); }); // TODO: remove .name()
      return result;
   }

private:
   //std::list<Account> m_accounts;
   //std::list<Payee>   m_payees;
   std::vector<Adjustment> m_adjustments;
}; // struct Ledger

} // namespace ledger

#if 0
struct Transfer {
   date::year_month_day Date;
   std::string Payee;
   std::string Account;
   Money Amount;
}; // struct Transfer

struct Accounts {
   struct Node {
      std::string Name;
      Node* Parent;
      std::vector<Node*> Children;

      std::string GetFullName() {
         if (Parent) {
            return Parent->GetFullName() + ":" + Name;
         } else {
            return Name;
         }
      }
   }; // struct Account
private:
   Node* Root;
}; // struct Accounts

struct Account {

private:
   std::map<std::string, Account> mChildren;
}; // struct Account

struct Ledger {
private:

   std::vector<Transfer> mTransfers;
}; // struct Ledger
#endif

#endif // COCLES_LEDGER_LEDGER_HPP
