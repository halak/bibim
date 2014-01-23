#pragma once
#ifndef __BIBIM_COLOR_H__
#define __BIBIM_COLOR_H__

#include <Bibim/Foundation.h>
#include <Bibim/Vector3.h>
#include <Bibim/Vector4.h>

namespace Bibim
{
    struct Color
    {
        byte A;
        byte R;
        byte G;
        byte B;

        inline Color();
        inline Color(int r, int g, int b);
        inline Color(int r, int g, int b, int a);
        inline Color(unsigned long argb);
        inline explicit Color(Vector3 rgb);
        inline explicit Color(Vector4 rgba);
        inline Color(const Color& original);

        inline float GetR() const;
        inline float GetG() const;
        inline float GetB() const;
        inline float GetA() const;

        inline Vector3 ToVector3() const;
        inline Vector4 ToVector4() const;
        inline unsigned long ToRGBA() const;
        inline unsigned long ToARGB() const;

        inline Color& operator = (const Color& right);
        inline Color& operator += (Color right);
        inline Color& operator -= (Color right);
        inline Color& operator *= (Color right);
        inline Color& operator *= (float right);
        inline Color& operator *= (Vector4 right);
        inline Color& operator /= (Color right);
        inline Color& operator /= (float right);

        inline Color operator + (Color right) const;
        inline Color operator - (Color right) const;
        inline Color operator * (Color right) const;
        inline Color operator * (float right) const;
        inline Color operator * (Vector4 right) const;
        inline Color operator / (Color right) const;
        inline Color operator / (float right) const;

        inline bool operator == (Color right) const;
        inline bool operator != (Color right) const;

        static const Color TransparentBlack;
        static const Color TransparentWhite;
        static const Color AliceBlue;
        static const Color AntiqueWhite;
        static const Color Aqua;
        static const Color AquaMarine;
        static const Color Azure;
        static const Color Beige;
        static const Color Bisque;
        static const Color Black;
        static const Color BlanchedAlmond;
        static const Color Blue;
        static const Color BlueViolet;
        static const Color Brown;
        static const Color BurlyWood;
        static const Color CadetBlue;
        static const Color Chartreuse;
        static const Color Chocolate;
        static const Color Coral;
        static const Color CornflowerBlue;
        static const Color Cornsilk;
        static const Color Crimson;
        static const Color Cyan;
        static const Color DarkBlue;
        static const Color DarkCyan;
        static const Color DarkGoldenRod;
        static const Color DarkGray;
        static const Color DarkGreen;
        static const Color DarkKhaki;
        static const Color DarkMagenta;
        static const Color DarkOliveGreen;
        static const Color DarkOrange;
        static const Color DarkOrchid;
        static const Color DarkRed;
        static const Color DarkSalmon;
        static const Color DarkSeaGreen;
        static const Color DarkSlateBlue;
        static const Color DarkSlateGray;
        static const Color DarkTurquoise;
        static const Color DarkViolet;
        static const Color DeepPink;
        static const Color DeepSkyBlue;
        static const Color DimGray;
        static const Color DodgerBlue;
        static const Color FireBrick;
        static const Color FloralWhite;
        static const Color ForestGreen;
        static const Color Fuchsia;
        static const Color Gainsboro;
        static const Color GhostWhite;
        static const Color Gold;
        static const Color GoldenRod;
        static const Color Gray;
        static const Color Green;
        static const Color GreenYellow;
        static const Color HoneyDew;
        static const Color HotPink;
        static const Color IndianRed;
        static const Color Indigo;
        static const Color Ivory;
        static const Color Khaki;
        static const Color Lavender;
        static const Color LavenderBlush;
        static const Color LawnGreen;
        static const Color LemonChiffon;
        static const Color LightBlue;
        static const Color LightCoral;
        static const Color LightCyan;
        static const Color LightGoldenRodYellow;
        static const Color LightGrey;
        static const Color LightGreen;
        static const Color LightPink;
        static const Color LightSalmon;
        static const Color LightSeaGreen;
        static const Color LightSkyBlue;
        static const Color LightSlateGray;
        static const Color LightSteelBlue;
        static const Color LightYellow;
        static const Color Lime;
        static const Color LimeGreen;
        static const Color Linen;
        static const Color Magenta;
        static const Color Maroon;
        static const Color MediumAquaMarine;
        static const Color MediumBlue;
        static const Color MediumOrchid;
        static const Color MediumPurple;
        static const Color MediumSeaGreen;
        static const Color MediumSlateBlue;
        static const Color MediumSpringGreen;
        static const Color MediumTurquoise;
        static const Color MediumVioletRed;
        static const Color MidnightBlue;
        static const Color MintCream;
        static const Color MistyRose;
        static const Color Moccasin;
        static const Color NavajoWhite;
        static const Color Navy;
        static const Color OldLace;
        static const Color Olive;
        static const Color OliveDrab;
        static const Color Orange;
        static const Color OrangeRed;
        static const Color Orchid;
        static const Color PaleGoldenRod;
        static const Color PaleGreen;
        static const Color PaleTurquoise;
        static const Color PaleVioletRed;
        static const Color PapayaWhip;
        static const Color PeachPuff;
        static const Color Peru;
        static const Color Pink;
        static const Color Plum;
        static const Color PowderBlue;
        static const Color Purple;
        static const Color Red;
        static const Color RosyBrown;
        static const Color RoyalBlue;
        static const Color SaddleBrown;
        static const Color Salmon;
        static const Color SandyBrown;
        static const Color SeaGreen;
        static const Color SeaShell;
        static const Color Sienna;
        static const Color Silver;
        static const Color SkyBlue;
        static const Color SlateBlue;
        static const Color SlateGray;
        static const Color Snow;
        static const Color SpringGreen;
        static const Color SteelBlue;
        static const Color Tan;
        static const Color Teal;
        static const Color Thistle;
        static const Color Tomato;
        static const Color Turquoise;
        static const Color Violet;
        static const Color Wheat;
        static const Color White;
        static const Color WhiteSmoke;
        static const Color Yellow;
        static const Color YellowGreen;

