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

#ifndef COCLES_LEDGER_LEDGER_HPP
#define COCLES_LEDGER_LEDGER_HPP

struct Transfer {
   date::year_month_day Date;
   std::string Payee;
   std::string Account;
   Money Amount;
}; // struct Transfer

struct Accounts {
   struct Node {
      std::string Name;
      Node* Parent;
      std::vector<Node*> Children;

      std::string GetFullName() {
         if (Parent) {
            return Parent->GetFullName() + ":" + Name;
         } else {
            return Name;
         }
      }
   }; // struct Account
private:
   Node* Root;
}; // struct Accounts

struct Account {

private:
   std::map<std::string, Account> mChildren;
}; // struct Account

struct Ledger {
private:

   std::vector<Transfer> mTransfers;
}; // struct Ledger

#endif // COCLES_LEDGER_LEDGER_HPP
