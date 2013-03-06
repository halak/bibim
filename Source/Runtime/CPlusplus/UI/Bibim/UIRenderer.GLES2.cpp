#include <Bibim/PCH.h>
#include <Bibim/UIRenderer.GLES2.h>
#include <Bibim/Assert.h>
#include <Bibim/BinaryReader.h>
#include <Bibim/BlendMode.h>
#include <Bibim/CheckedRelease.h>
#include <Bibim/Color.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/GraphicsDevice.GLES2.h>
#include <Bibim/Math.h>
#include <Bibim/Memory.h>
#include <Bibim/Matrix4.h>
#include <Bibim/ShaderEffect.GLES2.h>
#include <Bibim/Texture2D.GLES2.h>

namespace Bibim
{
    UIRenderer::UIRenderer()
        : Base(BBMakeFOURCC('O', 'G', 'L', '_'))
    {
    }

    UIRenderer::UIRenderer(GraphicsDevice* graphicsDevice, GameAssetStorage* storage, const String& shaderEffectDirectory)
        : Base(BBMakeFOURCC('O', 'G', 'L', '_'), graphicsDevice, storage, shaderEffectDirectory)
    {
    }

    UIRenderer::~UIRenderer()
    {
    }

    void UIRenderer::Begin()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_POLYGON_OFFSET_FILL);
        glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
        glDisable(GL_SAMPLE_COVERAGE);
        glDisable(GL_STENCIL_TEST);
        glDisable(GL_SCISSOR_TEST);

        Base::Begin();
    }

    void UIRenderer::End()
    {
        Base::End();
    }

    UIRenderer::Vertex* UIRenderer::LockVB(int /*size*/)
    {
        return &vb[0];
    }

    void UIRenderer::UnlockVB()
    {
    }

    void UIRenderer::DrawLines(int count, const Vector2* p, Color color)
    {
        if (count == 0)
            return;
        BBAssert(count > 0 && p);

        Flush();

        const unsigned long argb = color.ToARGB();
        for (int i = 0; i < count; i++)
            vb[i] = Vertex(p[i], argb);

        DrawArrays(GL_LINE_STRIP, count);
    }

    void UIRenderer::DrawLines(int count, const Vector2* p, const Color* c)
    {
        if (count == 0)
            return;
        BBAssert(count > 0 && p && c);

        Flush();

        for (int i = 0; i < count; i++)
            vb[i] = Vertex(p[i], c[i].ToARGB());

        DrawArrays(GL_LINE_STRIP, count);
    }

    void UIRenderer::DrawTriangles(int count, const Vector2* p, Color color)
    {
        if (count == 0)
            return;
        BBAssert(count > 0 && p);

        Flush();

        count -= (count % 3);

        const unsigned long argb = color.ToARGB();
        for (int i = 0; i < count; i++)
            vb[i] = Vertex(p[i], argb);

        DrawArrays(GL_TRIANGLES, count);
    }

    void UIRenderer::DrawQuads(Texture2D* texture, Texture2D* mask, int vertexStart, int /*numberOfVertices*/, int numberOfQuads)
    {   
        glActiveTexture(GL_TEXTURE0);
        if (texture)
            glBindTexture(GL_TEXTURE_2D, texture->GetHandle());
        else
            glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE1);
        if (mask)
            glBindTexture(GL_TEXTURE_2D, mask->GetHandle());
        else
            glBindTexture(GL_TEXTURE_2D, 0);

        glDrawElements(GL_TRIANGLES,
                       numberOfQuads * IndicesPerQuad / TrianglesPerQuad,
                       GL_UNSIGNED_SHORT,
                       &ib[static_cast<int>(vertexStart / VerticesPerQuad) * IndicesPerQuad]);
    }

    void UIRenderer::OnCreateQuadsCache(int vbSize, int numberOfIndices)
    {
        vb.resize(vbSize / sizeof(Vertex));
        ib.resize(numberOfIndices);

        for (ushort i = 0, v = 0; i < numberOfIndices; i += IndicesPerQuad, v += VerticesPerQuad)
        {
            ib[i + 0] = v + 0;
            ib[i + 1] = v + 1;
            ib[i + 2] = v + 2;
            ib[i + 3] = v + 3;
            ib[i + 4] = v + 2;
            ib[i + 5] = v + 1;
        }
    }

    void UIRenderer::OnEffectBegan(PixelMode mode, ShaderEffect* effect)
    {
        GLuint handle = effect->GetHandle();
        glUseProgram(handle);
        glUniformMatrix4fv(effect->GetMVPTransformLocation(), 1, GL_FALSE, mvpTransform);

        if (mode != ColorOnlyMode)
            glUniform1i(effect->GetMainSamplerLocation(), 0);
        if (mode == MaskedColorMode || mode == MaskedColorTextureMode || mode == MaskedAlphaTextureMode)
            glUniform1i(effect->GetMaskSamplerLocation(), 1);

        const Vertex* v = &vb[0];
        const void* positions = &v->Position;
        const void* colors = &v->Color;
        const void* texCoords1 = &v->TexCoord1;
        const void* texCoords2 = &v->TexCoord2;

        glVertexAttribPointer(effect->GetPositionLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), positions);
        glEnableVertexAttribArray(effect->GetPositionLocation());

        glVertexAttribPointer(effect->GetColorLocation(), 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), colors);
        glEnableVertexAttribArray(effect->GetColorLocation());

        if (mode == ColorTextureOnlyMode || mode == AlphaTextureOnlyMode || mode == MaskedColorTextureMode || mode == MaskedAlphaTextureMode)
        {
            glVertexAttribPointer(effect->GetTexCoord1Location(), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), texCoords1);
            glEnableVertexAttribArray(effect->GetTexCoord1Location());
        }

        if (mode == MaskedColorMode || mode == MaskedColorTextureMode || mode == MaskedAlphaTextureMode)
        {
            glVertexAttribPointer(effect->GetTexCoord2Location(), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), texCoords2);
            glEnableVertexAttribArray(effect->GetTexCoord2Location());
        }
    }

    void UIRenderer::OnEffectEnded(PixelMode /*mode*/, ShaderEffect* /*effect*/)
    {
        glUseProgram(0);
    }

    void UIRenderer::OnTransformChanged(const Matrix4& newValue)
    {
        mvpTransform = newValue * GetViewTransform() * GetProjectionTransform();
    }

    void UIRenderer::OnBlendModeChanged(BlendMode newValue)
    {
        GLenum blendOp = GL_FUNC_ADD;
        GLenum srcBlend = GL_SRC_ALPHA;
        GLenum dstBlend = GL_ONE_MINUS_SRC_ALPHA;
        switch (newValue)
        {
            case NormalBlend:
                srcBlend = GL_SRC_ALPHA;
                dstBlend = GL_ONE_MINUS_SRC_ALPHA;
                break;
            case AdditiveBlend:
                srcBlend = GL_SRC_ALPHA;
                dstBlend = GL_ONE;
                break;
            case LightenBlend:
                srcBlend = GL_SRC_ALPHA;
                dstBlend = GL_ONE;
                break;
            case DarkenBlend:
                blendOp = GL_FUNC_SUBTRACT;
                srcBlend = GL_SRC_ALPHA;
                dstBlend = GL_ONE_MINUS_SRC_ALPHA;
                break;
            case MultiplyBlend:
                srcBlend = GL_ZERO;
                dstBlend = GL_SRC_COLOR;
                break;
            case ScreenBlend:
                srcBlend = GL_ONE_MINUS_DST_COLOR;
                dstBlend = GL_ONE;
                break;
        }

        glBlendEquation(blendOp);
        glBlendFunc(srcBlend, dstBlend);
    }

    void UIRenderer::DrawArraysActually(GLenum primitiveType, PixelMode pixelMode, int numberOfVertices, Texture2D* texture, Texture2D* mask)
    {
        BeginEffect(pixelMode);
        glActiveTexture(GL_TEXTURE0);
        if (texture)
            glBindTexture(GL_TEXTURE_2D, texture->GetHandle());
        else
            glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE1);
        if (mask)
            glBindTexture(GL_TEXTURE_2D, mask->GetHandle());
        else
            glBindTexture(GL_TEXTURE_2D, 0);
        glDrawArrays(primitiveType, 0, numberOfVertices);
        EndEffect(pixelMode);
    }
}