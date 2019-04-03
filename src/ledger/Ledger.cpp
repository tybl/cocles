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

#include "Ledger.hpp"

#include "Account.hpp"
#include "ExtendedAdjustment.hpp"
#include "Payee.hpp"
#include "Transaction.hpp"
#include "util/transform_if.hpp"

#include <boost/container/flat_set.hpp>

#include <iostream>
#include <regex>

namespace ledger {

struct Ledger::Impl {

   void insert(Account const& a) { m_accounts.insert(a); }

   void insert(Payee const& p) { m_payees.insert(p); }

   void insert(Transaction const& t) {
      if (is_valid(t)) {
         for (auto const& a : t.adjustments()) {
            m_adjustments.emplace_back(t.date(), t.payee(), a.account(), a.amount());
         }
      } else {
         std::cout << "Error: invalid transaction!\n";
      }
   }

   [[nodiscard]] std::vector<Account> accounts(std::string const& re) const {
      std::vector<Account> result;
      std::copy_if(m_accounts.begin(), m_accounts.end(), std::back_inserter(result),
                   [re](Account const& account) {
                      return std::regex_search(account.name(), std::regex(re)); });
      return result;
   }

   [[nodiscard]] std::vector<Payee> payees(std::string const& re) const {
      std::vector<Payee> result;
      std::copy_if(m_payees.begin(), m_payees.end(), std::back_inserter(result),
                   [re](Payee const& payee) {
                      return std::regex_search(payee.name(), std::regex(re)); });
      return result;
   }

private:
   bool is_valid(Transaction const& t) {
      if (!m_payees.contains(t.payee())) {
         return false;
      }
      for (auto const& a : t.adjustments()) {
         if (!m_accounts.contains(a.account())) {
            return false;
         }
      }
      return true;
   }

private:
   boost::container::flat_set<Account> m_accounts;
   boost::container::flat_set<Payee>   m_payees;
   std::vector<ExtendedAdjustment>     m_adjustments;
};

Ledger::Ledger() : m_pimpl(std::make_shared<Ledger::Impl>()) {}

void Ledger::insert(Account const& a) { m_pimpl->insert(a); }

void Ledger::insert(Payee const& p) { m_pimpl->insert(p); }

void Ledger::insert(Transaction const& t) { m_pimpl->insert(t); }

std::vector<Account> Ledger::accounts(std::string const& re) const { return m_pimpl->accounts(re); }

std::vector<Payee> Ledger::payees(std::string const& re) const { return m_pimpl->payees(re); }

} // namespace ledger
