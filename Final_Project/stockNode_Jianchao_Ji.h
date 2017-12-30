#pragma once
#include<iostream>

using std::string;


/*class stockNode is used to store the information of the stock*/
class stockNode
{
	friend class stockAccount;
public:
	stockNode()
	{
		//myHead = NULL;
		myNext = NULL;
	}
private:
	//stockNode *myHead;
	stockNode *myNext;
	string companyName, date;
	double stockPrice;
};