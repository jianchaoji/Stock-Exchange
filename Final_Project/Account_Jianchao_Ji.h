#pragma once
#include<iostream>

class account
{
public:
	account();
	virtual void openAccount()=0;
protected:
	double balance;
};
