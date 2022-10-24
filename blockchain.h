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
private:
	block(int i, const vector <Transaction> &T) {
		index = i;
		transactions = T;
		timestamp = std::time(nullptr);
		version = "1";
		hash = calculateHash();
	}

	friend class blockchain;
};

class blockchain {
private:
	vector <block> blocks;
	int difficulty;
private:
	blockchain(const vector <Transaction>& T) {
		blocks.push_back(block(0, T));
		difficulty = 5;
	}
	void addBlock(block newBlock)
	{
		newBlock.prev_block_hash = getLastBlock().hash;
		newBlock.mineBlock(difficulty);
		blocks.push_back(newBlock);
	}
	block getLastBlock() const
	{
		return blocks.back();
	}
};