#ifndef CCARD_H
#define CCARD_H

#include <string>

using namespace std;

class CreditCard
{
		double mBalance;
		string mNumber;
		const string mExpires;
		const unsigned mCvvCode;
	public:
		CreditCard( double balance = 0, const string& str = string(), unsigned code = 111, const string& number = string()  );	
		double balance()const;
		const CreditCard& operator+=( const CreditCard& rhs );
		const char* number()const;
		bool inputNumber();
		bool charge( double );
		bool addFunds( double );
		static const unsigned sSize;
};

#endif
