#include<iostream>
#include"accountNode_Jianchao_Ji.h"

using namespace std;

Node::Node()
	
{
	totalValue = numberOfShare*price;
	head = NULL;
	tail = NULL;
	previous = NULL;
	next = NULL;
}