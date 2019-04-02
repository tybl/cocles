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

#include <memory>
#include <string>
#include <vector>

namespace ledger {

struct Account;
struct Adjustment;
struct Payee;
struct Transaction;

struct Ledger {

   Ledger();

   void insert(Account const& a);

   void insert(Payee const& p);

   void insert(Adjustment const& a);

   void insert(Transaction const& t);

   // Copies all account names that match a specific regex
   [[nodiscard]] std::vector<Account> accounts(std::string const& re) const;

   // Copies all payee names that match a specific regex
   [[nodiscard]] std::vector<Payee> payees(std::string const& re) const;

private:
   struct Impl;
   std::shared_ptr<Impl> m_pimpl;
}; // struct Ledger

} // namespace ledger

#endif // COCLES_LEDGER_LEDGER_HPP