        private:
            static inline byte Add(byte a, byte b);
            static inline byte Subtract(byte a, byte b);
            static inline byte Clamp(int value);
            static inline byte Clamp(float value);
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    byte Color::Add(byte a, byte b)
    {
        return 255 - a < b ? 255 : a + b;
    }

    byte Color::Subtract(byte a, byte b)
    {
        return a > b ? a - b : 0;
    }

    byte Color::Clamp(int value)
    {
        return value < 0 ? 0 : (value > 255 ? 255 : static_cast<byte>(value));
    }

    byte Color::Clamp(float value)
    {
        return value < 0.0f ? 0 : (value > 255.0f ? 255 : static_cast<byte>(value));
    }

    Color::Color()
        : A(0), R(0), G(0), B(0)
    {
    }

    Color::Color(int r, int g, int b)
        : A(255), R(Clamp(r)), G(Clamp(g)), B(Clamp(b))
    {
    }

    Color::Color(int r, int g, int b, int a)
        : A(Clamp(a)), R(Clamp(r)), G(Clamp(g)), B(Clamp(b))
    {
    }

    Color::Color(unsigned long argb)
        : A(static_cast<byte>((argb & 0xFF000000) >> 24)),
          R(static_cast<byte>((argb & 0x00FF0000) >> 16)),
          G(static_cast<byte>((argb & 0x0000FF00) >> 8)),
          B(static_cast<byte>((argb & 0x000000FF) >> 0))
    {
    }

    Color::Color(Vector3 rgb)
        : A(255),
          R(Clamp(rgb.X * 255.0f)),
          G(Clamp(rgb.Y * 255.0f)),
          B(Clamp(rgb.Z * 255.0f))
    {
    }

    Color::Color(Vector4 rgba)
        : A(Clamp(rgba.W * 255.0f)),
          R(Clamp(rgba.X * 255.0f)),
          G(Clamp(rgba.Y * 255.0f)),
          B(Clamp(rgba.Z * 255.0f))
    {
    }

    Color::Color(const Color& original)
        : A(original.A), R(original.R), G(original.G), B(original.B)
    {
    }

    float Color::GetR() const
    {
        return static_cast<float>(R) / 255.0f;
    }

    float Color::GetG() const
    {
        return static_cast<float>(G) / 255.0f;
    }

    float Color::GetB() const
    {
        return static_cast<float>(B) / 255.0f;
    }

    float Color::GetA() const
    {
        return static_cast<float>(A) / 255.0f;
    }

    Vector3 Color::ToVector3() const
    {
        return Vector3(GetR(), GetG(), GetB());
    }

    Vector4 Color::ToVector4() const
    {
        return Vector4(GetR(), GetG(), GetB(), GetA());
    }

    unsigned long Color::ToRGBA() const
    {
        return (static_cast<unsigned long>(R) << 24) |
               (static_cast<unsigned long>(G) << 16) |
               (static_cast<unsigned long>(B) << 8)  |
               (static_cast<unsigned long>(A) << 0);
    }

