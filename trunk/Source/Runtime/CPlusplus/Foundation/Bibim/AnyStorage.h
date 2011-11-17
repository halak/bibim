#pragma once
#ifndef __BIBIM_ANYSTORAGE_H__
#define __BIBIM_ANYSTORAGE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/Any.h>
#   include <Bibim/String.h>
#   include <map>
#   include <vector>

    namespace Bibim
    {
        class AnyStorage : public SharedObject
        {
            public:
                AnyStorage();
                virtual ~AnyStorage();

                void AddReference(AnyStorage* item);
                void RemoveReference(AnyStorage* item);
                void RemoveAllReferences();

                const Any& GetValue(const String& name) const;
                const Any& GetValueDirect(const String& name) const;
                void SetValue(const String& name, const Any& value);

            private:
                typedef std::map<String, Any> Dictionary;
                typedef std::vector<AnyStoragePtr> StorageCollection;

                Dictionary dictionary;
                StorageCollection references;
        };
    }

#   include <Bibim/AnyStorage.inl>

#endif