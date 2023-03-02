#pragma once
#ifdef DYNAMICSORT_EXPORTS
#define DLL_API _declspec(dllexport)
#else
#define DLL_API _declspec(dllimport)
#endif
extern "C" DLL_API void bubbleSortDynamic(int*, int);