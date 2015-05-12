// burnside.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "burnside.h"

// This is an example of an exported variable
BURNSIDE_DECL_API int nburnside = 0;

// This is an example of an exported function.
BURNSIDE_DECL_API int fnburnside(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see burnside.h for the class definition
Cburnside::Cburnside()
{
	return;
}
