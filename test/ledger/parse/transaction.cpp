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

#include "../src/ledger/parse/transaction.hpp"

#include "doctest/doctest.h"

TEST_CASE("parse::transaction_t") {
   using namespace std::string_literals;
   using namespace date::literals;
   auto str = "2019-03-05 Wegman's\n    Accounts:Citi:Credit   $-4.35\n    Funds:Daily:Food   $4.35\n\n"s;
   auto trans = ledger::Parse(str);
   CHECK(trans.date().year() == 2019_y);
   CHECK(trans.date().month() == date::March);
   CHECK(trans.date().day() == 5_d);
   CHECK(trans.payee() == "Wegman's"s);
} // TEST_CASE("parse::transaction_t")
