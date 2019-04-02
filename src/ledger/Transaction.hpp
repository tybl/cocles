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

#ifndef COCLES_LEDGER_TRANSACTION_HPP
#define COCLES_LEDGER_TRANSACTION_HPP

#include "Account.hpp"
#include "Payee.hpp"
#include "util/Money.hpp"

#include <boost/date_time/gregorian/gregorian.hpp>

namespace ledger {

struct Transaction {
   using Date = boost::gregorian::date;

   struct Adjustment {
      Adjustment(std::string const& account, int64_t amount)
         : m_account(account)
         , m_amount(amount) { }

      [[nodiscard]] Account const& account() const { return m_account; }

      [[nodiscard]] util::Money const& amount() const { return m_amount; }

   private:
      Account m_account;
      util::Money   m_amount;
   }; // Transaction::Adjustment

   Transaction(Date date, Payee payee)
      : m_date(date)
      , m_payee(std::move(payee)) { }

   [[nodiscard]] std::vector<Adjustment> adjustments() const { return m_adjustments; }
   [[nodiscard]] Date const& date() const { return m_date; }
   [[nodiscard]] Payee const& payee() const { return m_payee; }
private:
   Date m_date;
   Payee m_payee;
   std::vector<Adjustment> m_adjustments;
}; // struct Transaction

#if 0
struct Transaction {
   using Date = boost::gregorian::date;
   Transaction(Date date, Payee payee);

   [[nodiscard]] Payee const& payee() const;

private:
   struct Impl;
   std::shared_ptr<Impl> m_pimpl;
}; // struct Transaction
#endif

} // namespace ledger

#endif // COCLES_LEDGER_TRANSACTION_HPP
