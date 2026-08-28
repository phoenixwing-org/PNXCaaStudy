
#if defined(_WIN32) && !defined(KTCORE_STATIC_DEFINE)
#ifdef KtCore_EXPORTS
#define ExportedByKtCore __declspec(dllexport)
#else
#define ExportedByKtCore __declspec(dllimport)
#endif
#else
#define ExportedByKtCore
#endif
