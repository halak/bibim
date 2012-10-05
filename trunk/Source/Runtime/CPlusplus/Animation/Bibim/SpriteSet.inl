namespace Bibim
{
    Sprite* SpriteSet::FindByChars(const char* name) const
    {
        if (name)
            return Find(name);
        else
            return nullptr;
    }
}