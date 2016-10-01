#include "Func.h"

bool valid( const CreditCard& card )	// return true if valid card and false otherwise	
{
	const char* number = card.number();
	int digit = 0; // ?
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

bool dateExists( unsigned y, unsigned m, unsigned d )
{
	if (! (2016<=y && y<=2040) )
		return false;
	if (! (1<= m && m<=12) )
    	return false;
	if (! (1<= d && d<=31) )
    	return false;

  	if ( (d==31) && (m==2 || m==4 || m==6 || m==9 || m==11) )
		return false;
	if ( (d==30) && (m==2) )
		return false;

	if ( (m==2) && (d==29) && (y%4!=0) )
		return false;
 
	return true;	
}
