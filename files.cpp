#include "Header.h"

void UserGenerator(int n, vector<User>& Users) {
    User U;
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(100, 1000000);
    std::ofstream fr("users.txt");
    std::stringstream my_buffer;
    for (int i = 0; i < n; i++) {
        U.setName("Vartotojas" + std::to_string(i + 1));
        U.setBalance(distribution(generator));
        Users.push_back(U);
        my_buffer << U.getName() + " " << U.getKey() << " " << U.getBalance();
        if (i + 1 != n) my_buffer << endl;
    }
    fr << my_buffer.str();
    fr.close();
}

void ReadUsers(string failas, vector<User>& Users) {
    User U;
    std::stringstream my_buffer;
    std::ifstream fd(failas);
    string eil;
    string name, public_key;
    int balance;
    my_buffer << fd.rdbuf();
    while (my_buffer) {
        if (!my_buffer.eof()) {
            std::getline(my_buffer, eil);
            std::stringstream s(eil);
            s >> name >> public_key >> balance;
            U.setName(name);
            U.setBalance(balance);
            Users.push_back(U);
        }
        else break;
    }
    fd.close();
}

void TransactionGenerator(vector<User>& Users, vector <Transaction>& Transactions, int n) {
    User sender;
    User receiver;
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, Users.size()-1);
    std::uniform_int_distribution<> distribution2(1, 10000);
    std::ofstream fr("transactions.txt");
    std::stringstream my_buffer;
    int amount;
    for (int i = 0; i < n; i++) {
        do {
            sender = Users[distribution(generator)];
            receiver = Users[distribution(generator)];
        } while (sender.getKey() == receiver.getKey());
        amount = distribution2(generator);
        Transaction T(sender, receiver, amount);
        Transactions.push_back(T);
        my_buffer << T.getId() << " " << T.getSender() << " " << T.getReceiver() << " " << amount << endl;
    }
    fr << my_buffer.str();
    fr.close();
}

void ReadTransactions(string failas, vector<Transaction>& Transactions) {
    std::stringstream my_buffer;
    std::ifstream fd(failas);
    string eil;
    string id, sender_key, receiver_key;
    int amount;
    my_buffer << fd.rdbuf();
    while (my_buffer) {
        if (!my_buffer.eof()) {
            std::getline(my_buffer, eil);
            std::stringstream s(eil);
            s >> id >> sender_key >> receiver_key >> amount;
            Transaction T (id, sender_key, receiver_key, amount);
            Transactions.push_back(T);
        }
        else break;
    }
    fd.close();
}