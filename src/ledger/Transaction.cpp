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

#include "Transaction.hpp"

namespace ledger {

#if 0
struct Transaction::Impl {

   Impl(Date date, Payee payee) : m_payee(std::move(payee)), m_date(date) { }

   [[nodiscard]] Payee const& payee() const { return m_payee; }

private:
   Payee          m_payee;
   boost::gregorian::date m_date;
}; // struct Transaction::Impl

Transaction::Transaction(Date date, Payee payee)
   : m_pimpl(new Impl(date, std::move(payee))) { }

Payee const& Transaction::payee() const { return m_pimpl->payee(); }
#endif

} // namespace ledger
