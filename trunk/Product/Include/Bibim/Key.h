#pragma once
#ifndef __BIBIM_KEYS_H__
#define __BIBIM_KEYS_H__

#   include <Bibim/FWD.h>
#   include <vector>

    namespace Bibim
    {
        struct Key
        {
            BBThisIsStaticStruct(Key);
            enum Code
            {
                None = 0x00,
                Back = 0x08,
                Enter = 0x0D,
                Shift = 0x10,
                Ctrl = 0x11,
                Alt = 0x12,
                Escape = 0x1B,
                Space = 0x20,
                Left = 0x25,
                Up = 0x26,
                Right = 0x27,
                Down = 0x28,
                D0 = '0',
                D1 = '1',
                D2 = '2',
                D3 = '3',
                D4 = '4',
                D5 = '5',
                D6 = '6',
                D7 = '7',
                D8 = '8',
                D9 = '9',
                A = 0x41,
                B = 0x42,
                C = 0x43,
                D = 0x44,
                E = 0x45,
                F = 0x46,
                G = 0x47,
                H = 0x48,
                I = 0x49,
                J = 0x4A,
                K = 0x4B,
                L = 0x4C,
                M = 0x4D,
                N = 0x4E,
                O = 0x4F,
                P = 0x50,
                Q = 0x51,
                R = 0x52,
                S = 0x53,
                T = 0x54,
                U = 0x55,
                V = 0x56,
                W = 0x57,
                X = 0x58,
                Y = 0x59,
                Z = 0x5A,
                F1 = 0x70,
                F2 = 0x71,
                F3 = 0x72,
                F4 = 0x73,
                F5 = 0x74,
                F6 = 0x75,
                F7 = 0x76,
                F8 = 0x77,
                F9 = 0x78,
                F10 = 0x79,
                F11 = 0x7A,
                F12 = 0x7B,

                Insert = 0x2D,
                Delete = 0x2E,
                Home = 0x24,
                End = 0x23,

                MouseLeftButton = 0x01,
                MouseRightButton = 0x02,
                MouseMiddleButton = 0x04,

                GamePadA = 0xF0,
                GamePadB = 0xF1,
                GamePadX = 0xF2,
                GamePadY = 0xF3,
                GamePadUp = 0xF4,
                GamePadDown = 0xF5,
                GamePadLeft = 0xF6,
                GamePadRight = 0xF7,
                GamePadStart = 0xF8,
                GamePadBack = 0xF9,
                GamePadSelect = 0xFA,
                GamePadLeftThumb = 0xFB,
                GamePadRightThumb = 0xFC,
                GamePadLeftShoulder = 0xFD,
                GamePadRightShoulder = 0xFE,
            };

            static const int Count = 256;
            static const Code Codes[Count];

            static void Setup();
            static const char* ToString(Code value);
            static Code Parse(const char* value);

            typedef std::pair<const char*, Code> Entry;

            private:
                static std::vector<Entry> stringToCodeMap;
                static std::vector<Entry> codeToStringMap;
        };
    }

#endif