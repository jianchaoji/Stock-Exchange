#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include"Account_Jianchao_Ji.h"

using std::ifstream;
using std::ofstream;

class bankAccount : public  account
{
public:
	bankAccount();
	double returnBalance();
	void setBalance();
	virtual void openAccount();
	void viewAccount();
	void depositMoney();
	void withdrawMoeey();
	void printHistory();
private:
	ifstream accountBalanceRead;
	ofstream accountBalanceWrite;
};
