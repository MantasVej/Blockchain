#pragma once
#include "sha256.h"
#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>

using std::cout;
using std:: endl;
using std::string;
using std::vector;

class User {
private:
	string name;
	string public_key;
	int balance;
private:
	string hash(string s) {
		SHA256 sha256;
		return sha256(s);
	}
public:
	User() { name = ""; public_key = ""; balance = 0; }
	~User() {}
	void setName(string n) { name = n; public_key = hash(n); }
	void setBalance(int w) { balance = w; }
	string getName() { return name; }
	string getKey() { return public_key; }
	int getBalance() { return balance; }

};

class Transaction {
private:
	string id;
	string sender;
	string receiver;
	int amount;
private:
	string hash(string s) {
		SHA256 sha256;
		return sha256(s);
	}
public:
	Transaction() { id = ""; sender = ""; receiver = ""; amount = 0; }
	Transaction(User& U1, User& U2, int n) {
		sender = U1.getKey();
		receiver = U2.getKey();
		amount = n;
		id = hash(sender + receiver + std::to_string(amount));
	}
	Transaction(string i, string s, string r, int a) {
		id = i;
		sender = s;
		receiver = r;
		amount = a;
	}
	~Transaction() {}
	string getId() { return id; }
	string getSender() { return sender; }
	string getReceiver() { return receiver; }
	int getAmount() { return amount; }

};

void UserGenerator(int n, vector<User>& Users);
void ReadUsers(string failas, vector<User>& Users);
void TransactionGenerator(vector<User>& Users, vector <Transaction>& Transactions, int n);
void ReadTransactions(string failas, vector<Transaction>& Transactions);