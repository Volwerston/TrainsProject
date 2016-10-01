#include "Tests.h"

int main( void )
{
	CreditCard testCard = test_dflt_ctor();
	test_add( testCard );
	testCCValidation();
	testInputValidation();

	return 0;
}
