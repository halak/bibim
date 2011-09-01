#pragma once
#ifndef __BIBIM_QUATERNION_H__
#define __BIBIM_QUATERNION_H__

#   include <Bibim/Foundation.h>

    namespace Bibim
    {
        struct Quaternion
        {
            float X;
            float Y;
            float Z;
            float W;

            inline Quaternion();
            inline Quaternion(float x, float y, float z);
            inline Quaternion(float x, float y, float z, float w);
            inline Quaternion(const Quaternion& original);

            inline Quaternion& operator = (const Quaternion& original);
            
            inline bool operator == (const Quaternion& right) const;
            inline bool operator != (const Quaternion& right) const;

            static const Quaternion Zero;
            static const Quaternion Identity;
        };
    }

#   include <Bibim/Quaternion.inl>

#endif