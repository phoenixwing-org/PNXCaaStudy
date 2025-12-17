#ifdef _WINDOWS_SOURCE
#ifdef __KTCAutoCodeUI
#define ExportedByKTCAutoCodeUI __declspec(dllexport)
#else
#define ExportedByKTCAutoCodeUI __declspec(dllimport)
#endif
#else
#define ExportedByKTCAutoCodeUI
#endif
