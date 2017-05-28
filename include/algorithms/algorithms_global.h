
#if defined(ALGORITHMS_LIB_LIBRARY)
#  define ALGORITHMS_LIB_EXPORT __declspec(dllexport)
#else
#  define ALGORITHMS_LIB_EXPORT __declspec(dllimport)
#endif
