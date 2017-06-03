#ifndef _ALGORITHMS_GLOBAL_EXPORT_HEADER_
#define _ALGORITHMS_GLOBAL_EXPORT_HEADER_

#if (defined _WIN32 || defined __CYGWIN__ || defined _WIN64)
   #ifdef __GNUC__
      #define DLL_EXPORT __attribute__ ((dllexport))
      #define DLL_IMPORT __attribute__ ((dllimport))
   #elif _MSC_VER
      #define DLL_EXPORT __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
      #define DLL_IMPORT __declspec(dllimport)
   #else  // We should probably need a change here in order to support clang.
      #define DLL_EXPORT __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
      #define DLL_IMPORT __declspec(dllimport)
   #endif
#else
   #if __GNUC__ >= 4
      #define DLL_EXPORT __attribute__ ((visibility ("default")))
      #define DLL_IMPORT __attribute__ ((visibility ("default")))
      #define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
   #endif
#endif

#if defined(BUILDING_ALGORITHMS_LIBRARY)
#  define ALGORITHMS_LIB DLL_EXPORT
#else
#  define ALGORITHMS_LIB DLL_IMPORT
#endif

#endif // _ALGORITHMS_GLOBAL_EXPORT_HEADER_
