namespace Bibim
{
    Matrix4::operator float* ()
    {
        return &M00;
    }

    Matrix4::operator const float* () const
    {
        return &M00;
    }

}