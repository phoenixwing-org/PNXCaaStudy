#ifdef _WINDOWS_SOURCE
#ifdef __PNXCurveDivisionItf
#define ExportedByPNXCurveDivisionItf __declspec(dllexport)
#else
#define ExportedByPNXCurveDivisionItf __declspec(dllimport)
#endif
#else
#define ExportedByPNXCurveDivisionItf
#endif
