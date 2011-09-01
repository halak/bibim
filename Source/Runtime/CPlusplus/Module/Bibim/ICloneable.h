#pragma once
#ifndef __BIBIM_CLONEABLE_INTERFACE__
#define __BIBIM_CLONEABLE_INTERFACE__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class ICloneable
        {
            BBInterfaceFOURCC('I', 'C', 'L', 'N');
            public:
                virtual ~ICloneable() { }

                virtual ICloneable* Clone() const;
                virtual ICloneable* CloneWith(CloningContext& context) const = 0;

            protected:
                ICloneable();
                ICloneable(CloningContext& context);
        };
    }

#endif