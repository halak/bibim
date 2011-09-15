namespace Bibim
{
    Quaternion::Quaternion()
        : X(0.0f), Y(0.0f), Z(0.0f), W(0.0f)
    {
    }

    Quaternion::Quaternion(float X, float Y, float Z)
        : X(X), Y(Y), Z(Z), W(0.0f)
    {
    }

    Quaternion::Quaternion(float X, float Y, float Z, float W)
        : X(X), Y(Y), Z(Z), W(W)
    {
    }

    Quaternion::Quaternion(const Quaternion& original)
        : X(original.X), Y(original.Y), Z(original.Z), W(original.W)
    {
    }

    Quaternion& Quaternion::operator = (const Quaternion& right)
    {
        X = right.X;
        Y = right.Y;
        Z = right.Z;
        W = right.W;
        return *this;
    }

    bool Quaternion::operator == (const Quaternion& right) const
    {
        return X == right.X && Y == right.Y && Z == right.Z && W == right.W;
    }

    bool Quaternion::operator != (const Quaternion& right) const
    {
        return !operator == (right);
    }
}