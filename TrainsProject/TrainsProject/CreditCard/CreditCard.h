

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
};
