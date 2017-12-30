#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include"bankAccount_Jianchao_Ji.h"
#include<fstream>
#include<iomanip>
#include<string>
#include <time.h>

using namespace std;

bankAccount::bankAccount()
{
	openAccount();
	balance = returnBalance();
}

void  bankAccount::openAccount()
{
	accountBalanceRead.open("Balance.txt", ios::in);
	if (!accountBalanceRead)
	{
		accountBalanceWrite.open("Balance.txt");
		accountBalanceWrite << 10000;
		accountBalanceWrite.close();
		return;
	}
	accountBalanceRead.close();
}

double bankAccount::returnBalance()
{
	double result;
	accountBalanceRead.open("Balance.txt");
	accountBalanceRead >> result;
	accountBalanceRead.close();
	return result;
}

void bankAccount::setBalance()
{
	double result;
	result = balance;
	accountBalanceWrite.open("Balance.txt");
	accountBalanceWrite << result;
	accountBalanceWrite.close();
}

void bankAccount::viewAccount()
{
	cout << "You have $" << returnBalance() << " in your bank account." << endl;
}

void bankAccount::depositMoney()
{
	double deposit;
	double result = returnBalance();
	cout << "Please input the amount you wish to deposit:";
		cin >> deposit;
		result += deposit;
		balance = result;
		this->setBalance();
		accountBalanceWrite.open("bankHistoryDate.txt", ios::app);
		time_t tt = time(NULL);
		tm* t = localtime(&tt);
		accountBalanceWrite << setiosflags(ios::fixed) << setprecision(2) << left << "   " << "Deposit" << "   " << "$" << deposit
			<< " " << t->tm_mon + 1 << "/" << t->tm_mday << "/" << t->tm_year + 1900 << "   " << "$" << returnBalance() << endl;
		accountBalanceWrite.close();
		accountBalanceWrite.open("bankHistoryTime.txt", ios::app);

		accountBalanceWrite << setiosflags(ios::fixed) << setprecision(2) << left << "   " << "Deposit" << "   " << "$" << deposit
			                << " " << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << "   " << "$" << returnBalance() << endl;
		accountBalanceWrite.close();

}

void bankAccount::withdrawMoeey()
{
	double withdraw;
	double result = returnBalance();
	cout << "Please input the amount you wish to withdraw:";
	cin >> withdraw;
	if (withdraw > result)
	{
		cout << "Insufficient Money!" << endl;
		return;
	}
	result -= withdraw;
	balance = result;
	this->setBalance();
    accountBalanceWrite.open("bankHistoryDate.txt",ios::app);
	time_t tt = time(NULL);
	tm* t = localtime(&tt);
	accountBalanceWrite << setiosflags(ios::fixed) << setprecision(2) << left << "   " << "Withdraw" << "   " << "$" << withdraw
		<< " " << t->tm_mon + 1 << "/" << t->tm_mday << "/" << t->tm_year + 1900 << "   " << "$" << returnBalance()<<endl;
	accountBalanceWrite.close();
	accountBalanceWrite.open("bankHistoryTime.txt", ios::app);

	accountBalanceWrite << setiosflags(ios::fixed) << setprecision(2) << left << "   " << "Withdraw" << "   " << "$" << withdraw
		               << " "<< t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << "   " << "$"<<returnBalance()<<endl;
	accountBalanceWrite.close();

}

void bankAccount::printHistory()
{
	string s;
	int i = 0;
	int choice;
	cout << "You want to print history in date or in time." << endl;
	cout << "1.In date." << endl;
	cout << "2.In time." << endl;
	cin >> choice;
	while (choice < 1 || choice>2)
	{
		cout << "The choice is wrong.Please input a choice a choice between 1 and 2.";
		cin >> choice;
	}
	if (choice == 1)
	{
		accountBalanceRead.open("bankHistoryDate.txt");
	}

	if (choice == 2)
	{
		accountBalanceRead.open("bankHistoryTime.txt");
	}
	cout << left << setw(15) << "Event" << setw(8) << "Amount" << "       " << "Time" <<"            "<<"Balance"<<endl;
	while (accountBalanceRead >> s)
	{
		cout << left << setw(15) << s;
		i++;
		if (i % 4 == 0)
			cout << endl;
	}
	cout << endl;
	accountBalanceRead.close();
}