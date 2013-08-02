#include <Bibim/Config.h>
#include <Bibim/Key.h>
#include <Bibim/String.h>
#include <algorithm>

namespace Bibim
{
    const Key::Code Key::Codes[Count] = 
    {
        Back,
        Enter,
        Shift,
        Ctrl,
        Alt,
        Escape,
        Space,
        Left,
        Up,
        Right,
        Down,
        D0,
        D1,
        D2,
        D3,
        D4,
        D5,
        D6,
        D7,
        D8,
        D9,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        Insert,
        Delete,
        Home,
        End,
        None,
    };

    std::vector<Key::Entry> Key::stringToCodeMap;
    std::vector<Key::Entry> Key::codeToStringMap;

    struct CompareByString
    {
        bool operator () (Key::Entry a, Key::Entry b)
        {
            return String::CompareCharsIgnoreCase(a.first, b.first) < 0;
        }
    };

    struct CompareByCode
    {
        bool operator () (Key::Entry a, Key::Entry b)
        {
            return a.second < b.second;
        }
    };

    void Key::Setup()
    {
        stringToCodeMap.reserve(256);

#       define BBAddKeyEntry(code) stringToCodeMap.push_back(Entry(#code, code));

        BBAddKeyEntry(None);
        BBAddKeyEntry(Back);
        BBAddKeyEntry(Enter);
        BBAddKeyEntry(Shift);
        BBAddKeyEntry(Ctrl);
        BBAddKeyEntry(Alt);
        BBAddKeyEntry(Escape);
        BBAddKeyEntry(Space);
        BBAddKeyEntry(Left);
        BBAddKeyEntry(Up);
        BBAddKeyEntry(Right);
        BBAddKeyEntry(Down);
        BBAddKeyEntry(D0);
        BBAddKeyEntry(D1);
        BBAddKeyEntry(D2);
        BBAddKeyEntry(D3);
        BBAddKeyEntry(D4);
        BBAddKeyEntry(D5);
        BBAddKeyEntry(D6);
        BBAddKeyEntry(D7);
        BBAddKeyEntry(D8);
        BBAddKeyEntry(D9);
        BBAddKeyEntry(A);
        BBAddKeyEntry(B);
        BBAddKeyEntry(C);
        BBAddKeyEntry(D);
        BBAddKeyEntry(E);
        BBAddKeyEntry(F);
        BBAddKeyEntry(G);
        BBAddKeyEntry(H);
        BBAddKeyEntry(I);
        BBAddKeyEntry(J);
        BBAddKeyEntry(K);
        BBAddKeyEntry(L);
        BBAddKeyEntry(M);
        BBAddKeyEntry(N);
        BBAddKeyEntry(O);
        BBAddKeyEntry(P);
        BBAddKeyEntry(Q);
        BBAddKeyEntry(R);
        BBAddKeyEntry(S);
        BBAddKeyEntry(T);
        BBAddKeyEntry(U);
        BBAddKeyEntry(V);
        BBAddKeyEntry(W);
        BBAddKeyEntry(X);
        BBAddKeyEntry(Y);
        BBAddKeyEntry(Z);
        BBAddKeyEntry(F1);
        BBAddKeyEntry(F2);
        BBAddKeyEntry(F3);
        BBAddKeyEntry(F4);
        BBAddKeyEntry(F5);
        BBAddKeyEntry(F6);
        BBAddKeyEntry(F7);
        BBAddKeyEntry(F8);
        BBAddKeyEntry(F9);
        BBAddKeyEntry(F10);
        BBAddKeyEntry(F11);
        BBAddKeyEntry(F12);
        BBAddKeyEntry(Insert);
        BBAddKeyEntry(Delete);
        BBAddKeyEntry(Home);
        BBAddKeyEntry(End);
        BBAddKeyEntry(MouseLeftButton);
        BBAddKeyEntry(MouseRightButton);
        BBAddKeyEntry(MouseMiddleButton);
        BBAddKeyEntry(GamePadA);
        BBAddKeyEntry(GamePadB);
        BBAddKeyEntry(GamePadX);
        BBAddKeyEntry(GamePadY);
        BBAddKeyEntry(GamePadUp);
        BBAddKeyEntry(GamePadDown);
        BBAddKeyEntry(GamePadLeft);
        BBAddKeyEntry(GamePadRight);
        BBAddKeyEntry(GamePadStart);
        BBAddKeyEntry(GamePadBack);
        BBAddKeyEntry(GamePadSelect);
        BBAddKeyEntry(GamePadLeftThumb);
        BBAddKeyEntry(GamePadRightThumb);
        BBAddKeyEntry(GamePadLeftShoulder);
        BBAddKeyEntry(GamePadRightShoulder);
#       undef BBAddKeyEntry

        codeToStringMap = stringToCodeMap;

        std::sort(stringToCodeMap.begin(), stringToCodeMap.end(), CompareByString());
        std::sort(codeToStringMap.begin(), codeToStringMap.end(), CompareByCode());
    }

    const char* Key::ToString(Code value)
    {
        std::vector<Entry>::const_iterator it = std::lower_bound(codeToStringMap.begin(), codeToStringMap.end(), Entry(nullptr, value), CompareByCode());
        if ((*it).second == value)
            return (*it).first;
        else
            return "None";
    }

    Key::Code Key::Parse(const char* value)
    {
        if (value == nullptr)
            return None;

        std::vector<Entry>::const_iterator it = std::lower_bound(stringToCodeMap.begin(), stringToCodeMap.end(), Entry(value, None), CompareByString());
        if (String::EqualsCharsIgnoreCase((*it).first, value))
            return (*it).second;
        else
            return None;
    }
}