#include <Bibim/PCH.h>
#include <Bibim/Font.h>
#include <Bibim/AssetStreamReader.h>
#include <Bibim/Assert.h>
#include <Bibim/FontCache.h>
#include <Bibim/FontLibrary.h>
#include <Bibim/FontString.h>
#include <Bibim/Math.h>
#include <Bibim/Numerics.h>
#include <Bibim/String.h>
#include <Bibim/Glyph.h>
#include <Bibim/GlyphTable.h>
#include <Bibim/TypingContext.h>

namespace Bibim
{
    const Font::GlyphDictionary Font::EmptyGlyphs;

    Font::Font()
        : library(nullptr),
          color(Color(0, 0, 0, 255)),
          strokeColor(Color(0, 0, 0, 255)),
          shadowColor(Color(0, 0, 255)),
          spacing(1.0f),
          parametersPointer(new FontCacheParameters()),
          parameters(*parametersPointer),
          cache(nullptr)
    {
    }

    Font::Font(FontLibrary* library)
        : library(library),
          color(Color(0, 0, 0, 255)),
          strokeColor(Color(0, 0, 0, 255)),
          shadowColor(Color(0, 0, 255)),
          spacing(1.0f),
          parametersPointer(new FontCacheParameters()),
          parameters(*parametersPointer),
          cache(nullptr)
    {
        if (library)
            library->Add(this);
    }

    Font::Font(const Font& original)
        : library(original.library),
          color(original.color),
          strokeColor(original.strokeColor),
          shadowColor(original.shadowColor),
          spacing(original.spacing),
          parametersPointer(new FontCacheParameters(original.parameters)),
          parameters(*parametersPointer),
          cache(original.cache)
    {
    }

    Font::~Font()
    {
        if (library)
            library->Remove(this);

        delete parametersPointer;
    }

    Vector2 Font::Measure(const String& text)
    {
        return Measure(text, Float::Max);
    }

    Vector2 Font::Measure(const String& text, float boundary)
    {
        return Measure(FontString(this, text), boundary);
    }

    Vector2 Font::Measure(const FontString& fontString)
    {
        return Measure(fontString, Float::Max);
    }
    
    Vector2 Font::Measure(const FontString& fontString, float boundary)
    {
        BBAssert(fontString.GetFont() == this);

       TypingContext context(fontString, boundary);

        Vector2 result = Vector2::Zero;
        while (context.MoveNext())
        {
            const Vector2 current = context.GetPosition();
            result.X = Math::Max(result.X, current.X + context.GetRegularGlyph()->GetAdvance().X);
            result.Y = Math::Max(result.Y, current.Y + GetLineHeight());
        }

        return result;
    }

    void Font::SetLibrary(FontLibrary* value)
    {
        if (library != value)
        {
            if (library)
                library->Remove(this);

            library = value;
            cache.Reset();
            IncreaseRevision();

            if (library)
                library->Add(this);
        }
    }

    const String& Font::GetFaceURI() const
    {
        return parameters.FaceURI;
    }

    void Font::SetFaceURI(const String& value)
    {
        if (parameters.FaceURI != value)
        {
            parameters.FaceURI = value;
            cache.Reset();
            IncreaseRevision();
        }
    }

    void Font::SetFace(const byte* data, int length)
    {
        if (data == nullptr || length <= 0)
            return;

        parameters.FaceURI = String::Empty;
        parameters.FaceData.resize(length);
        parameters.FaceData.assign(&data[0], &data[length]);
        cache.Reset();
        IncreaseRevision();        
    }

    float Font::GetSize() const
    {
        return parameters.FontSize;
    }

    void Font::SetSize(float value)
    {
        value = Math::Max(value, 0.0f);
        if (parameters.FontSize != value)
        {
            parameters.FontSize = value;
            cache.Reset();
            IncreaseRevision();
        }
    }

    float Font::GetStrokeSize() const
    {
        return parameters.StrokeSize;
    }

    void Font::SetStrokeSize(float value)
    {
        value = Math::Max(value, 0.0f);
        if (parameters.StrokeSize != value)
        {
            parameters.StrokeSize = value;
            cache.Reset();
            IncreaseRevision();
        }
    }

    float Font::GetWeights() const
    {
        return parameters.Weights;
    }

    void Font::SetWeights(float value)
    {
        value = Math::Max(value, 0.0f);
        if (parameters.Weights != value)
        {
            parameters.Weights = value;
            cache.Reset();
            IncreaseRevision();
        }
    }

    bool Font::GetBold() const
    {
        return parameters.Weights > 0.0f;
    }

    void Font::SetBold(bool value)
    {
        if (GetBold() != value)
        {
            parameters.Weights = value ? 1.0f : 0.0f;
            cache.Reset();
            IncreaseRevision();
        }
    }

    float Font::GetShear() const
    {
        return parameters.Shear;
    }

    void Font::SetShear(float value)
    {
        value = Math::Max(value, 0.0f);
        if (parameters.Shear != value)
        {
            parameters.Shear = value;
            cache.Reset();
            IncreaseRevision();
        }
    }

    bool Font::GetItalic() const
    {
        return parameters.Shear > 0.0f;
    }

    void Font::SetItalic(bool value)
    {
        if (GetItalic() != value)
        {
            parameters.Shear = value ? 0.2f : 0.0f;
            cache.Reset();
            IncreaseRevision();
        }
    }
    
    int Font::GetShadowSize() const
    {
        return parameters.ShadowSize;
    }

    void Font::SetShadowSize(int value)
    {
        value = Math::Max(value, 0);
        if (parameters.ShadowSize != value)
        {
            parameters.ShadowSize = value;
            cache.Reset();
            IncreaseRevision();
        }
    }

