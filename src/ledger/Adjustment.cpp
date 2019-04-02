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

#include "Adjustment.hpp"

namespace ledger {

// enum class AdjustmentStatus { UNKNOWN, PENDING, CLEARED, RECONCILED };

struct Adjustment::Impl {
   Impl(Date date, Payee payee, Account account, util::Money amount)
      : m_date(date)
      , m_payee(std::move(payee))
      , m_account(std::move(account))
      , m_amount(amount) { }

   [[nodiscard]] Date        const& date() const { return m_date; }
   [[nodiscard]] Payee       const& payee() const { return m_payee; }
   [[nodiscard]] Account     const& account() const { return m_account; }
   [[nodiscard]] util::Money const& amount() const { return m_amount; }

private:
   Date        m_date;
   Payee       m_payee;
   Account     m_account;
   util::Money m_amount;
}; // struct Adjustment::Impl

Adjustment::Adjustment(Adjustment::Date date, Payee payee, Account account, util::Money amount)
   : m_pimpl(new Impl(date, std::move(payee), std::move(account), amount)) { }

Adjustment::Date const& Adjustment::date() const { return m_pimpl->date(); }

Payee const& Adjustment::payee() const { return m_pimpl->payee(); }

Account const& Adjustment::account() const { return m_pimpl->account(); }

util::Money const& Adjustment::amount() const { return m_pimpl->amount(); }

} // namespace ledger
