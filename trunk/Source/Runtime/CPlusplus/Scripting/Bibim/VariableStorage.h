//#pragma once
//#ifndef __BIBIM_WORKFLOW_VARIABLESTORAGE_H__
//#define __BIBIM_WORKFLOW_VARIABLESTORAGE_H__
//
//#   include <Bibim/FWD.h>
//#   include <Bibim/SharedObject.h>
//#   include <Bibim/Any.h>
//#   include <map>
//#   include <vector>
//
//    namespace Bibim
//    {
//        class VariableStorage : public SharedObject
//        {
//            BBObjectClass(VariableStorage, SharedObject, 'V', 'S', 'T', 'O');
//            public:
//                typedef std::map<String, Any> AnyDictionary;
//                typedef std::vector<Any> AnyCollection;
//
//            public:
//                VariableStorage();
//                VariableStorage(VariableStoragePtr reference);
//                virtual ~VariableStorage();
//
//                bool Contains(const String& name) const;
//
//                const Any& GetValue(const String& name) const;
//                const Any& GetValue(int index) const;
//                void SetValue(const String& name, const Any& value);
//                void SetValue(int index, const Any& value);
//
//                VariableStoragePtr GetReference() const;
//                void SetReference(VariableStoragePtr value);
//
//                const AnyDictionary& GetDictionary() const;
//
//            private:
//                VariableStoragePtr reference;
//                AnyDictionary variables;
//
//                AnyCollection arrangedVariables;
//        };
//    }
//
//#endif