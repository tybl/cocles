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

#ifndef COCLES_LEDGER_EXTENDED_ADJUSTMENT_HPP
#define COCLES_LEDGER_EXTENDED_ADJUSTMENT_HPP

#include "Account.hpp"
#include "Payee.hpp"
#include "util/Date.hpp"
#include "util/Money.hpp"

namespace ledger {

struct ExtendedAdjustment {

   ExtendedAdjustment(util::Date date, Payee payee, Account account, util::Money amount);

   [[nodiscard]] util::Date const& date() const;

   [[nodiscard]] Payee const& payee() const;

   [[nodiscard]] Account const& account() const;

   [[nodiscard]] util::Money const& amount() const;

private:
   util::Date  m_date;
   Payee       m_payee;
   Account     m_account;
   util::Money m_amount;
}; // struct ExtendedAdjustment

} // namespace ledger

#endif // COCLES_LEDGER_EXTENDED_ADJUSTMENT_HPP