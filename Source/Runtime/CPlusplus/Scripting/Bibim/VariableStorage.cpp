//#include <Bibim/PCH.h>
//#include <Bibim/VariableStorage.h>
//#include <Bibim/Assert.h>
//#include <Bibim/String.h>
//
//namespace Bibim
//{
//    VariableStorage::VariableStorage()
//    {
//    }
//
//    VariableStorage::VariableStorage(VariableStoragePtr reference)
//        : reference(reference)
//    {
//    }
//
//    VariableStorage::~VariableStorage()
//    {
//    }
//
//    //void VariableStorage::OnCloning(const VariableStorage& original, CloningContext& context)
//    //{
//    //    reference = context.CloneObject(original.reference);
//    //    variables = original.variables;
//    //}
//
//    bool VariableStorage::Contains(const String& name) const
//    {
//        return variables.find(name) != variables.end() || (reference && reference->Contains(name));
//    }
//
//    const Any& VariableStorage::GetValue(const String& name) const
//    {
//        AnyDictionary::const_iterator it = variables.find(name);
//        if (it != variables.end())
//            return (*it).second;
//        else
//        {
//            if (reference)
//                return reference->GetValue(name);
//            else
//                return Any::Missing;
//        }
//    }
//
//    const Any& VariableStorage::GetValue(int index) const
//    {
//        BBAssert(0 <= index);
//
//        const int length = static_cast<int>(arrangedVariables.size());
//
//        if (index < length && arrangedVariables[index].GetType() != Any::MissingType)
//            return arrangedVariables[index];
//        else
//        {
//            if (reference)
//                return reference->GetValue(index);
//            else
//                return Any::Missing;
//        }
//    }
//
//    void VariableStorage::SetValue(const String& name, const Any& value)
//    {
//        AnyDictionary::iterator it = variables.find(name);
//        if (it != variables.end())
//        {
//            if (value != Any::Missing)
//                (*it).second = value;
//            else
//                variables.erase(it);
//        }
//        else
//        {
//            if (reference && reference->Contains(name))
//                reference->SetValue(name, value);
//            else
//                variables.insert(AnyDictionary::value_type(name, value));
//        }
//    }
//
//    void VariableStorage::SetValue(int index, const Any& value)
//    {
//        BBAssert(0 <= index);
//
//        if (index >= static_cast<int>(arrangedVariables.size()))
//            arrangedVariables.resize(index + 1, Any::MissingType);
//
//        arrangedVariables[index] = value;
//    }
//
//    VariableStoragePtr VariableStorage::GetReference() const
//    {
//        return reference;
//    }
//
//    void VariableStorage::SetReference(VariableStoragePtr value)
//    {
//        reference = value;
//    }
//
//    const VariableStorage::AnyDictionary& VariableStorage::GetDictionary() const
//    {
//        return variables;
//    }
//}