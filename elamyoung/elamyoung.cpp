// elamyoung.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "elamyoung.h"


// This is an example of an exported variable
ELAMYOUNG_API int nelamyoung=0;

// This is an example of an exported function.
ELAMYOUNG_API int fnelamyoung(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see elamyoung.h for the class definition
Celamyoung::Celamyoung()
{
	return;
}
