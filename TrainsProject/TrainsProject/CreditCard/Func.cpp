#include "Func.h"

bool valid( const CreditCard& card )	// return true if valid card and false otherwise	
{
	const char* number = card.number();
	int digit = card.sSize - 1;
	unsigned mult = 0, sumOdd = 0, sumEven = 0;

	while( digit >= 0 )
	{
		if( digit%2 == 1 )
			sumOdd += number[digit] - '0';
		else
		{
			mult = (number[digit] - '0') * 2;	

			if( mult > 9 )
				mult = mult % 10 + mult / 10;	// add digits in the number
			
			sumEven += mult;
		}
	
		--digit;	
	}

	return ! (( sumOdd + sumEven ) % 10);	// if mod 10 == zero card is valid
}
