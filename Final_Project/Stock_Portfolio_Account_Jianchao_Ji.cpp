#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include"Stock_Portfolio_Account_Jianchao_Ji.h"
#include<fstream>
#include<iomanip>
#include<string>
#include <time.h>
#include"accountNode_Jianchao_Ji.h"
#include <sstream>
#include<vector>
#include"stockNode_Jianchao_Ji.h"
#include<stdlib.h>
#include<yvals.h>
#if(_MSC_VER >=1600)
#define _STDC_utf_16__
#endif
#include"mex.h"
#include<engine.h>

#pragma comment(lib,"libmx.lib")
#pragma comment(lib,"libmex.lib")
#pragma comment(lib,"libeng.lib")

using namespace std;

/*class stockNode is used to store the information of the stock*/

stockAccount::stockAccount()
{ 
	openAccount();
	balance = returnBalance();
	head = NULL;
	tail = NULL;
}

template <class Type>
Type stringToNum(const string& str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}

void  stockAccount::openAccount()
{
	accountBalanceRead.open("Balance.txt",ios::in);
	if (!accountBalanceRead)
	{
		accountBalanceWrite.open("Balance.txt");
		accountBalanceWrite << 10000;
		accountBalanceWrite.close();
		return;
	}
	accountBalanceRead.close();
}

double stockAccount::returnBalance()
{
	double result;
	accountBalanceRead.open("Balance.txt");
	accountBalanceRead >> result;
	accountBalanceRead.close();
	return result;
}

void stockAccount::setBalance()
{
	double result;
	result = balance;
	accountBalanceWrite.open("Balance.txt");
	accountBalanceWrite << result;
	accountBalanceWrite.close();
}

/*Function readFile is used to put the information of the stock into stockNode*/
void stockAccount::readFile()
{
	int randCount = rand();
	int i = 0;
	string s;
	stockNode *ptr=NULL;
	string store[3];
	
	if (randCount % 2 == 0)
	{
		infile.open("Result 1.txt");
	}
	else if (randCount % 2 == 1)
	{
		infile.open("Result 2.txt");
	}
	while (infile>>s)
	{
		if (myHead == NULL)
		{
			if (i % 3 == 0)
			{
				myHead = new stockNode();
				myHead->companyName = s;
			}
			else if (i % 3 == 1)
			{
				myHead->stockPrice = stringToNum<double>(s);
			}
			else if (i % 3 == 2)
			{
				myHead->date = s;
			}
			i++;
			ptr = myHead;
		}
		else
		{
			if (i % 3 == 0)
			{
				ptr->myNext = new stockNode();
				ptr = ptr->myNext;
				ptr->companyName = s;
			}
			else if (i % 3 == 1)
			{
				ptr->stockPrice = stringToNum<double>(s);
			}
			else if (i % 3 == 2)
			{
				ptr->date = s;
			}
			i++;
		}
	}
	infile.close();

}

/*This function is used to read the current account information*/
void stockAccount::readAccount()
{
	string s;
	Node *ptr = NULL;
	int i = 0;
	accountRead.open("Stock_Portfolio_Account.txt");
	while (accountRead >> s)
	{
		if (head == NULL)
		{
			if (i % 4 == 0)
			{
				tail = head = new Node();
				head->name = s;
				i++;
			}
			else if (i % 4 == 1)
			{
				head->numberOfShare = stringToNum<double>(s);
				i++;
			}
			else if (i % 4 == 2)
			{
				head->price = stringToNum<double>(s);
				i++;
			}
			else if (i % 4 == 3)
			{
				head->totalValue = stringToNum<double>(s);
				i++;
			}
			//ptr = tail;
		}
		else if(head==tail)
		{
			if (i % 4 == 0)
			{
				tail = new Node();
				head->next = tail;
				tail->previous = head;
				tail->name = s;
				i++;
			}
			else if (i % 4 == 1)
			{
				tail->numberOfShare = stringToNum<double>(s);
				i++;
			}
			else if (i % 4 == 2)
			{
				tail->price = stringToNum<double>(s);
				i++;
			}
			else if (i % 4 == 3)
			{
				tail->totalValue = stringToNum<double>(s);
				i++;
			}
		}
		else
		{
			if (i % 4 == 0)
			{
				ptr = tail;
				tail = new Node();
				ptr->next = tail;
				tail->previous = ptr;
				tail->name = s;
				i++;
			}
			else if (i % 4 == 1)
			{
				tail->numberOfShare = stringToNum<double>(s);
				i++;
			}
			else if (i % 4 == 2)
			{
				tail->price = stringToNum<double>(s);
				i++;
			}
			else if (i % 4 == 3)
			{
				tail->totalValue = stringToNum<double>(s);
				i++;
			}
		}
	}
	accountRead.close();
}
int stockAccount::size() const
{
	int length = 0;
	Node *ptr =head;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		length++;
	}
	return length;
}

