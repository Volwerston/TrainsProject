
#include "CreditCard.h"
#include "Func.h"
#include <iostream>

using namespace std;

const unsigned CreditCard::sSize = 16;

double CreditCard::balance()const
{
	return mBalance;
}

CreditCard::CreditCard( double balance, const string& expires, unsigned cvvCode , const string& number )
		: mNumber( number ), mExpires( expires ), mCvvCode( cvvCode ), mBalance( balance )	
{
	;
}
const CreditCard& CreditCard::operator+=( const CreditCard& rhs )
{
	this->mBalance += rhs.mBalance;
	return *this;
}

const char* CreditCard::number()const
{
	return mNumber.c_str();
}

bool CreditCard::charge( double amount )	// return true if success and false otherwise
{
	if( mBalance >= amount )
	{
		mBalance -= amount;
		return true;
	}
	else
		return false;
}

bool CreditCard::addFunds( double amount )	// return true if success and false otherwise
{
	if( amount > 0 )
	{
		mBalance += amount;
		return true;
	}
	else
		return false;
}	

bool CreditCard::inputNumber()
{
	cout<< "Please input credit card number:" <<endl;
	cin>> mNumber;
	while( !valid( *this ) )
	{
		cout<< "Incorrect number. Please try again." <<endl;
		mNumber.clear();
		cin>> mNumber;
	}

	return true;
}
	