    float Font::GetShadowSpread() const
    {
        return parameters.ShadowSpread;
    }

    void Font::SetShadowSpread(float value)
    {
        value = Math::Max(value, 0.0001f);
        if (parameters.ShadowSpread != value)
        {
            parameters.ShadowSpread = value;
            cache.Reset();
            IncreaseRevision();
        }
    }

    float Font::GetShadowThickness() const
    {
        return parameters.ShadowThickness;
    }

    void Font::SetShadowThickness(float value)
    {
        value = Math::Clamp(value, 0.0001f, 0.9999f);
        if (parameters.ShadowThickness != value)
        {
            parameters.ShadowThickness = value;
            cache.Reset();
            IncreaseRevision();
        }
    }

    Vector2 Font::GetShadowOffset() const
    {
        return shadowOffset;
    }

    void Font::SetShadowOffset(Vector2 value)
    {
        if (shadowOffset != value)
        {
            shadowOffset = value;
            IncreaseRevision();
        }
    }

    float Font::GetScale() const
    {
        return parameters.Scale;
    }

    void Font::SetScale(float value)
    {
        value = Math::Max(value, 0.0f);
        if (parameters.Scale != value)
        {
            parameters.Scale = value;
            cache.Reset();
            IncreaseRevision();
        }
    }

    bool Font::GetHinting() const
    {
        return parameters.Hinting;
    }

    void Font::SetHinting(bool value)
    {
        if (parameters.Hinting != value)
        {
            parameters.Hinting = value;
            cache.Reset();
            IncreaseRevision();
        }
    }

    bool Font::GetIgnoreBitmap() const
    {
        return parameters.IgnoreBitmap;
    }

    void Font::SetIgnoreBitmap(bool value)
    {
        if (parameters.IgnoreBitmap != value)
        {
            parameters.IgnoreBitmap = value;
            cache.Reset();
            IncreaseRevision();
        }
    }

    void Font::SetColor(Color value)
    {
        if (color != value)
        {
            color = value;
            IncreaseRevision();
        }
    }

    void Font::SetStrokeColor(Color value)
    {
        if (strokeColor != value)
        {
            strokeColor = value;
            IncreaseRevision();
        }
    }

    void Font::SetShadowColor(Color value)
    {
        if (shadowColor != value)
        {
            shadowColor = value;
            IncreaseRevision();
        }
    }

    void Font::SetSpacing(float value)
    {
        value = Math::Max(value, 0.0f);
        if (spacing != value)
        {
            spacing = value;
            IncreaseRevision();
        }
    }

    const Glyph* Font::GetRegularGlyph(int code) const
    {
        return GetCache()->GetGlyph(code);
    }

    const Glyph* Font::GetStrokedGlyph(int code) const
    {
        if (const GlyphTable* t = GetCache()->GetStrokedGlyphTable())
            return t->Find(code);
        else
            return nullptr;
    }

    const Glyph* Font::GetShadowGlyph(int code) const
    {
        if (const GlyphTable* t = GetCache()->GetShadowGlyphTable())
            return t->Find(code);
        else
            return nullptr;
    }

    float Font::GetAscender() const
    {
        return GetCache()->GetAscender();
    }

    float Font::GetDescender() const
    {
        return GetCache()->GetDescender();
    }

    float Font::GetLineHeight() const
    {
        return GetCache()->GetLineHeight();
    }

    const Font::GlyphDictionary& Font::GetCachedRegularGlyphs() const
    {
        FontCache* c = GetCache();
        if (c && c->GetRegularGlyphTable())
            return c->GetRegularGlyphTable()->GetGlyphs();
        else
            return EmptyGlyphs;
    }

    const Font::GlyphDictionary& Font::GetCachedStrokedGlyphs() const
    {
        FontCache* c = GetCache();
        if (c && c->GetStrokedGlyphTable())
            return c->GetStrokedGlyphTable()->GetGlyphs();
        else
            return EmptyGlyphs;
    }

    const Font::GlyphDictionary& Font::GetCachedShadowGlyphs() const
    {
        FontCache* c = GetCache();
        if (c && c->GetShadowGlyphTable())
            return c->GetShadowGlyphTable()->GetGlyphs();
        else
            return EmptyGlyphs;
    }

    FontCache* Font::GetCache() const
    {
        if (cache == nullptr && library)
            cache = library->GetCache(parameters);

        return cache;
    }

    GameAsset* Font::Create(StreamReader& reader, GameAsset* existingInstance)
    {
        Font* result = nullptr;
        
        if (existingInstance)
            result = static_cast<Font*>(existingInstance);
        else
            result = new Font();

        result->SetStatus(GameAsset::LoadingStatus);
        result->cache.Reset();
        result->library = static_cast<FontLibrary*>(reader.ReadModule(FontLibrary::ClassID));
        result->parameters.FaceURI = reader.ReadString();
        result->parameters.FontSize = reader.ReadFloat();
        result->parameters.StrokeSize = reader.ReadFloat();
        result->parameters.Weights = reader.ReadFloat();
        result->parameters.Shear = reader.ReadFloat();
        result->parameters.ShadowSize = reader.ReadInt();
        result->parameters.ShadowSpread = reader.ReadFloat();
        result->parameters.ShadowThickness = reader.ReadFloat();
        result->shadowOffset = reader.ReadVector2();
        result->parameters.Scale = reader.ReadFloat();
        result->parameters.Hinting = reader.ReadBool();
        result->parameters.IgnoreBitmap = reader.ReadBool();
        result->spacing = reader.ReadFloat();
        result->color = reader.ReadColor();
        result->strokeColor = reader.ReadColor();
        result->shadowColor = reader.ReadColor();
        result->IncreaseRevision();
        result->SetStatus(GameAsset::CompletedStatus);

        return result;
    }
}