#pragma once
#ifndef __BIBIM_ASSET_H__
#define __BIBIM_ASSET_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/URI.h>

    namespace Bibim
    {
        class Asset : public SharedObject
        {
            BBThisIsNoncopyableClass(Asset);
            public:
                virtual ~Asset();

                inline const URI& GetURI() const;

            protected:
                Asset();
                Asset(const URI& uri);

            private:
                URI uri;
        };
    }

#   include <Bibim/Asset.inl>

#endif