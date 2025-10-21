#ifdef _WINDOWS_SOURCE
#ifdef __PNXBomAnalysisItf
#define ExportedByPNXBomAnalysisItf __declspec(dllexport)
#else
#define ExportedByPNXBomAnalysisItf __declspec(dllimport)
#endif
#else
#define ExportedByPNXBomAnalysisItf
#endif
