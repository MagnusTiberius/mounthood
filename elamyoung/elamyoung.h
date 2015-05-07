// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ELAMYOUNG_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ELAMYOUNG_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef ELAMYOUNG_EXPORTS
#define ELAMYOUNG_API __declspec(dllexport)
#else
#define ELAMYOUNG_API __declspec(dllimport)
#endif

// This class is exported from the elamyoung.dll
class ELAMYOUNG_API Celamyoung {
public:
	Celamyoung(void);
	// TODO: add your methods here.
};

extern ELAMYOUNG_API int nelamyoung;

ELAMYOUNG_API int fnelamyoung(void);
