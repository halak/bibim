#pragma once
#ifndef __BIBIM_SCRIPT_H__
#define __BIBIM_SCRIPT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameAsset.h>
#   include <Bibim/Any.h>
#   include <Bibim/String.h>
#   include <vector>

    namespace Bibim
    {
        class Script : public GameAsset
        {
            BBSerializableAssetClass(Script, GameAsset, 'S', 'C', 'R', 'T');
            public:
                struct Function
                {
                    String Name;
                    int Position;
                    int ArgumentStackSize;
                    std::vector<AnyType> ReturnTypes;
                    std::vector<AnyType> ParameterTypes;
                };

            public:
                typedef std::vector<byte> Buffer;
                typedef std::vector<String> StringCollection;
                typedef std::vector<Function> FunctionTable;

            public:
                Script();
                virtual ~Script();

                const Function* Find(const String& name) const;

                inline const Buffer& GetBuffer() const;
                inline const StringCollection& GetStringTable() const;

            private:
                struct MoveTag {};
                Script(Buffer& buffer, FunctionTable& functionTable, StringCollection& stringTable, MoveTag);

            private:
                Buffer buffer;
                FunctionTable functionTable;
                StringCollection stringTable;
        };
    }

#endif