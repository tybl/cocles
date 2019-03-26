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

struct Adjustment::Impl {
   Impl(Transaction transaction, Account account, util::Money amount)
      : m_transaction(std::move(transaction))
      , m_account(std::move(account))
      , m_amount(amount) { }

   Transaction const& transaction() const { return m_transaction; }
   Account     const& account() const { return m_account; }
   util::Money const& amount() const { return m_amount; }

private:
   Transaction m_transaction;
   Account     m_account;
   util::Money m_amount;
};

Adjustment::Adjustment(Transaction transaction, Account account, util::Money amount)
   : m_pimpl(new Impl(std::move(transaction), std::move(account), amount)) { }

Transaction const& Adjustment::transaction() const { return m_pimpl->transaction(); }

Account const& Adjustment::account() const { return m_pimpl->account(); }

util::Money const& Adjustment::amount() const { return m_pimpl->amount(); }

} // namespace ledger
