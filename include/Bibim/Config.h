#pragma once
#ifndef __BIBIM_CONFIG_H__
#define __BIBIM_CONFIG_H__

#if (defined(WINDOWS) || defined(WIN32) || defined(WIN64))
#    define BIBIM_PLATFORM_WINDOWS
#    define BIBIM_USE_DIRECTX9
#elif (defined(ANDROID))
#    define BIBIM_PLATFORM_UNIX
#    define BIBIM_PLATFORM_ANDROID
#    define BIBIM_USE_OPENGLES2
#elif (defined(__APPLE__))
#    define BIBIM_PLATFORM_UNIX
#    define BIBIM_PLATFORM_IOS
#    define BIBIM_USE_OPENGLES2
#else
#    error "UNKNOWN PLATFORM"
#    define BIBIM_PLATFORM_UNKNOWN
#endif

#if (defined(DEBUG) || defined(_DEBUG))
#    define BIBIM_DEBUG
#    define BIBIM_USE_DIAGNOSTICS
#else
#    define BIBIM_RELEASE
#    define BIBIM_USE_DIAGNOSTICS
#endif

#if (defined(_MSC_VER))
#    define BIBIM_COMPILER_MSVC
#    define NOMINMAX
#else
#    define BIBIM_COMPILER_GCC
#endif

#if (__cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER  >= 1600))
#    define BIBIM_CPLUSPLUS_0X
#endif

#endif