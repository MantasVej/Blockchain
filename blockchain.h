#pragma once
#include "Header.h"
#include "Merkle.h"
SHA256 sha256;
class block {
private:
	string hash;
	int index;
	string prev_block_hash;
	std::time_t timestamp;
	string version;
	string mercle_root_hash;
	int nonce;
	int difficulty;
	vector <Transaction> transactions;
public:
	block(vector <Transaction> &T) {
		vector <Transaction> pool = T;
		vector <Transaction> Transactions;
		Transactions = GetTransactions(pool, 100);
		timestamp = std::time(nullptr);
		version = "1";
		nonce = 0;
		difficulty = 5;
		transactions = Transactions;
		mercle_root_hash = mercleTree(transactions);
		hash = "";
		T = pool;
	}
private:
	inline string calculateHash() {
		std::stringstream s;
		s << prev_block_hash << timestamp << version << mercle_root_hash << nonce << difficulty;
		return sha256(s.str());
	}
	string mercleTree(const vector <Transaction>& T) {
		MerkleTree M(T);
		return M.getRoot();
	}
	void mineBlock(int difficulty)
	{
		string str;
		str.append(difficulty, '0');
		do
		{
			nonce++;
			hash = calculateHash();
		} while (hash.substr(0, difficulty) != str);
		cout << "ID |" << std::setw(33) << "hash" << std::setw(34) << "|" << std::setw(33) << "mercle root" << std::setw(34) << "|" << " timestamp  " << "|" << " difficulty " << "|" << "   nonce  " << "|" << " version" << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << index << "  | " << hash << " | " << mercle_root_hash << " | " << timestamp << " | " << std::setw(6) << difficulty << std::setw(7) << " | " << std::setw(8) << std::right << nonce << " | " << version << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	}
	void mineBlock(int difficulty, int maxNonce)
	{
		string str;
		str.append(difficulty, '0');
		do
		{
			if (maxNonce == nonce) { hash = ""; return; }
			nonce++;
			hash = calculateHash();
		} while (hash.substr(0, difficulty) != str);
		cout << "ID |" << std::setw(33) << "hash" << std::setw(34) << "|" << std::setw(33) << "mercle root" << std::setw(34) << "|" << " timestamp  " << "|" << " difficulty " << "|" << "   nonce  " << "|" << " version" << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << index << "  | " << hash << " | " << mercle_root_hash << " | " << timestamp << " | " << std::setw(6) << difficulty << std::setw(7) << " | " << std::setw(8) << std::right << nonce << " | " << version << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	}
	friend class blockchain;
};

