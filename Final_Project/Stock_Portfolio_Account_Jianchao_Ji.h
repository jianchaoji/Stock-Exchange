#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include"Account_Jianchao_Ji.h"
#include"accountNode_Jianchao_Ji.h"
#include"stockNode_Jianchao_Ji.h"

using std::string;
using std::ofstream;
using std::ifstream;



class stockAccount : public  account
{
public :
	stockAccount();
	virtual void openAccount();
	double returnBalance();
	void setBalance();
	void readFile();
	void readAccount();
	void insert(Node *);
	void deleteNode(string);
	void input();
	void displayAccount();
	void displayTransactionHistory();
	void buyStock();
	bool findStockInAccount(string);
	stockNode returnStockNode(string);
	Node returnNode(string);
	void stockAccountHistory();
	void sellStock();
	bool findStock(string name);
	void displayOneStock();
	void displayMatlab();
	void saveTotalValue();

	int size() const;
private:
	Node *head=NULL;
	Node *tail=NULL;
	ofstream Account;
	ifstream infile;
	ifstream accountBalanceRead;
	ofstream accountBalanceWrite;
	stockNode *myHead = NULL;
	ofstream accountWrite;
	ifstream accountRead;
	ofstream accountHistory;
	ifstream accountHistoryRead;
	ofstream totalValueWrite;
	ifstream totalValueRead;
};