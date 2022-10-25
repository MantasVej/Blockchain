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