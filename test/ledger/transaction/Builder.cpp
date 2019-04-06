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

#include "ledger/transaction/Builder.hpp"

#include "doctest/doctest.h"

TEST_CASE("tblyons/cocles#3") {
   using namespace ledger;

   CHECK(Transaction::Builder().set_date("2019-03-09").set_payee("Wegman's")
         .add_adjustment(Adjustment(Account("Accounts:Citi:Credit"), util::Money("-54.33 USD")))
         .add_adjustment(Adjustment(Account("Funds:Daily:Food"), util::Money("54.33 USD")))
         .is_valid());
   CHECK(!Transaction::Builder().set_date("2019-03-09").set_payee("Wegman's")
         .add_adjustment(Adjustment(Account("Funds:Daily:Food"), util::Money("54.33 USD")))
         .is_valid());
}
