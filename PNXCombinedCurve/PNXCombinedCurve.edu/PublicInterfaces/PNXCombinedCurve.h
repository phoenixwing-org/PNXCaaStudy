// COPYRIGHT DASSAULT SYSTEMES 2000
#ifdef _WINDOWS_SOURCE
#ifdef __PNXCombinedCurve
#define ExportedByPNXCombinedCurve __declspec(dllexport)
#else
#define ExportedByPNXCombinedCurve __declspec(dllimport)
#endif
#else
#define ExportedByPNXCombinedCurve
#endif
