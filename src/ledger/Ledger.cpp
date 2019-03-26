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

#include "util/transform_if.hpp"

namespace ledger {

void Ledger::insert(Account const& a) { m_accounts.push_back(a); }
void Ledger::insert(Payee const& p) { m_payees.push_back(p); }
void Ledger::insert(Adjustment const& a) { m_adjustments.push_back(a); }

// Copies all account names that match a specific regex
std::vector<Account> Ledger::accounts(std::string const& re) const {
   std::vector<Account> result;
   transform_if(m_adjustments,
                std::back_inserter(result),
                [re](Adjustment const& adjustment) {
                   return std::regex_search(adjustment.account().name(), std::regex(re)); },
                [](Adjustment const& adjustment) {
                   return adjustment.account(); });
   return result;
}

// Copies all payee names that match a specific regex
std::vector<Payee> Ledger::payees(std::string const& re) const {
   std::vector<Payee> result;
   transform_if(m_adjustments,
                std::back_inserter(result),
                [re](Adjustment const& adjustment) {
                   return std::regex_search(adjustment.transaction().payee().name(), std::regex(re)); },
                [](Adjustment const& adjustment) {
                   return adjustment.transaction().payee(); });
   return result;
}

} // namespace ledger
