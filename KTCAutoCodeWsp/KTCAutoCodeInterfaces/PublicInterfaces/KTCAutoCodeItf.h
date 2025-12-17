#ifdef _WINDOWS_SOURCE
#ifdef __KTCAutoCodeItf
#define ExportedByKTCAutoCodeItf __declspec(dllexport)
#else
#define ExportedByKTCAutoCodeItf __declspec(dllimport)
#endif
#else
#define ExportedByKTCAutoCodeItf
#endif
