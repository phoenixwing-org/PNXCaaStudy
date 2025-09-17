// COPYRIGHT DASSAULT SYSTEMES 2000
#ifdef  _WINDOWS_SOURCE
#ifdef  __CAAMmrCombinedCurve
#define ExportedByCAAMmrCombinedCurve     __declspec(dllexport)
#else
#define ExportedByCAAMmrCombinedCurve     __declspec(dllimport)
#endif
#else
#define ExportedByCAAMmrCombinedCurve
#endif
