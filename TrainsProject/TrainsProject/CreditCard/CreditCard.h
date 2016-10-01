#ifndef CCARD_H
#define CCARD_H

#include <string>

using namespace std;

class CreditCard
{
		string mNumber;
		double mBalance;
	public:
		CreditCard( double balance = 0, const string& number = string()  );	
		double balance()const;
		const CreditCard& operator+=( const CreditCard& rhs );
		const char* number()const;
		bool inputNumber();
		bool charge( double );
		bool addFunds( double );
		static const unsigned sSize;
};

#endif
