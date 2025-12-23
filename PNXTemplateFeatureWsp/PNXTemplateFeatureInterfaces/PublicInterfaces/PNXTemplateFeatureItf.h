#ifdef _WINDOWS_SOURCE
#ifdef __PNXTemplateFeatureItf
#define ExportedByPNXTemplateFeatureItf __declspec(dllexport)
#else
#define ExportedByPNXTemplateFeatureItf __declspec(dllimport)
#endif
#else
#define ExportedByPNXTemplateFeatureItf
#endif
