#ifdef _WINDOWS_SOURCE
#ifdef __PNXTemplateBaseItf
#define ExportedByPNXTemplateBaseItf __declspec(dllexport)
#else
#define ExportedByPNXTemplateBaseItf __declspec(dllimport)
#endif
#else
#define ExportedByPNXTemplateBaseItf
#endif
