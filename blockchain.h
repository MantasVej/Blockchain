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
		index = 0;
		transactions = T;
		timestamp = std::time(nullptr);
		version = "1";
		nonce = 0;
		hash = calculateHash();
	}
private:
	inline string calculateHash() {
		std::stringstream s;
		s << prev_block_hash << timestamp << version << mercle_root_hash << nonce << difficulty;
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
		blocks.push_back(block(T));
		difficulty = 5;
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