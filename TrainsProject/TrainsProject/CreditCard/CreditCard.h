#ifndef CCARD_H
#define CCARD_H

#include <string>

using namespace std; 

class CreditCard
{
		double mBalance;
		string mNumber;
		string mExpires;
		unsigned mCvvCode;
	public:
		CreditCard( double balance = 0, const string& str = string(), unsigned code = 111, const string& number = string()  );	
		double balance()const;
		const CreditCard& operator+=( const CreditCard& rhs );
		const char* number()const;
		const string& expires()const;
		unsigned code()const;
		bool inputNumber();
		bool inputExpirationDate();
		bool inputCvvCode();
		bool charge( double );
		bool addFunds( double );
		static const unsigned sNumberSize;
		static const unsigned sCvvSize;
};

#endif