void stockAccount::displayAccount()
{
	int i = 0;
	double value=0;
	if (head == NULL)
	{
		this->readAccount();
	}
	Node *ptr = head;
	cout << "Cash balance = $" << this->returnBalance() << endl;
	cout << "Company-Symbol" << "    " << "Amount" << "    " << "Price-per-share/$" << "   " << "Total value/$" << endl;
	while (ptr != NULL)
	{
		cout  <<  left<<setw(18)<<ptr->name << setw(10) << ptr->numberOfShare << setw(20) << ptr->price
			<< setw(20) << ptr->totalValue << endl;
		ptr = ptr->next;
		
	}
	ptr = head;
	while (ptr != NULL)
	{
		value += ptr->totalValue;
		ptr = ptr->next;
	}
	cout << "Total portfolio value: $" << setw(8) << value <<endl;
}

void stockAccount::insert(Node *ptr)
{
	
	if (this->size()==0)
	{
		head = tail = ptr;
		return;
	}
	else if(ptr->totalValue>=head->totalValue)
	{
		ptr->next = head;
		head->previous = ptr;
		head = ptr;
		return;
	}
	else if (ptr->totalValue <= tail->totalValue)
	{
		tail->next = ptr;
		ptr->previous = tail;
		tail = ptr;
		return;
	}
	else
	{
		Node *previousNode, *nextNode;
		previousNode = head;
		nextNode = previousNode->next;
		while (nextNode->totalValue > ptr->totalValue)
		{
			previousNode = nextNode;
			nextNode = previousNode->next;
		}
		previousNode->next = ptr;
		nextNode->previous = ptr;
		ptr->next = nextNode;
		ptr->previous = previousNode;

	}
}

void stockAccount::deleteNode(string name)
{
	Node *ptr = NULL;
	ptr = head;
	while (ptr != NULL)
	{
		if (ptr->name.compare(name) == 0)
		{
			break;
		}
		ptr = ptr->next;
	}
	if (ptr == head && ptr == tail)
	{
		delete ptr;
		head = tail = NULL;
		return;
	}
	else if (ptr==head)
	{
		head = head->next;
		delete ptr;
		return;
	}
	else if (ptr == tail)
	{
		tail=tail->previous;
		ptr->previous->next = NULL;
		delete ptr;
		return;
	}
	else
	{
		ptr->previous->next = ptr->next;
		ptr->next->previous = ptr->previous;
		delete ptr;
		return;
	}

}



 void stockAccount::input()
 {
	 Node *content = head;
	 accountWrite.open("Stock_Portfolio_Account.txt");
	 while (content != NULL)
	 {
		 accountWrite  << setw(20) << content->name << setw(10) << content->numberOfShare << setw(10)
			 << setiosflags(ios::fixed) << setprecision(2) << content->price << setw(15) << content->totalValue << endl;
		 content = content->next;
	 }
	 accountWrite.close();
 }

