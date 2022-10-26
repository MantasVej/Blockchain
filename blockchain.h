#pragma once
#include "Header.h"
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
		Transactions = GetTransactions(pool, 10);
		timestamp = std::time(nullptr);
		version = "1";
		nonce = 0;
		difficulty = 5;
		transactions = Transactions;
		mercle_root_hash = mercleTree(T);
		hash = calculateHash();
		T = pool;
	}
private:
	inline string calculateHash() {
		std::stringstream s;
		s << prev_block_hash << timestamp << version << mercle_root_hash << nonce << difficulty;
		return sha256(s.str());
	}
	string mercleTree(const vector <Transaction>& T) {
		//TODO: mercle tree implementation
		std::stringstream s;
		for (auto a : T) {
			s << a.getId();
		}
		return sha256(s.str());
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
	friend class blockchain;
};

class blockchain {
private:
	vector <block> blocks;
public:
	blockchain(vector <Transaction>& T) {
		block Genesis_block(T);
		Genesis_block.index = 0;
		Genesis_block.prev_block_hash = sha256("");
		Genesis_block.mineBlock(Genesis_block.difficulty);
		blocks.push_back(Genesis_block);
	}
	void addBlock(vector <Transaction>& T)
	{
		block newBlock(T);
		newBlock.prev_block_hash = getLastBlock().hash;
		newBlock.index = getLastBlock().index + 1;
		newBlock.mineBlock(newBlock.difficulty);
		blocks.push_back(newBlock);
	}
	void addBlocks(vector <Transaction>& T) {
		while (T.size() > 0) {
			addBlock(T);
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
	void manageBlockchain(vector <Transaction>& Transactions) {
		int input;
		int idB, idT;
		while (1) {
			cout << "Kurti bloka                             1" << endl;
			cout << "Kurti blokus kol yra laisvu transakciju 2" << endl;
			cout << "Spausdinti bloka                        3" << endl;
			cout << "Spausdinti transakcija                  4" << endl;
			cout << "Baigti                                  0" << endl;
			cin >> input;
			if (input == 0) { printBlockchain(); break; }
			else if (input == 1) { if (Transactions.size() != 0) addBlock(Transactions); else cout << "Transakciju pool'as tuscias" << endl; }
			else if (input == 2) { if (Transactions.size() != 0) addBlocks(Transactions); else cout << "Transakciju pool'as tuscias" << endl; }
			else if (input == 3) { cout << "Iveskite bloko id "; cin >> idB; printBlock(idB); }
			else if (input == 4) { cout << "Iveskite bloko id "; cin >> idB; cout << "Iveskite transakcijos id "; cin >> idT; printTransaction(idB, idT); }
			else cout << "Netinkama ivestis" << endl;
		}
	}
private:
	block getLastBlock() const
	{
		return blocks.back();
	}
};