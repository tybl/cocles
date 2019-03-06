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

#include "date/date.h"

#include <iostream>
#include <sstream>
#include <string>

namespace parse {

struct transaction_t {
   using date_t = date::year_month_day;

   transaction_t(std::string pTransaction)
      : value_(pTransaction)
   {
      std::cout << "transaction_c(std::string) with \"" << value_ << "\"";
      date::parse_manip<date_t, std::string::value_type> parser("%F", date_);
      std::istringstream trans_ss(value_);
      trans_ss >> parser;
      std::string test;
      trans_ss >> test;
      std::cout << test << std::endl;
   }

   date_t date() const { return date_; }

private:
   std::string value_;
   date_t date_;
}; // struct transaction_t

} // namespace parse

namespace ledger {

parse::transaction_t parse(std::string input) {
   return parse::transaction_t(input);
} // parse(std::string input)

} // namespace ledger

#endif // COCLES_LEDGER_PARSE_TRANSACTION_HPP