/*This function is used to find the stock*/
 bool stockAccount::findStock(string name)
 {
	 stockNode *ptr=NULL;
	 bool flat = 0;//flat is used to symbol if the item is found;
	 ptr = myHead;
	 while (ptr != NULL)
	 {
		 if (ptr->companyName.compare(name) == 0)
		 {
			 flat = 1;
			 break;
		 }
		 ptr = ptr->myNext;
	 }
	 return flat;
 }

 bool stockAccount::findStockInAccount(string name)
 {
	 Node *ptr = head;
	 bool flat = 0;
	 while (ptr != NULL)
	 {
		 if(ptr->name.compare(name)==0)
		 {
			 flat = 1;
			 break;
		 }
		 ptr = ptr->next;
	 }
	 return flat;

 }

 /*This function is used to return the informantion of specific stock*/
 stockNode stockAccount::returnStockNode(string name)
 {
	 stockNode *ptr=myHead;
	 while (ptr != NULL)
	 {
		 if (ptr->companyName.compare(name) == 0)
		 {
			 return *ptr;
		 }
		 ptr = ptr->myNext;
	 }
	 return *ptr;
 }

 Node stockAccount::returnNode(string name)
 {
	 Node *ptr =head;
	 while (ptr != NULL)
	 {
		 if (ptr->name.compare(name) == 0)
		 {
			 break;
		 }
		 ptr = ptr->next;
	 }
	 return *ptr;
 }

 /*This function is used to buy the stock*/
 void stockAccount::buyStock()
{
	 string name;
	 double buyPrice,totlaPrice;
	 int count;
	 Node *content;
	 stockNode temp;
	 if (myHead == NULL)
	 {
		 readFile();
	 }
	//accountRead.open("Stock_Portfolio_Account.txt");
	//accountWrite.open("transction.txt",ios::app);
	cout << "Please enter the stock symbol you wish to purchase:" << endl;
	cin >> name;
	if (this->findStock(name) == 0)
	{
		cout << "There is no" << endl;
		return;
	}
	if (this->findStock(name) == 1)
	{

		if (head==NULL)
		{
			this->readAccount();
		}

		if (this->findStockInAccount(name)==0)
		{
			content = new Node();
			temp = this->returnStockNode(name);
			cout << "Please enter the stock number you wish to purchase:" << endl;
			cin >> content->numberOfShare;
			cout << "Please enter the maximum amount you are willing to pay per share:" << endl;
			cin >> buyPrice;
			if (buyPrice < temp.stockPrice)
			{
				cout << "The price you want to buy is low than the market price!";
					return;
			}
			totlaPrice = (content->numberOfShare)*temp.stockPrice;
			if (totlaPrice > balance)
			{
				cout << "Insufficient balance!" << endl;
				return;
			}
			else
			{
				cout << "You have purchased "<< content->numberOfShare <<"shares of " << temp.companyName << " at $" << buyPrice << " each for a total of $" << totlaPrice << endl;
				balance = balance - totlaPrice;
				setBalance();
			}
			accountHistory.open("stockHistory.txt", ios::app);
			time_t tt = time(NULL);
			tm* t = localtime(&tt);
			accountHistory << setiosflags(ios::fixed) << setprecision(2) << left << "   " << "BUY" << "   " << temp.companyName
				<< "   " << content->numberOfShare << "   " << "$" << temp.stockPrice << "   " << "$" << totlaPrice
				<< "   "  << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << endl;
			accountHistory.close();
			content->name = temp.companyName;
			content->price = temp.stockPrice;
			content->totalValue = (content->numberOfShare)*(content->price);
			this->insert(content);
			this->input();
		}
		else if(this->findStockInAccount(name) == 1)
		{
			content = new Node();
			Node *returnResult = &(returnNode(name));
			temp = this->returnStockNode(name);
			cout << "Please enter the stock number you wish to purchase:" << endl;
			cin >> count;
			cout << "Please enter the maximum amount you are willing to pay per share:" << endl;
			cin >> buyPrice;
			if (buyPrice < temp.stockPrice)
			{
				cout << "The price you want to buy is lower than the market price!";
				return;
			}
			totlaPrice = count*temp.stockPrice;
			if (totlaPrice > balance)
			{
				cout << "Insufficient balance!" << endl;
				return;
			}
			else
			{
				cout << "You have purchased " << count << "shares of "<< temp.companyName <<" at $" << temp.stockPrice << " each for a total of $" << totlaPrice << endl;
				balance = balance - totlaPrice;
				setBalance();
			}
			accountHistory.open("stockHistory.txt", ios::app);
			time_t tt = time(NULL);
			tm* t = localtime(&tt);
			accountHistory << setiosflags(ios::fixed) << setprecision(2) << left << "   " << "BUY" << "   " << temp.companyName
				<< "   " << count << "   " << "$" << temp.stockPrice << "   " << "$" << totlaPrice
				<< "  " <<""<< t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << endl;
			accountHistory.close();
			content->name = temp.companyName;
			content->numberOfShare = returnResult->numberOfShare+count;
			content->price = temp.stockPrice;
			content->totalValue = (content->numberOfShare)*(content->price);
			this->deleteNode(name);
			this->insert(content);
			this->input();
		}
	}
	//accountRead.close();
	//accountWrite.close();
}

 void stockAccount::sellStock()
 {
	 string name;
	 int count;
	 double sellPrice, totalPrice;
	 Node *content;
	 stockNode temp;
	 if (myHead == NULL)
	 {
		 readFile();
	 }
	 cout << "Please enter the stock symbol you wish to sell:" << endl;
	 cin >> name;
	 if (head == NULL)
	 {
		 this->readAccount();
	 }
	 if (this->findStockInAccount(name) == 0)
	 {
		 cout << "There is not such stock in account" << endl;
	 }
	 else if (this->findStockInAccount(name) == 1)
	 {
		 content = new Node();
		 Node *returnResult = &(returnNode(name));
		 temp = this->returnStockNode(name);
		 cout << "Please input the number you want to sell" << endl;
		 cin >> count;
		 content->name = temp.companyName;
		 if (returnResult->numberOfShare < count)
		 {
			 cout << "the number is so big" << endl;
			 return;
		 }
		 cout << "Please enter the minimum amount you are willing to get per share:" << endl;
		 cin >> sellPrice;
		 if (sellPrice > temp.stockPrice)
		 {
			 cout << "The price you want to buy is higer than the market price!";
			 return;
		 }
		 totalPrice = count*temp.stockPrice;
		 cout << "You have sold " << count << "shares of "<< temp.companyName << "at $" << temp.stockPrice << " each for a total of $" << totalPrice << endl;
		 balance = balance + totalPrice;
		 setBalance();
		 content->numberOfShare = returnResult->numberOfShare - count;
		 if (content->numberOfShare == 0) 
		 { 
			 this->deleteNode(name);
			 this->input();
			 accountHistory.open("stockHistory.txt", ios::app);
			 time_t tt = time(NULL);
			 tm* t = localtime(&tt);
			 accountHistory << setiosflags(ios::fixed) << setprecision(2) << left << "SELL" << "   " << temp.companyName
				 << "   " << count << "   " << "$" << temp.stockPrice << "   " << "$" << totalPrice
				 << " " << "" << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << endl;
			 accountHistory.close();
			 return; 
		 }
		 accountHistory.open("stockHistory.txt", ios::app);
		 time_t tt = time(NULL);
		 tm* t = localtime(&tt);
		 accountHistory << setiosflags(ios::fixed) << setprecision(2) << left  << "SELL" << "   " << temp.companyName
			 << "   " << count << "   " << "$" << temp.stockPrice <<  "   " << "$" << totalPrice
			 << " " << ""  << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << endl;
		 accountHistory.close();
		 content->price = temp.stockPrice;
		 content->totalValue = (content->numberOfShare)*(content->price);
		 this->deleteNode(name);
		 this->insert(content);
		 this->input();
	 }
 }


 void stockAccount::displayOneStock()
 {
	 string name;
	 stockNode temp;
	 if (myHead == NULL)
	 {
		 this->readFile();
	 }
	 cout << "Please enter the stock symbol:" << endl;
	 cin >> name;
	 if (this->findStock(name) == 0)
	 {
		 cout << "There is not such company!" << endl;
		 return;
	 }
	 temp = this->returnStockNode(name);
	 cout << "Company Symbol         Price per share/$" << endl;
	 cout << temp.companyName << "                   " << temp.stockPrice << endl;
 }

 void stockAccount::displayTransactionHistory()
 {
	 string s;
	 int i = 0;
	 accountHistoryRead.open("stockHistory.txt");
	 cout << "Event" << "       " << "CompanySymbol" << "    " << "Amount" << "     "
		 << "PricePerShare" << "     " << "TotalValue" << "      " << "Time" << endl;
	 while (accountHistoryRead >> s)
	 {
		 cout << left << setw(15)<<s;
		 i++;
		 if (i % 6 == 0)
			 cout << endl;
	 }
	 accountHistoryRead.close();
 }

 void stockAccount::displayMatlab()
 {
	 Engine *ep;
	 ep = engOpen(NULL);
	 if (ep == NULL)
	 {
		 cout << "Error: engine open failed" << endl;
		 exit(1);
	 }
	 int time;
	 double value;
	 int i=0;
	 vector<int> timeV;
	 vector<double> valueV;

	 totalValueRead.open("totalValue.txt");
	 while (totalValueRead >> value)
	 {
		 if (i % 2 == 0)
		 {
			 valueV.push_back(value);
			 i++;
		 }
		 if (i % 2 == 1)
		 {
			 time = i / 2 + 1;
			 timeV.push_back(time);
			 i++;
		 }
		
	 }
	 int tSize = timeV.size();
	 int vSize = valueV.size();
	 double *tArray = new double[tSize];
	 double *vArray = new double[vSize];

	 totalValueRead.close();
	 for (int i = 0; i < tSize; i++) {
		 tArray[i] = timeV[i];
		 vArray[i] = valueV[i];
	 }
	 mxArray *A;
	 A = mxCreateDoubleMatrix(1, tSize, mxREAL);
	 mxArray *B;
	 B = mxCreateDoubleMatrix(1, tSize, mxREAL);
	 memcpy((void*)mxGetPr(A), (void *)tArray, sizeof(double) * tSize);
	 memcpy((void*)mxGetPr(B), (void *)vArray, sizeof(double) * tSize);
	 engPutVariable(ep, "time", A);
	 engPutVariable(ep, "value",B);
	 engEvalString(ep, "plot(time,value);");
	 system("pause");
	 mxDestroyArray(A);
	 mxDestroyArray(B);
	 engEvalString(ep, "close;");
	 engClose(ep);
 }

 void stockAccount::saveTotalValue()
 {
	 Node *ptr;
	 double value=0;
	 ptr = head;
	 while (ptr != NULL)
	 {
		 value += ptr->totalValue;
		 ptr = ptr->next;
	 }
	 myHead == NULL;
	 totalValueWrite.open("totalValue.txt", ios::app);
	 totalValueWrite << returnBalance() + value << endl;
	 totalValueWrite.close();
 }