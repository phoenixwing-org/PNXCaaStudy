// COPYRIGHT DASSAULT SYSTEMES 2000
#ifdef _WINDOWS_SOURCE
#ifdef __PNXCombinedCurveUI
#define ExportedByPNXCombinedCurveUI __declspec(dllexport)
#else
#define ExportedByPNXCombinedCurveUI __declspec(dllimport)
#endif
#else
#define ExportedByPNXCombinedCurveUI
#endif
