#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

#include <algorithm>
#include <chrono>
#include <iostream>

static int run_unit_tests(int argc, const char* argv[]) {
   doctest::Context context; // initialize

   // defaults
   context.addFilter("test-case-exclude", "*math*"); // exclude test cases with "math" in their name
   context.setOption("abort-after", 5);              // stop test execution after 5 failed assertions
   context.setOption("sort", "name");                // sort the test cases by their name

   context.applyCommandLine(argc, argv);

   // overrides
   context.setOption("no-breaks", true);             // don't break in the debugger when assertions fail

   int result = context.run();                       // run

   if (context.shouldExit()) {          // important !! query flags (and --exit) rely on the user doing this
      exit(result);                                  // propagate the result of the tests
   }
   return result;
}

#if 0
struct event_t {

   event_t() noexcept
      : m_time(std::chrono::high_resolution_clock::now()) {}

private:
   std::chrono::high_resolution_clock::time_point m_time;
};

struct add_account_event_t
   : public event_t
   , public account_t
{

   add_account_event_t(const std::string &name, account_type_t type)
      : event_t()
      , account_t(name, type) {}

}; // struct add_account_event_t

struct add_transaction_event_t
   : public event_t
   , public transaction_t
{

   add_transaction_event_t(const std::string &date)
      : event_t()
      , transaction_t(date) {}

}; // add_transaction_event_t
#endif

template <typename TYPE>
struct identifier_t {

   class passkey {
      friend TYPE;
      passkey() = default;
      passkey(const passkey&) = delete;
   };

   using parent_type = TYPE;
   using element_type = typename parent_type::value_type;
   using size_type = typename parent_type::size_type;

   constexpr explicit identifier_t(passkey, const parent_type& owner, size_type index) noexcept
      : m_owner(owner)
      , m_index(index) {}

   bool operator==(const identifier_t& other) const noexcept {
      return (&m_owner == &other.m_owner) && (m_index == other.m_index);
   }

   bool operator!=(const identifier_t& other) const noexcept {
      return !operator==(other);
   }

   explicit operator size_type() const noexcept {
      return m_index;
   }

   // This method has very large implications for the API
   const element_type& operator*() const {
      return m_owner.m_entries.at(m_index);
   }

private:
   const parent_type& m_owner;
   size_type m_index;
};

template <typename TYPE>
struct stable_table_t {

   using identifier_type = identifier_t<stable_table_t>;
   using value_type = TYPE;
   using container_type = std::vector<TYPE>;
   using size_type = typename std::vector<TYPE>::size_type;
   using difference_type = typename std::vector<TYPE>::difference_type;
   friend identifier_type;

   identifier_type insert(TYPE entry) {
      size_type pos = 0;
      if (m_free_rows.size()) {
         pos = m_free_rows.back();
         m_entries.insert(m_entries.begin() + static_cast<difference_type>(pos), entry);
         m_free_rows.pop_back();
      } else {
         pos = m_entries.size();
         m_entries.push_back(entry);
      }
      return identifier_type({}, *this, pos);
   }

   TYPE remove(identifier_type id) {
      std::size_t index = static_cast<std::size_t>(id);
      auto iter = std::upper_bound(m_free_rows.begin(), m_free_rows.end(), index, std::greater<size_type>());
      m_free_rows.insert(iter, index);
      return m_entries.at(index);
   }

   std::size_t size() const {
      return m_entries.size() - m_free_rows.size();
   }

#if 0
   struct iterator_t {

      explicit iterator_t(size_type index)
         : m_value(index) {}

      iterator_t& operator++() {

         // TODO(tblyons): Skip empty elements
         return *this;
      }

      iterator_t operator++(int) {
         iterator_t result = *this;
         operator++();
         return result;
      }

      bool operator==(iterator_t other) const {
         return (m_value == other.m_iterator);
      }

      bool operator!=(iterator_t other) const {
         return !operator==(other);
      }

   private:
      size_type m_value;
   }; // struct iterator_t

   iterator_t begin() {
      // Should this provide the first not deleted element?
      return iterator_t(0);
   }

   iterator_t end() {
      return iterator_t(size());
   }
#endif

   bool is_used(identifier_type id) const {
      size_type index = static_cast<size_type>(id);
      auto iter = std::upper_bound(m_free_rows.begin(), m_free_rows.end(), index, std::greater<size_type>());
      return index < m_entries.size() && *iter != index;
   }

private:
   container_type m_entries;
   std::vector<size_type> m_free_rows; // Sorted in reverse order
}; // struct stable_table_t

template <typename TYPE>
struct table_t {

   using identifier_type = identifier_t<table_t>;
   using value_type = TYPE;
   using container_type = std::vector<TYPE>;
   using size_type = typename std::vector<TYPE>::size_type;

   identifier_type insert(TYPE entry) {
      size_type pos = m_entries.size();
      m_entries.push_back(entry);
      return identifier_type({}, *this, pos);
   }

   TYPE remove(identifier_type id) {
      size_type index = static_cast<size_type>(id);
      TYPE result = m_entries.at(index);
      m_entries.erase(m_entries.begin() + index);
      return result;
   }

   size_type size() const {
      return m_entries.size();
   }

private:
   std::vector<TYPE> m_entries;
}; // struct table_t

