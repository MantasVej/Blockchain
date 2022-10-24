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
	block(const vector <Transaction> &T) {
		timestamp = std::time(nullptr);
		version = "1";
		nonce = 0;
		transactions = T;
		mercle_root_hash = mercleTree(T);
		hash = calculateHash();
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

		cout << "Block mined: " << hash << endl;
	}
	friend class blockchain;
};

class blockchain {
private:
	vector <block> blocks;
	int difficulty;
public:
	blockchain(const vector <Transaction>& T) {
		difficulty = 5;
		block Genesis_block(T);
		Genesis_block.index = 0;
		Genesis_block.prev_block_hash = sha256("");
		Genesis_block.mineBlock(difficulty);
		blocks.push_back(Genesis_block);
	}
	void addBlock(block newBlock)
	{
		newBlock.prev_block_hash = getLastBlock().hash;
		newBlock.index = getLastBlock().index + 1;
		newBlock.mineBlock(difficulty);
		blocks.push_back(newBlock);
	}
private:
	block getLastBlock() const
	{
		return blocks.back();
	}
};