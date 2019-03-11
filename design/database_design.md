# Notes
* Return types for queries:
    * View Objects:
        * http://www.drdobbs.com/cpp/c-view-objects/196513737
        * https://scarvenger.wordpress.com/2008/11/14/c-container-view/
    * https://www.fluentcpp.com/?s=filter+iterator

# Use cases
* Add account
* Add transaction
* List accounts
* List budget categories
* List payees
* List transactions for a payee
* List adjustments for an account
* Sum balance for transaction
* Sum balances for accounts
* Sum balances for budget categories

# Naive Design
```
struct adjustment_t {
   std::string account;
   money_t amount;
}; // struct adjustment_t

struct transaction_t {
   date::year_month_day date;
   std::string memo;
   std::string payee;
   std::vector<adjustment_t> adjustments;
}; // struct transaction_t

std::vector<transaction_t> database;
```

This design captures the essential characteristics of a transaction in that it contains a date, memo, and a list of account adjustments. It is very simple to add a transaction. However, an account cannot be added without adding a transaction. This 

* Add account

Cannot add an account separate from a transaction.

* Add transaction

```
database.insert(transaction);
```
It doesn't get any simpler than this.

* List accounts
```
boost::container::flat_set<std::string> accounts;
for (const auto&& transaction : database) {
   for (const auto&& adjustment : transaction.adjustments) {
      const auto& act_pos = accounts.lower_bound(adjustment.account);
      if (accounts.end() == act_pos || adjustment.account != *act_pos) {
         accounts.insert(act_pos, adjustment.account);
      }
   }
}
```
* List budget categories
* List payees
```
boost::container::flat_set<std::string> payees;
for (const auto&& transaction : database) {
   const auto& payee_pos = payees.lower_bound(transaction.payee);
   if (payees.end() == payee_pos || transaction.payee != *payee_pos) {
      payees.insert(payee_pos, transaction.payee);
   }
} // for (transaction : database)
```
* List transactions for a payee
* List adjustments for an account
```
std::vector<adjustment_t> adjustments;
```
A new type is required to return all the information that needs to be associated with this UC. 
* Sum balance for transaction
* Sum balances for accounts
* Sum balances for budget categories

# Extended Adjustment Table
```
struct adjustment_t {
   date::year_month_day date;
   std::string payee;
   std::string account;
   money_t amount;
}; // struct adjustment_t

std::vector<adjustment_t> database;
```

* Add account

Cannot add an account separate from an adjustment.

* Add transaction
* List accounts
```
boost::container::flat_set<std::string> accounts;
for (const auto&& adjustment : database) {
   const auto& act_pos = accounts.lower_bound(adjustment.account);
   if (accounts.end() == act_pos || adjustment.account != *act_pos) {
      accounts.insert(act_pos, adjustment.account);
   }
}
```
* List budget categories
* List payees
```
boost::container::flat_set<std::string> payees;
for (const auto&& adjustment : database) {
   const auto& payee_pos = payees.lower_bound(adjustment.payee);
   if (payees.end() == payee_pos || adjustment.payee != *payee_pos) {
      payees.insert(payee_pos, adjustment.payee);
   }
} // for (adjustment : database)
```
* List transactions for a payee
* List adjustments for an account
```
std::vector<adjustment_t> result;
std::copy_if(database.begin(),
             database.end(),
             std::back_inserter(result),
             [account](adjustment_t const& other){ return account == other.account; });
```
* Sum balance for transaction
* Sum balance for account
```
money_t zero;
std::accumulate(database.begin(),
                database.end(),
                zero,
                [](money_t const& value, adjustment_t const& adjustment){
                   return value + adjustment.amount;
                });
```
* Sum balances for budget categories

Same as Sum balance for account
