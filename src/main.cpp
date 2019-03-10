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

#include "ledger/util/Money.hpp"

#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <regex>
#include <string>
#include <vector>

template<class InputIt, class OutputIt, class UnaryPredicate, class UnaryOperation>
OutputIt transform_if(InputIt first, InputIt last, OutputIt d_first, UnaryPredicate pred, UnaryOperation unary_op) {
   while (first != last) {
      if (pred(*first)) {
         *d_first++ = unary_op(*first);
      }
      first++;
   }
   return d_first;
}

struct Account {
   Account(std::string name);
   std::string const& name() const;
private:
   struct Impl;
   std::shared_ptr<Impl> m_pimpl;
}; // struct Account

struct Account::Impl {
   Impl(std::string name) : m_name(name) { }
   std::string const& name() const { return m_name; }
private:
   std::string m_name;
}; // struct Account::Impl

Account::Account(std::string name) : m_pimpl(new Impl(name)) { }

std::string const& Account::name() const { return m_pimpl->name(); }

struct Payee {
   Payee(std::string name);
   std::string const& name() const;
private:
   struct Impl;
   std::shared_ptr<Impl> m_pimpl;
}; // struct Payee

struct Payee::Impl {
   Impl(std::string name) : m_name(name) { }
   std::string const& name() const { return m_name; }
private:
   std::string m_name;
}; // struct Payee::Impl

Payee::Payee(std::string name) : m_pimpl(new Impl(name)) { }

std::string const& Payee::name() const { return m_pimpl->name(); }

#include <boost/date_time/gregorian/gregorian.hpp>

struct Transaction {
   using Date = boost::gregorian::date;
   Transaction(Date date, Payee payee);

   Payee const& payee() const;

private:
   struct Impl;
   std::shared_ptr<Impl> m_pimpl;
}; // struct Transaction

struct Transaction::Impl {

   Impl(Date date, Payee payee) : m_payee(payee), m_date(date) { }

   Payee const& payee() const { return m_payee; }

private:
   Payee                  m_payee;
   boost::gregorian::date m_date;
}; // struct Transaction::Impl

Transaction::Transaction(Date date, Payee payee)
   : m_pimpl(new Impl(date, payee)) { }

Payee const& Transaction::payee() const { return m_pimpl->payee(); }

struct Adjustment {
   Adjustment(Transaction transaction, Account account, util::Money amount);

   Transaction const& transaction() const;

   Account const& account() const;

   util::Money const& amount() const;

private:
   struct Impl;
   std::shared_ptr<Impl> m_pimpl;
};

struct Adjustment::Impl {
   Impl(Transaction transaction, Account account, util::Money amount)
      : m_transaction(transaction)
      , m_account(account)
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
   : m_pimpl(new Impl(transaction, account, amount)) { }

Transaction const& Adjustment::transaction() const { return m_pimpl->transaction(); }

Account const& Adjustment::account() const { return m_pimpl->account(); }

util::Money const& Adjustment::amount() const { return m_pimpl->amount(); }

struct Ledger {

   void insert(Account a) { m_accounts.push_back(a); }
   void insert(Payee p) { m_payees.push_back(p); }
   void insert(Adjustment a) { m_adjustments.push_back(a); }

   std::vector<Account> accounts(std::string re) {
      std::vector<Account> result;
      transform_if(m_adjustments.begin(),
                   m_adjustments.end(),
                   std::back_inserter(result),
                   [re](Adjustment const& adjustment) {
                      return std::regex_search(adjustment.account().name(), std::regex(re)); },
                   [](Adjustment const& adjustment) {
                      return adjustment.account(); });
      return result;
   }

#if 0
   std::vector<Payee> payees(std::string re) {
      std::vector<Payee> result;
      std::copy_if(m_payees.begin(),
                   m_payees.end(),
                   std::back_inserter(result),
                   [re](Payee const& payee) {
                      return std::regex_search(payee.name(), std::regex(re)); });
      return result;
   }
#endif
   std::vector<Payee> payees(std::string re) {
      std::vector<Payee> result;
      transform_if(m_adjustments.begin(),
                   m_adjustments.end(),
                   std::back_inserter(result),
                   [re](Adjustment const& adjustment) {
                      return std::regex_search(adjustment.transaction().payee().name(), std::regex(re)); },
                   [](Adjustment const& adjustment) {
                      return adjustment.transaction().payee().name(); }); // TODO: remove .name()
      return result;
   }

private:
   std::list<Account> m_accounts;
   std::list<Payee>   m_payees;
   std::vector<Adjustment> m_adjustments;
}; // struct Ledger

int main(int argc, const char* argv[], const char* envp[]) {
   using namespace std::string_literals;
   static_cast<void>(argc);
   static_cast<void>(argv);
   static_cast<void>(envp);

   Ledger ledger;

   ledger.insert(
         Adjustment(
            Transaction(boost::gregorian::from_string("2019-03-09"),
                        Payee("Wegman's")),
            Account("Accounts:Citi:Credit"),
            util::Money("-54.33 USD")));

   for (auto a : ledger.accounts("")) {
      std::cout << a.name() << "\n";
   }

   for (auto p : ledger.payees("")) {
      std::cout << p.name() << "\n";
   }

   return 0;
}

#if 0
//#include "Application.hpp"
#include "ledger/util/stringify_arguments.hpp"

#include <atomic>
#include <iostream>
#include <list>
#include <map>

struct Account {
   std::string Name;
}; // struct Account

struct Accounts {
   std::string Name;
}; // struct Accounts

struct Ledger {
   void AddAccount(std::string pName);
   std::list<std::string>::const_iterator begin() const { return mAccounts.cbegin(); }
   std::list<std::string>::const_iterator end() const { return mAccounts.cend(); }
   std::list<std::string>::const_iterator cbegin() const { return mAccounts.cbegin(); }
   std::list<std::string>::const_iterator cend() const { return mAccounts.cend(); }
private:
   std::list<std::string> mAccounts;
}; // struct Ledger

struct Application {
   Application(std::vector<std::string> args, const char* envp[]);
   ~Application();
   int run();

   // Deleted functions
   Application(Application const&) = delete;
   Application(Application&&) = delete;
   Application& operator=(Application) = delete;
   Application& operator=(Application&&) = delete;
private:
   static std::atomic<bool> mInstanceExists;
}; // class Application

int main(int argc, const char* argv[], const char* envp[]) {
   Application app(ledger::util::stringify_arguments(argc, argv), envp);
   return app.run();
}

void Ledger::AddAccount(std::string pName) {
   mAccounts.push_back(pName);
}

std::atomic<bool> Application::mInstanceExists = false;

Application::Application(std::vector<std::string> args, const char* envp[]) {
   static_cast<void>(args);
   static_cast<void>(envp);

   if (mInstanceExists) {
      throw std::runtime_error(
          "Error: An instance of Application already exists");
   }
   mInstanceExists = true;
}

Application::~Application() { mInstanceExists = false; }

int Application::run() {
   Ledger ledger;
   ledger.AddAccount("test");
   for (auto const& a : ledger) {
      std::cout << a << std::endl;
   }
   return 0;
}
#endif
