namespace Bibim
{
    ScriptObject::ScriptObject()
        : type(VoidType)
    {
    }

    ScriptObject::ScriptObject(bool value)
        : type(BooleanType),
          value(value)
    {
    }

    ScriptObject::ScriptObject(int value)
        : type(IntType),
          value(value)
    {
    }

    ScriptObject::ScriptObject(uint value)
        : type(UIntType),
          value(value)
    {
    }

    ScriptObject::ScriptObject(int64 value)
        : type(FloatType),
          value(value)
    {
    }

    ScriptObject::ScriptObject(float value)
        : type(FloatType),
          value(value)
    {
    }

    ScriptObject::ScriptObject(Color value)
        : type(ColorType),
          value(static_cast<uint>(value.ToARGB()))

    {
    }

    ScriptObject::ScriptObject(Vector2 value)
        : type(Float2Type),
          value(value.X, value.Y)
    {
    }

    ScriptObject::ScriptObject(Vector3 value)
        : type(Float3Type),
          value(new SixteenBytes(value.X, value.Y, value.Z, 0.0f))
    {
    }

    ScriptObject::ScriptObject(Vector4 value)
        : type(Float3Type),
          value(new SixteenBytes(value.X, value.Y, value.Z, value.W))
    {
    }

    ScriptObject::ScriptObject(const char* value)
        : type(StringType),
          value(new String(value))
    {
    }

    ScriptObject::ScriptObject(const String& value)
        : type(StringType),
          value(new String(value))
    {
    }

    ScriptObject::ScriptObject(SharedObject* value)
        : type(SharedObjectType),
          value(new SharedObjectPtr(value))
    {
    }

    ScriptObject::ScriptObject(void* value)
        : type(LightObjectType),
          value(value)
    {
    }

    ScriptObject::Type ScriptObject::GetType() const
    {
        return type;
    }

    bool ScriptObject::operator != (const ScriptObject& right) const
    {
        return !operator == (right);
    }
}