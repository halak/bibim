namespace Bibim
{
    Vector3 Matrix4::GetTranslation() const
    {
        return Vector3(M30, M31, M32);
    }

    Matrix4::operator float* ()
    {
        return &M00;
    }

    Matrix4::operator const float* () const
    {
        return &M00;
    }
}