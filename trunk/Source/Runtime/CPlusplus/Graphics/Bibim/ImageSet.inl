namespace Bibim
{
    Image* ImageSet::FindByChars(const char* name) const
    {
        if (name)
            return Find(name);
        else
            return nullptr;
    }
}