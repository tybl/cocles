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

#include "transaction.hpp"

#include <boost/algorithm/string/trim.hpp>

#include <regex>
#include <sstream>

namespace ledger {

namespace parse {

Transaction::Transaction(std::string const& t) {
   std::smatch m;
   std::regex re(R"(\d{4}-\d{2}-\d{2}) ([A-Za-z ']*)", std::regex_constants::ECMAScript);
   if (std::regex_search(t, m, re)) {
      m_date = boost::gregorian::from_string(m[1]);
   } else {
      throw std::runtime_error("Error: Incomplete transaction");
   }
   m_payee = m[2];
}

std::unique_ptr<Transaction> Transaction::parse(std::string const& t) {
   std::unique_ptr<Transaction> result;
   std::smatch m;
   std::regex re(R"(\d{4}-\d{2}-\d{2})([A-Za-z ']*)", std::regex_constants::ECMAScript);
   if (std::regex_search(t, m, re)) {
      result = std::make_unique<Transaction>(PassKey(), boost::gregorian::from_string(m[1]), m[2]);
      boost::algorithm::trim(result->m_payee);
   }
   return result;
}

Transaction Transaction::parse(std::istream& /* unused */) {
   throw std::runtime_error("Error: Incomplete transaction");
}

Transaction::Transaction(PassKey /* unused */, date_t date, std::string payee)
   : m_date(date)
   , m_payee(std::move(payee)) { }

Transaction::date_t Transaction::date() const { return m_date; }

const std::string& Transaction::payee() const { return m_payee; }

} // namespace parse

} // namespace ledger
