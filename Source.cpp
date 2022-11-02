#include "Header.h"
#include "blockchain.h"

void Blockchain(vector<User>& Users, vector <Transaction>& Transactions) {
    int input;
    while (1) {
        cout << "Kurti blockchain'a? 1 | 0 ? "; cin >> input;

        if (input == 1) {
            blockchain B(Users, Transactions);
            B.manageBlockchain(Users, Transactions);
            break;
        }
        else if (input == 0) break;
        else cout << "Netinkama ivestis" << endl;
    }
}

int main()
{
    vector <User> Users;
    vector <Transaction> Transactions;
    int input;
    int n;
    string file;
    while (1) {
        cout << "Generuoti nauja transakciju pool'a 1 | 0 ? "; cin >> input;
        if (input == 1) {
            cout << "Generuoti naujus vartotojus 1 | 0 ? "; cin >> input;
            if (input == 1) {
                cout << "Iveskite vartotoju skaiciu: "; cin >> n; UserGenerator(n, Users);
                cout << "Iveskite transakciju skaiciu: "; cin >> n; TransactionGenerator(Users, Transactions, n);
                Blockchain(Users, Transactions);
                break;
            }
            else if (input == 0) {
                cout << "Iveskite vartotoju faila: "; cin >> file;
                ReadUsers(file, Users);
                cout << "Iveskite transakciju skaiciu: "; cin >> n; TransactionGenerator(Users, Transactions, n);
                Blockchain(Users, Transactions);
                break;
            }
            else cout << "netinkama ivestis" << endl;
        }
        else if (input == 0) { 
            cout << "Iveskite transakciju faila: "; cin >> file;
            ReadUsers("users.txt", Users);
            ReadTransactions(file, Transactions);
            Blockchain(Users, Transactions);
            break;
        }
        else cout << "Netinkama ivestis" << endl;
    }
    return 0;
}

