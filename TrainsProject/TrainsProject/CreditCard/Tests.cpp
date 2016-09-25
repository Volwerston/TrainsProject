
#include "Tests.h"
#include <iostream>

using namespace std;

CreditCard test_dflt_ctor( void )
{
	const float testValue = 0;
	CreditCard card;

	if( card.balance() == testValue )
		cout<< "test_dflt_ctor success" <<endl;
	else
		cout<< "test_dflt_ctor failed" <<endl;
	return	CreditCard();
}

void test_add( CreditCard&  card )
{
	const float addSum = 10;
	card += addSum;
	
	if( card.balance() == addSum )
		cout<< "test_add success" <<endl;
	else
		cout<< "test_add failed" <<endl;
}
