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

#ifndef COCLES_LEDGER_PARSE_TRANSACTION_HPP
#define COCLES_LEDGER_PARSE_TRANSACTION_HPP

#include "adjustment.hpp"

#include <boost/date_time/gregorian/gregorian.hpp>

#include <memory>
#include <string>
#include <vector>

namespace ledger {

namespace parse {

class transaction_t {
   struct PassKey {
      PassKey() = default;
   }; // struct Passkey

public:
   using date_t = boost::gregorian::date;

   explicit transaction_t(std::string const& t);

   transaction_t(PassKey, date_t date, std::string payee)
      : m_date(date)
      , m_payee(std::move(payee)) { }

   date_t date() const;

   const std::string& payee() const;

   static std::unique_ptr<transaction_t> parse(std::string const& string);

private:
   date_t                    m_date;
   std::string               m_payee;
   std::vector<adjustment_t> m_adjustments;
}; // struct transaction_t

} // namespace parse

// TODO: Move the parse function to another file. Probably src/ledger/parse.hpp
inline
ledger::parse::transaction_t Parse(std::string const& input) {
   return ledger::parse::transaction_t(input);
} // parse(std::string input)

} // namespace ledger

#endif // COCLES_LEDGER_PARSE_TRANSACTION_HPP
