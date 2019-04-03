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

#include "ledger/Account.hpp"
#include "ledger/Adjustment.hpp"
#include "ledger/Ledger.hpp"
#include "ledger/Payee.hpp"
#include "ledger/Transaction.hpp"
#include "util/Date.hpp"
#include "util/Money.hpp"

int main(int argc, const char* argv[], const char* envp[]) {
   static_cast<void>(argc);
   static_cast<void>(argv);
   static_cast<void>(envp);

   ledger::Ledger ledger;

   ledger::Transaction t(boost::gregorian::from_string("2019-03-09"), ledger::Payee("Wegman's"));
   t.add_adjustment(ledger::Adjustment(ledger::Account("Accounts:Citi:Credit"), util::Money("-54.33 USD")));
   t.add_adjustment(ledger::Adjustment(ledger::Account("Funds:Daily:Food"), util::Money("54.33 USD")));

   ledger.insert(t);

   for (auto const& a : ledger.accounts("")) {
      std::cout << a.name() << "\n";
   }

   for (auto const& p : ledger.payees("")) {
      std::cout << p.name() << "\n";
   }

   return 0;
}
