#include "Header.h"
#include "blockchain.h"

int main()
{
    vector <User> Users;
    vector <Transaction> Transactions;
   // ReadUsers("users.txt", Users);
    
    ReadTransactions("transactions100.txt", Transactions);
    blockchain B(Transactions);
    B.manageBlockchain(Transactions);
    return 0;
}