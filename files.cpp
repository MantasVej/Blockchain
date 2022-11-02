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
    try {
        std::ifstream fd(failas);
        fd.exceptions(std::ifstream::failbit);
        my_buffer << fd.rdbuf();
        fd.close();
    }
    catch (std::exception& e) {
        cout << "Toks duomenu failas neegzistuoja.";
        exit(0);
    }
    string eil;
    string name, public_key;
    int balance;
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
}

void TransactionGenerator(vector<User>& Users, vector <Transaction>& Transactions, int n) {
    User sender;
    User receiver;
    int senderID;
    vector <User> Temp = Users;
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, Users.size()-1);
    std::uniform_int_distribution<> distribution2(1, 100000);
    std::ofstream fr("transactions.txt");
    std::stringstream my_buffer;
    int amount;
    cout << std::setw(33) << "hash" << std::setw(33) << "|" << std::setw(34) << "sender" << std::setw(34) << " | " << std::setw(33) << "receiver" << std::setw(34) << " | " << "amount" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < n; i++) {
        do {
            senderID = distribution(generator);
            sender = Users[senderID];
            receiver = Users[distribution(generator)];
        } while (sender.getKey() == receiver.getKey());
        amount = distribution2(generator);
        if (ValidateTransaction(Temp[senderID].getBalance(), amount)) {
            Temp[senderID].setBalance(Temp[senderID].getBalance() - amount);
            Transaction T(sender, receiver, amount);
            Transactions.push_back(T);
            my_buffer << T.getId() << " " << T.getSender() << " " << T.getReceiver() << " " << amount << endl;
            cout << T.getId() << " | " << T.getSender() << " | " << T.getReceiver() << " | " << T.getAmount() << endl;
            cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        }
    }
    fr << my_buffer.str();
    fr.close();
}

void ReadTransactions(string failas, vector<Transaction>& Transactions) {
    std::stringstream my_buffer;
    try {
        std::ifstream fd(failas);
        fd.exceptions(std::ifstream::failbit);
        my_buffer << fd.rdbuf();
        fd.close();
    }
    catch (std::exception& e) {
        cout << "Toks duomenu failas neegzistuoja.";
        exit(0);
    }
    string eil;
    string id, sender_key, receiver_key;
    int amount;
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
}