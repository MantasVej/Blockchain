#include "Header.h"
#include "blockchain.h"

int main()
{
    vector <User> Users;
    vector <Transaction> Transactions;
   // ReadUsers("users.txt", Users);
    ReadTransactions("transactions100.txt", Transactions);
    blockchain B(Transactions);
    while (Transactions.size() > 0) {
        B.addBlock(Transactions);
    }
    B.print();
    return 0;
}