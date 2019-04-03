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

#include "ExtendedAdjustment.hpp"

namespace ledger {

// enum class AdjustmentStatus { UNKNOWN, PENDING, CLEARED, RECONCILED };

ExtendedAdjustment::ExtendedAdjustment(util::Date date, Payee payee, Account account, util::Money amount)
   : m_date(date)
   , m_payee(std::move(payee))
   , m_account(std::move(account))
   , m_amount(amount)
{ }

util::Date const& ExtendedAdjustment::date() const { return m_date; }

Payee const& ExtendedAdjustment::payee() const { return m_payee; }

Account const& ExtendedAdjustment::account() const { return m_account; }

util::Money const& ExtendedAdjustment::amount() const { return m_amount; }

} // namespace ledger