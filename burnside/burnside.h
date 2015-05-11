// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the BURNSIDE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// BURNSIDE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#include "stdafx.h"

// This class is exported from the burnside.dll
class BURNSIDE_DECL_API Cburnside {
public:
	Cburnside(void);
	// TODO: add your methods here.
};

extern BURNSIDE_DECL_API int nburnside;

BURNSIDE_DECL_API int fnburnside(void);
