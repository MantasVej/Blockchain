#include "Header.h"

int main()
{
    vector <User> Users;
    vector <Transaction> Transactions;
    ReadUsers("users.txt", Users);
    ReadTransactions("transactions.txt", Transactions);
    return 0;
}