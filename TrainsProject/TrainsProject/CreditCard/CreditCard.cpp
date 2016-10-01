
#include "CreditCard.h"
#include "Func.h"
#include <iostream>

using namespace std;

const unsigned CreditCard::sNumberSize = 16;
const unsigned CreditCard::sCvvSize = 3;

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

const string& CreditCard::expires()const
{
	return mExpires;
}

unsigned CreditCard::code()const
{
	return mCvvCode;
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
<<<<<<< HEAD
	return( valid( *this ) );
=======
	while( !valid( *this ) )
	{
		cout<< "Incorrect number. Please try again." <<endl;
		mNumber.clear();
		cin>> mNumber;
	}

	return true;
>>>>>>> c9c3d81c9df699a232a3a2f296408af92b287c46
}
	
bool CreditCard::inputExpirationDate()
{
	bool exists = false;
	unsigned d(0), m(0), y(0);

	cout<< "Year:\t"; cin>> y;
	cout<< "Month:\t"; cin>> m;
	cout<< "Day:\t"; cin>> d;
		
	exists = dateExists( y,d,m );

	mExpires = y;
	mExpires += "-";
	mExpires += m;
	mExpires += "-";
	mExpires += d;
	
	return exists;
}

bool CreditCard::inputCvvCode()
{
	string code;
	cout<< "CVV code:\t" ;
	cin>> code;
	return ( "000" <= code && code <= "999" );
}
