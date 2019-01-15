# cocles

Cocles uses an internal, custom database for accumulating and querying ledger
entries. This database has the following interface for recording transactions:

```c++
InsertAccount(account_name)
InsertPayee(payee_name)
InsertTransaction(date)
InsertTransfer()

GetBalanceForAccount(account)
GetTransfersForAccount(account)
std::vector<account> GetAccountsWithNameContaining(string)
```