    unsigned long Color::ToARGB() const
    {
        return (static_cast<unsigned long>(A) << 24) |
               (static_cast<unsigned long>(R) << 16) |
               (static_cast<unsigned long>(G) << 8)  |
               (static_cast<unsigned long>(B) << 0);
    }

    Color& Color::operator = (const Color& right)
    {
        A = right.A;
        R = right.R;
        G = right.G;
        B = right.B;
        return *this;
    }

    Color& Color::operator += (Color right)
    {
        A = Add(A, right.A);
        R = Add(R, right.R);
        G = Add(G, right.G);
        B = Add(B, right.B);
        return *this;
    }

    Color& Color::operator -= (Color right)
    {
        A = Subtract(A, right.A);
        R = Subtract(R, right.R);
        G = Subtract(G, right.G);
        B = Subtract(B, right.B);
        return *this;
    }

    Color& Color::operator *= (Color right)
    {
        A = Clamp(static_cast<float>(A) * right.GetA());
        R = Clamp(static_cast<float>(R) * right.GetR());
        G = Clamp(static_cast<float>(G) * right.GetG());
        B = Clamp(static_cast<float>(B) * right.GetB());
        return *this;
    }

    Color& Color::operator *= (float right)
    {
        A = Clamp(static_cast<float>(A) * right);
        R = Clamp(static_cast<float>(R) * right);
        G = Clamp(static_cast<float>(G) * right);
        B = Clamp(static_cast<float>(B) * right);
        return *this;
    }

    Color& Color::operator *= (Vector4 right)
    {
        A = Clamp(static_cast<float>(A) * right.W);
        R = Clamp(static_cast<float>(R) * right.X);
        G = Clamp(static_cast<float>(G) * right.Y);
        B = Clamp(static_cast<float>(B) * right.Z);
        return *this;
    }

    Color& Color::operator /= (Color right)
    {
        A = Clamp(static_cast<float>(A) / right.GetA());
        R = Clamp(static_cast<float>(R) / right.GetR());
        G = Clamp(static_cast<float>(G) / right.GetG());
        B = Clamp(static_cast<float>(B) / right.GetB());
        return *this;
    }

    Color& Color::operator /= (float right)
    {
        A = Clamp(static_cast<float>(A) / right);
        R = Clamp(static_cast<float>(R) / right);
        G = Clamp(static_cast<float>(G) / right);
        B = Clamp(static_cast<float>(B) / right);
        return *this;
    }

    Color Color::operator + (Color right) const
    {
        return Color(Add(R, right.R),
                     Add(G, right.G),
                     Add(B, right.B),
                     Add(A, right.A));
    }

    Color Color::operator - (Color right) const
    {
        return Color(Subtract(R, right.R),
                     Subtract(G, right.G),
                     Subtract(B, right.B),
                     Subtract(A, right.A));
    }

    Color Color::operator * (Color right) const
    {
        return Color(Clamp(static_cast<float>(R) * right.GetR()),
                     Clamp(static_cast<float>(G) * right.GetG()),
                     Clamp(static_cast<float>(B) * right.GetB()),
                     Clamp(static_cast<float>(A) * right.GetA()));
    }

    Color Color::operator * (float right) const
    {
        return Color(Clamp(static_cast<float>(R) * right),
                     Clamp(static_cast<float>(G) * right),
                     Clamp(static_cast<float>(B) * right),
                     Clamp(static_cast<float>(A) * right));
    }

    Color Color::operator * (Vector4 right) const
    {
        return Color(Clamp(static_cast<float>(R) * right.X),
                     Clamp(static_cast<float>(G) * right.Y),
                     Clamp(static_cast<float>(B) * right.Z),
                     Clamp(static_cast<float>(A) * right.W));
    }

    Color Color::operator / (Color right) const
    {
        return Color(Clamp(static_cast<float>(R) / right.GetR()),
                     Clamp(static_cast<float>(G) / right.GetG()),
                     Clamp(static_cast<float>(B) / right.GetB()),
                     Clamp(static_cast<float>(A) / right.GetA()));
    }

    Color Color::operator / (float right) const
    {
        return Color(Clamp(static_cast<float>(R) / right),
                     Clamp(static_cast<float>(G) / right),
                     Clamp(static_cast<float>(B) / right),
                     Clamp(static_cast<float>(A) / right));
    }

    bool Color::operator == (Color right) const
    {
        return R == right.R && G == right.G && B == right.B && A == right.A;
    }

    bool Color::operator != (Color right) const
    {
        return !operator == (right);
    }
}

#endif