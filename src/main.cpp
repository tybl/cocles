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

#include <iostream>
#include <iterator>
#include <list>
#include <regex>
#include <string>
#include <vector>

template<class I>
struct Iterator {
   using T = typename std::iterator_traits<I>::reference;

   Iterator(I value) : m_value(value) { }
   T& operator*() { return *m_value; }
   Iterator& operator++() { return *this; }
   operator T() { return *m_value; }
private:
   I m_value;
}; // struct Iterator

template<class T>
struct View {

   T* begin() { return m_list.begin(); }
   T* end()   { return m_list.end(); }
   void push_back(T* value) { m_list.push_back(value); }
private:
   std::vector<T*> m_list;
}; // struct View

struct Ledger {
   using Account = std::string;
   using AccountList = std::list<Account>;

   void insert(Account a) { m_accounts.push_back(a); }

   View<Account> accounts(std::string ) {
      View<Account> result;
      for (auto i = m_accounts.begin(); i != m_accounts.end(); ++i) {
         result.push_back(&*i);
      }
      return result;
   }

private:
   AccountList m_accounts;
}; // struct Ledger

int main(int argc, const char* argv[], const char* envp[]) {
   static_cast<void>(argc);
   static_cast<void>(argv);
   static_cast<void>(envp);

   Ledger ledger;
   ledger.insert("asset");
   ledger.insert("liability");
   ledger.insert("income");
   ledger.insert("expense");
   for (auto a : ledger.accounts("unused")) {
      std::cout << a << "\n";
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