class blockchain {
private:
	vector <block> blocks;
public:
	blockchain(vector<User>& U, vector <Transaction>& T) {
		block Genesis_block(T);
		Genesis_block.index = 0;
		Genesis_block.prev_block_hash = sha256("");
		Genesis_block.mineBlock(Genesis_block.difficulty);
		updateBalances(U, Genesis_block.transactions);
		blocks.push_back(Genesis_block);
	}
	void addBlock(vector<User>& U, vector <Transaction>& T)
	{
		mineFive(U, T);
		/*block newBlock(T);
		newBlock.prev_block_hash = getLastBlock().hash;
		newBlock.index = getLastBlock().index + 1;
		newBlock.mineBlock(newBlock.difficulty);
		updateBalances(U, newBlock.transactions);
		blocks.push_back(newBlock);*/
	}
	void addBlocks(vector<User>& U, vector <Transaction>& T) {
		while (T.size() > 0) {
			addBlock(U, T);
		}
	}
	void printBlockchain() {
		std::ofstream fr("blockchain.txt");
		std::stringstream my_buffer;
		my_buffer << "ID |" << std::setw(33) << "hash" << std::setw(34) << "|" << std::setw(33) << "mercle root" << std::setw(34) << "|" << " timestamp  " << "|" << " difficulty " << "|" << "   nonce  " << "|" << " version" << endl;
		my_buffer << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		for (auto a : blocks) {
			my_buffer << a.index << "  | " << a.hash << " | " << a.mercle_root_hash << " | " << a.timestamp << " | " << std::setw(6) << a.difficulty << std::setw(7) << " | " << std::setw(8) << std::right << a.nonce << " | " << a.version << endl;
			my_buffer << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		}
		fr << my_buffer.str();
		fr.close();
	}
	void printBlock(int i) {
		if ((i > blocks.size()) || (i < 0)) { cout << "Toks blokas neegzistuoja" << endl;  return; }
		cout << "ID  |" << std::setw(33) << "hash" << std::setw(34) << "|" << std::setw(33) << "mercle root" << std::setw(34) << "|" << " timestamp  " << "|" << " difficulty " << "|" << "   nonce  " << "|" << " version" << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << blocks[i].index << "   | " << blocks[i].hash << " | " << blocks[i].mercle_root_hash << " | " << blocks[i].timestamp << " | " << std::setw(6) << blocks[i].difficulty << std::setw(7) << " | " << std::setw(8) << std::right << blocks[i].nonce << " | " << blocks[i].version << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	}
	void printTransaction(int iB, int iT) {
		if ((iB > blocks.size()) || (iB < 0)) { cout << "Toks blokas neegzistuoja" << endl;  return; }
		if ((iT > blocks[iB].transactions.size()) || (iT < 0)) { cout << "Tokia transakcija neegzistuoja" << endl;  return; }
		cout << std::setw(33) << "hash" << std::setw(33) << "|" << std::setw(34) << "sender" << std::setw(34) << " | " << std::setw(33) << "receiver" << std::setw(34) << " | " << "amount" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << blocks[iB].transactions[iT].getId() << " | " << blocks[iB].transactions[iT].getSender() << " | " << blocks[iB].transactions[iT].getReceiver() << " | " <<  blocks[iB].transactions[iT].getAmount() << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	}
	void manageBlockchain(vector<User>& Users, vector <Transaction>& Transactions) {
		int input;
		int idB, idT;
		while (1) {
			cout << "Kurti nauja bloka                       1" << endl;
			cout << "Kurti blokus kol yra laisvu transakciju 2" << endl;
			cout << "Spausdinti bloka                        3" << endl;
			cout << "Spausdinti transakcija                  4" << endl;
			cout << "Baigti                                  0" << endl;
			cin >> input;
			if (input == 0) { printBlockchain(); break; }
			else if (input == 1) { if (Transactions.size() != 0) addBlock(Users, Transactions); else cout << "Transakciju pool'as tuscias" << endl; }
			else if (input == 2) { if (Transactions.size() != 0) addBlocks(Users, Transactions); else cout << "Transakciju pool'as tuscias" << endl; }
			else if (input == 3) { cout << "Iveskite bloko id "; cin >> idB; printBlock(idB); }
			else if (input == 4) { cout << "Iveskite bloko id "; cin >> idB; cout << "Iveskite transakcijos id "; cin >> idT; printTransaction(idB, idT); }
			else cout << "Netinkama ivestis" << endl;
		}
	}
	void mineFive(vector<User>& U, vector <Transaction>& T) {
		vector <block> b;
		vector <int> index = {0, 1, 2, 3, 4};
		int maxNonce = 100000;
		vector <Transaction> Transactions;
		vector <vector <Transaction>> pool;
		for (int i = 0; i < 5; i++) {
			vector <Transaction> Temp = T;
			Transactions = GetTransactions(Temp, 100);
			block B(Transactions);
			B.prev_block_hash = getLastBlock().hash;
			B.index = getLastBlock().index + 1;
			b.push_back(B);
			pool.push_back(Temp);
		}
		while (1) {
			std::random_shuffle(index.begin(), index.end());
			for (int i : index) {
				b[i].mineBlock(b[i].difficulty, maxNonce);
				if (b[i].hash != "") {
					updateBalances(U, b[i].transactions);
					blocks.push_back(b[i]);
					T = pool[i];
					return;
				}
			}
			maxNonce += 100000;
		}

	}
private:
	block getLastBlock() const
	{
		return blocks.back();
	}
	void updateBalances(vector<User>& U, vector <Transaction>& T) {
		for (auto t : T) {
			for (int i = 0; i < U.size(); i++) {
				if (U[i].getKey() == t.getSender()) U[i].setBalance(U[i].getBalance() - t.getAmount());
				if (U[i].getKey() == t.getReceiver()) U[i].setBalance(U[i].getBalance() + t.getAmount());
			}
		}
		printUsers(U);
	}
};