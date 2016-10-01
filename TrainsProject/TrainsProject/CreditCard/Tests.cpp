
#include "Tests.h"
#include "Func.h"
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

void testCCValidation( )
{
	CreditCard validCard( 100, "4149500017188320");
	CreditCard invalidCard( 100.10, "1234567891234567");

	if( valid( validCard ) && !valid( invalidCard ) )
		cout<< "test_card_validation success" <<endl;
	else
		cout<< "test_card_validation failed" <<endl;

	if( valid( validCard ) )
		cout<< "test_validCard success" <<endl;
	else
		cout<< "test_validCard failed" <<endl;

	if( !valid( invalidCard ) )
		cout<< "test_invalidCard success" <<endl;
	else
		cout<< "test_invalidCard failed" <<endl;
}

void testInputValidation()
{
	CreditCard card;
	card.inputNumber();
}
