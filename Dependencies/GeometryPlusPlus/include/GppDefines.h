#pragma once

#ifdef GPP_DLL_EXPORT
#ifdef WIN32
#ifdef GPP_BUILD
#define GPP_EXPORT __declspec(dllexport)
#else
#define GPP_EXPORT __declspec(dllimport)
#endif
#else
#define GPP_EXPORT
#endif
#else
#define GPP_EXPORT
#endif

#ifndef NULL
#define NULL 0
#endif

#define GPPFREEPOINTER(pointer) if (pointer != NULL) { delete pointer; pointer = NULL; }
#define GPPFREEARRAY(pointer) if (pointer != NULL) { delete []pointer; pointer = NULL; }

namespace GPP
{
    typedef double Real;
    typedef int Int;
    typedef unsigned int UInt;
    typedef long long LongInt;
    typedef unsigned long long ULongInt;
    static const Real REAL_TOL = 1.0e-15;
    static const Real REAL_LARGE = 1.7e+308;
}
