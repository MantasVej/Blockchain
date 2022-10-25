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

		cout << index << " Block mined: " << hash << endl;
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
	void print() {
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
private:
	block getLastBlock() const
	{
		return blocks.back();
	}
};