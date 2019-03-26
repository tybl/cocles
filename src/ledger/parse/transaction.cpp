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

transaction_t::transaction_t(std::string const& t) {
   std::smatch m;
   std::regex re(R"(\d{4}-\d{2}-\d{2}) ([A-Za-z ']*)", std::regex::ECMAScript);
   if (std::regex_search(t, m, re)) {
      m_date = boost::gregorian::from_string(m[1]);
   } else {
      throw std::runtime_error("Error: Incomplete transaction");
   }
   m_payee = m[2];
}

std::unique_ptr<transaction_t> transaction_t::parse(std::string const& t) {
   std::unique_ptr<transaction_t> result;
   std::smatch m;
   std::regex re(R"(\d{4}-\d{2}-\d{2})([A-Za-z ']*)");
   if (std::regex_search(t, m, re)) {
      result = std::make_unique<transaction_t>(transaction_t::PassKey(), boost::gregorian::from_string(m[1]), m[2]);
      boost::algorithm::trim(result->m_payee);
   }
   return result;
}

transaction_t::date_t transaction_t::date() const { return m_date; }

const std::string& transaction_t::payee() const { return m_payee; }

} // namespace parse

} // namespace ledger
