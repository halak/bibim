#include <Bibim/Config.h>
#include <Bibim/UIEffectMap.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/UIGeometryEffect.h>
#include <Bibim/UIPixelEffect.h>

namespace Bibim
{
    BBImplementsComponent(UIEffectMap);

    UIEffectMap::UIEffectMap()
    {
    }

    UIEffectMap::~UIEffectMap()
    {
    }

    void UIEffectMap::Insert(UIPixelEffect* item)
    {
        if (item == nullptr)
            return;

        const int index = item->GetSlotIndex();
        if (index >= static_cast<int>(pixelEffects.size()))
            pixelEffects.resize(index + 1);

        pixelEffects[index] = item;
    }

    bool UIEffectMap::Remove(UIPixelEffect* item)
    {
        if (item == nullptr)
            return false;

        const int index = item->GetSlotIndex();
        if (0 <= index && index < static_cast<int>(pixelEffects.size()))
        {
            if (pixelEffects[index] == item)
            {
                pixelEffects[index].Reset();
                return true;
            }
        }

        return false;
    }

    bool UIEffectMap::Remove(int index)
    {
        if (0 <= index && index < static_cast<int>(pixelEffects.size()))
        {
            pixelEffects[index].Reset();
            return true;
        }
        else
            return false;
    }

    void UIEffectMap::RemoveAll()
    {
        pixelEffects.clear();
    }

    UIPixelEffect* UIEffectMap::FindPixelEffect(const String& name)
    {
        for (PixelEffectCollection::const_iterator it = pixelEffects.begin(); it != pixelEffects.end(); it++)
        {
            if ((*it)->GetName() == name)
                return (*it);
        }

        return nullptr;
    }

    void UIEffectMap::SetGeometryEffect(UIGeometryEffect* value)
    {
        geomEffect = value;
    }

    void UIEffectMap::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        geomEffect = static_cast<UIGeometryEffect*>(reader.ReadComponent());
        const int count = static_cast<int>(reader.ReadShortInt());
        pixelEffects.reserve(count);
        for (int i = 0; i < count; i++)
            pixelEffects.push_back(static_cast<UIPixelEffect*>(reader.ReadComponent()));
    }

    void UIEffectMap::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        geomEffect = context.Clone(o->geomEffect);
        pixelEffects.reserve(o->pixelEffects.size());
        for (PixelEffectCollection::const_iterator it = o->pixelEffects.begin(); it != o->pixelEffects.end(); it++)
            pixelEffects.push_back(context.Clone(*it));
    }
}