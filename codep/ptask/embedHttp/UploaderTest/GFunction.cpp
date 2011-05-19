#include "GFunction.h"


std::string GFunction::toString( int i )
{
	char buf[16];
	return itoa(i,buf,10);
}