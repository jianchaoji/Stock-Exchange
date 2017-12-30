#pragma once
#include<iostream>

using std::string;

class Node
{
	friend class stockAccount;
public:
	Node();
private:
	Node* head;
	Node* tail;
	Node* previous;
	Node* next;
	string name;
	int numberOfShare;
	double price;
	double totalValue;
};
