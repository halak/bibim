#pragma once
#ifndef __BIBIM_NULLPOINTER_H__
#define __BIBIM_NULLPOINTER_H__

#include <Bibim/Foundation.h>
#include <Bibim/SharedPointer.h>

namespace Bibim
{
#   ifndef BIBIM_CPLUSPLUS_0X
    static struct NullPointer
    {
        template <typename T> bool operator == (      T* right)                { return right ? false : true; }
        template <typename T> bool operator == (const T* right)                { return right ? false : true; }
        template <typename T> bool operator == (const SharedPointer<T>& right) { return right.GetPointee() ? false : true; }
    
        template <typename T> bool operator != (      T* right)                { return right ? true : false; }
        template <typename T> bool operator != (const T* right)                { return right ? true : false; }
        template <typename T> bool operator != (const SharedPointer<T>& right) { return right.GetPointee() ? true : false; }
    
        template <typename T> friend bool operator == (      T* left, NullPointer)                { return left ? false : true; }
        template <typename T> friend bool operator == (const T* left, NullPointer)                { return left ? false : true; }
        template <typename T> friend bool operator == (const SharedPointer<T>& left, NullPointer) { return left.GetPointee() ? false : true; }
    
        template <typename T> friend bool operator != (      T* left, NullPointer)                { return left ? true : false; }
        template <typename T> friend bool operator != (const T* left, NullPointer)                { return left ? true : false; }
        template <typename T> friend bool operator != (const SharedPointer<T>& left, NullPointer) { return left.GetPointee() ? true : false; }
    
        template <typename T> operator T* () const               { return 0; }
        template <typename T> operator SharedPointer<T> () const { return SharedPointer<T>(); }
    
    } nullptr;
#   endif
}

#endif