#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<fstream>
#include<string>
#include"Account_Jianchao_Ji.h"
#include"Stock_Portfolio_Account_Jianchao_Ji.h"
#include <time.h>
#include <stdio.h>
#include"bankAccount_Jianchao_Ji.h"
using namespace std;

void stockManage();
void bankManage();

int main()
{
	
	int choice;
	stockAccount sAccount;
	while (1)
	{
		cout << "Welcome to the Account Management System." << endl;
		cout << "Please select an account to access:" << endl;
		cout << "1. Stock Portfolio Account" << endl;
		cout << "2. Bank Account" << endl;
		cout << "3. Exit" << endl;
		cout << "Please input the choice:";
		cin >> choice;
		cout << endl;
		while (choice < 1 || choice>3)
		{
			cout << "The choice is wrong.Please input a choice a choice between 1 and 3.";
			cin >> choice;
		}

		switch (choice)
		{
		case 1: {stockManage(); break; }
		case 2: {bankManage(); break; }
		case 3: {return 0; }
		}
	}
		system("pause");
		return 0;
	
}


void stockManage()
{
	stockAccount sAccount;
	while (1)
	{
		int choice;
		cout << "Stock Portfolio Account" << endl;
		cout << "Please select an option:" << endl;
		cout << "1. Display the price for a stock symbol" << endl;
		cout << "2. Display the current portfolio" << endl;
		cout << "3. Buy shares" << endl;
		cout << "4. Sell shares" << endl;
		cout << "5. View a graph for the portfolio value" << endl;
		cout << "6. View transaction history" << endl;
		cout << "7. Return to previous menu" << endl;
		cout << "Option" << endl;
		cin >> choice;
		while (choice < 1 || choice>7)
		{
			cout << "The choice is wrong.Please input a choice a choice between 1 and 7.";
			cin >> choice;
		}
		switch (choice)
		{
		case 1:
		{
			sAccount.displayOneStock();
			break;
		}
		case 2:
		{
			sAccount.displayAccount();
			break;
		}
		case 3:
		{

			sAccount.buyStock();
			break;
		}
		case 4:
		{
			sAccount.sellStock();
			break;
		}
		case 5:
		{
			sAccount.displayMatlab();
			break;
		}
		case 6:
		{
			sAccount.displayTransactionHistory();
			break;
		}
		case 7:
		{
			sAccount.saveTotalValue();
			return;
		}
		}
		cout << endl << endl;
	}
}


void bankManage()
{
	bankAccount bAccount;
	while (1)
	{
		int choice;
		cout << "Bank Account" << endl;
		cout << "Please select an option:" << endl;
		cout << "1. View account balance" << endl;
		cout << "2. Deposit money" << endl;
		cout << "3. Withdraw money" << endl;
		cout << "4. Print out history" << endl;
		cout << "5. Return to previous menu" << endl;
		cout << "Option" << endl;
		cin >> choice;
		while (choice < 1 || choice>5)
		{
			cout << "The choice is wrong.Please input a choice a choice between 1 and 7.";
			cin >> choice;
		}
		switch (choice)
		{
		case 1:
		{
			bAccount.viewAccount();
			break;
		}
		case 2:
		{
			bAccount.depositMoney();
			break;
		}
		case 3:
		{
			bAccount.withdrawMoeey();
			break;
		}
		case 4:
		{
			bAccount.printHistory();
			break;
		}
		case 5:
		{
			return;
		}
		}
	}
	cout << endl << endl;
}