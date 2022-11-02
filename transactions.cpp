#include "Header.h"

vector <Transaction> GetTransactions(vector <Transaction>& pool, int n) {
    vector <Transaction> Transactions;
    std::random_device random_device;
    std::mt19937 generator(random_device());
    int index;
    int size = pool.size();
    for (int i = 0; i < size; i++) {
        if (i == n) break;
        std::uniform_int_distribution<> distribution(0, pool.size() - 1);
        index = distribution(generator);
        Transactions.push_back(pool[index]);
        pool.erase(pool.begin() + index);
    }
    return Transactions;
}
void PrintTransactions(vector <Transaction>& Transactions) {
    std::ofstream fr("test.txt");
    for (auto a : Transactions) {
        fr << a.getId() << endl;
    }
    fr << "-------------------------" << endl;
    fr.close();
}
void printUsers(vector<User>& U) {
    std::stringstream my_buffer;
    std::ofstream fr("users.txt");
    for (int i = 0; i < U.size(); i++) {
        my_buffer << U[i].getName() + " " << U[i].getKey() << " " << U[i].getBalance();
        if (i + 1 != U.size()) my_buffer << endl;
    }
    fr << my_buffer.str();
    fr.close();
}
bool ValidateTransaction(int balance, int amount) {
    if (balance >= amount) return 1;
    else return 0;
}