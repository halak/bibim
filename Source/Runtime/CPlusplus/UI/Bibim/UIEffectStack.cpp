#include <Bibim/Config.h>
#include <Bibim/UIEffectStack.h>
#include <Bibim/Assert.h>
#include <Bibim/IMage.h>
#include <Bibim/Math.h>
#include <Bibim/UIEffectMap.h>
#include <Bibim/UIPixelEffect.h>
#include <Bibim/UIMaskEffect.h>

namespace Bibim
{
    UIEffectStack::UIEffectStack()
        : depth(0),
          numberOfClasses(16),
          maxDepth(16),
          isShaderFunctionRendering(false)
    {
        map.resize(numberOfClasses * maxDepth);
    }

    UIEffectStack::UIEffectStack(bool isShaderFunctionRendering)
        : depth(0),
          numberOfClasses(16),
          maxDepth(16),
          isShaderFunctionRendering(isShaderFunctionRendering)
    {
        map.resize(numberOfClasses * maxDepth);
    }

    UIEffectStack::~UIEffectStack()
    {
    }

    bool UIEffectStack::Push(UIEffectMap* item)
    {
        ImagePtr mask = nullptr;
        return Push(item, mask);
    }

    bool UIEffectStack::Push(UIEffectMap* item, ImagePtr& outMask)
    {
        if (item == nullptr || item->GetPixelEffects().empty())
            return false;

        if (static_cast<int>(item->GetPixelEffects().size()) > numberOfClasses)
            ExpandClass(item->GetPixelEffects().size());
        if (depth >= maxDepth)
            ExpandDepth(maxDepth + 4);

        struct IsEffectorCreateable
        {
            static bool Do(UIPixelEffect* effect, bool isShaderFunctionRendering)
            {
                if (isShaderFunctionRendering)
                    return effect->IsShaderFunctionImplemented();
                else
                    return effect->IsFixedFunctionImplemented();
            }
        };

        topEffectors.clear();

        bool result = false;
        const int minCount = Math::Min(numberOfClasses, static_cast<int>(item->GetPixelEffects().size()));
        const UIPixelEffectPtr* effects = &item->GetPixelEffects()[0];
        if (depth > 0)
        {
            UIRenderer::EffectorPtr* oldLine = &map[(depth - 1) * numberOfClasses];
            UIRenderer::EffectorPtr* newLine = &map[(depth + 0) * numberOfClasses];
            for (int i = 0; i < minCount; i++)
            {
                if (effects[i] && IsEffectorCreateable::Do(effects[i], isShaderFunctionRendering))
                {
                    newLine[i] = effects[i]->CreateEffector(oldLine[i], isShaderFunctionRendering);
                    result = true;
                }
                else
                    newLine[i] = oldLine[i];

                if (newLine[i])
                {
                    topEffectors.push_back(newLine[i]);

                    if (newLine[i]->IsMaskEffector())
                        outMask = StaticCast<UIMaskEffect::MaskEffector>(newLine[i])->GetMask();
                }
            }
            depth++;
        }
        else
        {
            UIRenderer::EffectorPtr* newLine = &map[0];
            for (int i = 0; i < minCount; i++)
            {
                if (effects[i] && IsEffectorCreateable::Do(effects[i], isShaderFunctionRendering))
                {
                    newLine[i] = effects[i]->CreateEffector(nullptr, isShaderFunctionRendering);
                    result = true;

                    if (newLine[i])
                    {
                        topEffectors.push_back(newLine[i]);

                        if (newLine[i]->IsMaskEffector())
                            outMask = StaticCast<UIMaskEffect::MaskEffector>(newLine[i])->GetMask();
                    }
                }
            }
            depth = 1;
        }

        return result;
    }

    bool UIEffectStack::Pop()
    {
        if (depth <= 0)
            return false;

        bool result = false;
        topEffectors.clear();
        if (depth > 1)
        {
            UIRenderer::EffectorPtr* newLine = &map[(depth - 2) * numberOfClasses];
            UIRenderer::EffectorPtr* currentLine = &map[(depth - 1) * numberOfClasses];
            for (int i = 0; i < numberOfClasses; i++)
            {
                if (currentLine[i] != newLine[i])
                    result = true;

                currentLine[i].Reset();

                if (newLine[i])
                    topEffectors.push_back(newLine[i]);
            }

            depth--;
        }
        else
        {
            UIRenderer::EffectorPtr* currentLine = &map[(depth - 1) * numberOfClasses];
            for (int i = 0; i < numberOfClasses; i++)
            {
                if (currentLine[i])
                {
                    currentLine[i].Reset();
                    result = true;
                }
            }

            depth = 0;
        }

        return result;
    }

    void UIEffectStack::Clear()
    {
        const int numberOfEffectors = depth * numberOfClasses;
        for (int i = 0; i < numberOfEffectors; i++)
            map[i].Reset();

        depth = 0;
        topEffectors.clear();
    }

    void UIEffectStack::ExpandClass(int newSize)
    {
        BBAssertDebug(newSize > numberOfClasses);
    }

    void UIEffectStack::ExpandDepth(int newSize)
    {
        BBAssertDebug(newSize > maxDepth);
    }
}