#pragma once
#ifndef __BIBIM_SCRIPTINGCONTEXT_H__
#define __BIBIM_SCRIPTINGCONTEXT_H__

    namespace Bibim
    {
        enum ScriptObjectType
        {
            ScriptNullType,
            ScriptBooleanType,
            ScriptIntType,
            ScriptUIntType,
            ScriptLongIntType,
            ScriptFloatType,
            ScriptColorType,
            ScriptInt2Type,
            ScriptInt3Type,
            ScriptInt4Type,
            ScriptFloat2Type,
            ScriptFloat3Type,
            ScriptFloat4Type,
            ScriptStringType,
            ScriptVector2Type = ScriptFloat2Type,
            ScriptVector3Type = ScriptFloat3Type,
            ScriptVector4Type = ScriptFloat4Type,
        };

        class ScriptingContext
        {
            public:
                ScriptingContext();
                ~ScriptingContext();

            private:
        };
    }

#endif