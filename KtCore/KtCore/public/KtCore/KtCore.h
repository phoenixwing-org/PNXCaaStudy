
#if defined(_WIN32)
  #ifdef KtCore_EXPORTS
    #define ExportedByKtCore __declspec(dllexport)
  #else
    #define ExportedByKtCore __declspec(dllimport)
  #endif
#else
  #define ExportedByKtCore
#endif
