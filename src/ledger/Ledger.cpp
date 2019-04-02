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
#include "Adjustment.hpp"
#include "Payee.hpp"
#include "Transaction.hpp"
#include "util/transform_if.hpp"

#include <boost/container/flat_set.hpp>

#include <list>
#include <regex>

namespace ledger {

struct Ledger::Impl {

   void insert(Account const& a) { m_accounts.insert(a); }

   void insert(Payee const& p) { m_payees.insert(p); }

   void insert(Adjustment const& a) { m_adjustments.push_back(a); }

   void insert(Transaction const& t) {
      if (is_valid(t)) {
         for (auto const& a : t.adjustments()) {
            m_adjustments.emplace_back(t.date(), t.payee(), a.account(), a.amount());
         }
      }
   }

   [[nodiscard]] std::vector<Account> accounts(std::string const& re) const {
      std::vector<Account> result;
      transform_if(m_adjustments,
                   std::back_inserter(result),
                   [re](Adjustment const& adjustment) {
                      return std::regex_search(adjustment.account().name(), std::regex(re)); },
                   [](Adjustment const& adjustment) {
                      return adjustment.account(); });
      return result;
   }

   [[nodiscard]] std::vector<Payee> payees(std::string const& re) const {
      std::vector<Payee> result;
      transform_if(m_adjustments,
                   std::back_inserter(result),
                   [re](Adjustment const& adjustment) {
                      return std::regex_search(adjustment.payee().name(), std::regex(re)); },
                   [](Adjustment const& adjustment) {
                      return adjustment.payee(); });
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
   std::vector<Adjustment>             m_adjustments;
};

Ledger::Ledger() : m_pimpl(std::make_shared<Ledger::Impl>()) {}

void Ledger::insert(Account const& a) { m_pimpl->insert(a); }

void Ledger::insert(Payee const& p) { m_pimpl->insert(p); }

void Ledger::insert(Adjustment const& a) { m_pimpl->insert(a); }

void Ledger::insert(Transaction const& t) { m_pimpl->insert(t); }

std::vector<Account> Ledger::accounts(std::string const& re) const { return m_pimpl->accounts(re); }

std::vector<Payee> Ledger::payees(std::string const& re) const { return m_pimpl->payees(re); }

} // namespace ledger
