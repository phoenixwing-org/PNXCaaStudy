#ifdef _WINDOWS_SOURCE
#ifdef __PNXV5V6AdapterItf
#define ExportedByPNXV5V6AdapterItf __declspec(dllexport)
#else
#define ExportedByPNXV5V6AdapterItf __declspec(dllimport)
#endif
#else
#define ExportedByPNXV5V6AdapterItf
#endif