enum class account_type_t {
   INCOME_EXPENSE,
   BUDGET_CATEGORY,
   BUDGETED_ACCOUNT,
   UNBUDGETED_ACCOUNT
};

struct account_t {

   account_t(std::string name, account_type_t type)
      : m_type(type)
      , m_name(name) {}

   const std::string& name() const {
      return m_name;
   }

   account_type_t type() const {
      return m_type;
   }

private:
   account_type_t m_type;
   std::string m_name;
}; // struct account_t

struct transaction_t {

   transaction_t(std::string date)
      : m_date(date) {}

   const std::string& date() const {
      return m_date;
   }

private:
   std::string m_date;
   //std::string m_memo;
}; // struct transaction_t

struct adjustment_t {
   using transaction_id_t = stable_table_t<transaction_t>::identifier_type;
   using account_id_t = stable_table_t<account_t>::identifier_type;

   adjustment_t(transaction_id_t transaction_id, account_id_t account_id)
      : m_transaction_id(transaction_id)
      , m_account_id(account_id) {}

private:
   transaction_id_t m_transaction_id;
   account_id_t m_account_id;
}; // struct adjustment_t

#if 0
struct ledger_impl_t {

   ledger_impl_t(std::string filename) {
      static_cast<void>(filename);
   }

   ~ledger_impl_t() noexcept {}

   void append_event(const add_account_event_t &event) {
      replay_event(event);
   }

   void replay_event(const add_account_event_t &event) {
      auto account_ptr = std::make_unique<account_t>(event.name(), event.type());
      auto iter = std::upper_bound(m_accounts.cbegin(), m_accounts.cend(), account_ptr, [](const std::unique_ptr<account_t> &a, const std::unique_ptr<account_t> &b) -> bool { return a->name() < b->name(); });
      if (m_accounts.cend() == iter || (*iter)->name() != event.name()) {
         m_accounts.insert(iter, std::move(account_ptr));
      }
   }

   std::pair<std::vector<std::unique_ptr<account_t>>::const_iterator, std::vector<std::unique_ptr<account_t>>::const_iterator> get_accounts_starting_with(const std::string &prefix) const {
      const auto& begin = std::lower_bound(m_accounts.cbegin(), m_accounts.cend(), prefix, [](const std::unique_ptr<account_t> &acnt_ptr, const std::string &str) -> bool { return str < acnt_ptr->name(); });
      const auto& end = std::upper_bound(m_accounts.cbegin(), m_accounts.cend(), prefix, [](const std::string &str, const std::unique_ptr<account_t> &acnt_ptr) -> bool { return str < acnt_ptr->name(); });
      return std::make_pair(begin, end);
   }

   account_t* find_account(const std::string &name) const {
      auto iter = std::upper_bound(m_accounts.cbegin(), m_accounts.cend(), name, [](const std::string &a, const std::unique_ptr<account_t> &b) -> bool { return a < b->name(); });
      if (m_accounts.cend() == iter || (name != (*iter)->name())) {
         return nullptr;
      }
      return iter->get();
   }

private:
   std::vector<std::unique_ptr<account_t>> m_accounts;
   std::vector<adjustment_t> m_adjustments;
   std::vector<transaction_t> m_transactions;
}; // struct ledger_impl_t

struct ledger_t {

   explicit ledger_t(std::string filename)
      : m_impl(std::make_unique<ledger_impl_t>(filename)) {}

   ~ledger_t() noexcept {}

   void add_account(const std::string &name) {
      m_impl->append_event(add_account_event_t(name, account_type_t::INCOME_EXPENSE));
   }

private:
   std::unique_ptr<ledger_impl_t> m_impl;
}; // struct ledger_t
#endif

struct ledger_t {
   stable_table_t<transaction_t> transaction_table;
   stable_table_t<account_t>         account_table;
          table_t<adjustment_t>   adjustment_table;

#if 0
   template <typename ... TYPES>
   std::vector<std::tuple<TYPES...>> select(std::function<std::tuple<TYPES...>(const stable_table_t<transaction_t>& transactions,
                                                                               const stable_table_t<account_t>& accounts,
                                                                               const table_t<adjustment_t>& adjustments))
#endif
};

template <typename ... TYPES>
std::vector<std::tuple<TYPES...>> make_vector_of_tuples(TYPES... args) {
   std::vector<std::tuple<TYPES...>> result;
   for (int i = 0; i < 5; ++i) {
      result.emplace_back(args...);
   }
   return result;
}

extern "C" int main(int argc, const char* argv[]) {
   int unit_test_results = run_unit_tests(argc, argv);

   ledger_t ledger;
   //ledger_t ledger("cocles.log");
   //ledger.add_account("Checking");

   auto l = make_vector_of_tuples<int, double, std::string>(5, 0.25, "hello");
   for (auto i : l) {
      std::cout << std::get<0>(i) << " " << std::get<1>(i) << " " << std::get<2>(i) << std::endl;
   }

   auto tid = ledger.transaction_table.insert({ "1999-12-31" });
   auto aid = ledger.account_table.insert({ "Checking", account_type_t::INCOME_EXPENSE });
   ledger.adjustment_table.insert({ tid, aid });
   std::cout << ledger.adjustment_table.size() << std::endl;
   std::cout << (*tid).date() << std::endl;
   return unit_test_results; // the result from doctest is propagated here as well
}
