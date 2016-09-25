
#include "CreditCard.h"

using namespace std;

double CreditCard::balance()const
{
	return mBalance;
}

CreditCard::CreditCard( double balance, const string& number ) : mBalance( balance ), mNumber( number ) 	
{
	;
}
const CreditCard& CreditCard::operator+=( const CreditCard& rhs )
{
	this->mBalance += rhs.mBalance;
	return *this;
}
