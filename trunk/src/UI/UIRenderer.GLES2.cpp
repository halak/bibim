#include <Bibim/Config.h>
#if (defined(BIBIM_USE_OPENGLES2))

#include <Bibim/UIRenderer.GLES2.h>
#include <Bibim/Assert.h>
#include <Bibim/BinaryReader.h>
#include <Bibim/BlendMode.h>
#include <Bibim/CheckedRelease.h>
#include <Bibim/Color.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/GLES2.h>
#include <Bibim/GraphicsDevice.GLES2.h>
#include <Bibim/Math.h>
#include <Bibim/Memory.h>
#include <Bibim/Matrix4.h>
#include <Bibim/ShaderEffect.GLES2.h>
#include <Bibim/Texture2D.GLES2.h>

namespace Bibim
{
    UIRenderer::UIRenderer()
        : Base(BBMakeFOURCC('O', 'G', 'L', '_')),
          vbo(0),
          ibo(0)
    {
    }

    UIRenderer::UIRenderer(GraphicsDevice* graphicsDevice, GameAssetStorage* storage, const String& shaderEffectDirectory)
        : Base(BBMakeFOURCC('O', 'G', 'L', '_'), graphicsDevice, storage, shaderEffectDirectory),
          vbo(0),
          ibo(0)
    {
    }

    UIRenderer::~UIRenderer()
    {
        if (ibo)
            glDeleteBuffers(1, &ibo);
        if (vbo)
            glDeleteBuffers(1, &vbo);
    }

    void UIRenderer::Begin()
    {
#       if (defined(BIBIM_PLATFORM_EMSCRIPTEN))
        if (vbo == 0)
            glGenBuffers(1, &vbo);
        if (ibo == 0)
            glGenBuffers(1, &ibo);
#       endif

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_POLYGON_OFFSET_FILL);
        glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
        glDisable(GL_SAMPLE_COVERAGE);
        glDisable(GL_STENCIL_TEST);
        glLineWidth(1.0f);

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

    void UIRenderer::DrawDebugLines(int count, const Vector2* p, Color color)
    {
        DrawLines(count, p, color);
    }

    void UIRenderer::DrawDebugLines(int count, const Vector2* p, const Color* c)
    {
        DrawLines(count, p, c);
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

    void UIRenderer::DrawTriangles(int count, const Vector2* p, const Vector2* uv, const Color* color, Texture2D* texture)
    {
        if (count == 0)
            return;
        BBAssert(count > 0 && p && uv && color && texture);

        Flush();

        count -= (count % 3);

        for (int i = 0; i < count; i++)
            vb[i] = Vertex(p[i], color[i].ToARGB(), uv[i]);

        glActiveTexture(GL_TEXTURE0);
        if (texture)
            glBindTexture(GL_TEXTURE_2D, texture->GetHandle());
        else
            glBindTexture(GL_TEXTURE_2D, 0);
        DrawArrays(GL_TRIANGLES, count);
    }

    void UIRenderer::DrawQuads(Texture2D* texture, Texture2D* mask, int vertexStart, int /*numberOfVertices*/, int numberOfQuads)
    {   
        glActiveTexture(GL_TEXTURE0);
        GLES2::CheckLastError("glActiveTexture");
        if (texture)
            glBindTexture(GL_TEXTURE_2D, texture->GetHandle());
        else
            glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE1);
        if (mask)
            glBindTexture(GL_TEXTURE_2D, mask->GetHandle());
        else
            glBindTexture(GL_TEXTURE_2D, 0);

        const int count = numberOfQuads * IndicesPerQuad / TrianglesPerQuad;
        const int index = static_cast<int>(vertexStart / VerticesPerQuad) * IndicesPerQuad;

#       if (defined(BIBIM_PLATFORM_EMSCRIPTEN))
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, reinterpret_cast<const GLvoid*>(index * sizeof(ushort)));
#       else
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, &ib[index]);
#       endif
        GLES2::CheckLastError("glDrawElements");
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

        if (ibo)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, ib.size() * sizeof(ushort), &ib[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    }

    void UIRenderer::OnEffectBegan(PixelMode mode, ShaderEffect* effect)
    {
        GLuint handle = effect->GetHandle();
        glUseProgram(handle);
        GLES2::CheckLastError("glUseProgram");
        glUniformMatrix4fv(effect->GetMVPTransformLocation(), 1, GL_FALSE, mvpTransform);
        GLES2::CheckLastError("glUniformMatrix4fv");

        if (mode != ColorOnlyMode)
            glUniform1i(effect->GetMainSamplerLocation(), 0);
        if (mode == MaskedColorMode || mode == MaskedColorTextureMode || mode == MaskedAlphaTextureMode)
            glUniform1i(effect->GetMaskSamplerLocation(), 1);

        const Vertex* v = &vb[0];
        const byte* first = reinterpret_cast<const byte*>(v);
        const int position = reinterpret_cast<const byte*>(&v->Position) - first;
        const int color = reinterpret_cast<const byte*>(&v->Color) - first;
        const int texCoord1 = reinterpret_cast<const byte*>(&v->TexCoord1) - first;
        const int texCoord2 = reinterpret_cast<const byte*>(&v->TexCoord2) - first;

        if (vbo)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, vb.size() * sizeof(Vertex), &vb[0], GL_DYNAMIC_DRAW);
        }

#       if (defined(BIBIM_PLATFORM_EMSCRIPTEN))
#       define VB(offset) reinterpret_cast<const GLvoid*>(offset)
#       else
#       define VB(offset) (first + offset)
#       endif

        glVertexAttribPointer(effect->GetPositionLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), VB(position));
        glEnableVertexAttribArray(effect->GetPositionLocation());

        glVertexAttribPointer(effect->GetColorLocation(), 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), VB(color));
        glEnableVertexAttribArray(effect->GetColorLocation());
        
        if (mode == ColorTextureOnlyMode || mode == MaskedColorTextureMode)
        {
            glVertexAttribPointer(effect->GetTexCoord1Location(), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), VB(texCoord1));
            glEnableVertexAttribArray(effect->GetTexCoord1Location());
        }
        else if (mode == AlphaTextureOnlyMode || mode == MaskedAlphaTextureMode)
        {
            glVertexAttribPointer(effect->GetTexCoord1Location(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), VB(texCoord1));
            glEnableVertexAttribArray(effect->GetTexCoord1Location());
        }

        if (mode == MaskedColorMode || mode == MaskedColorTextureMode || mode == MaskedAlphaTextureMode)
        {
            glVertexAttribPointer(effect->GetTexCoord2Location(), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), VB(texCoord2));
            glEnableVertexAttribArray(effect->GetTexCoord2Location());
        }

        if (vbo)
            glBindBuffer(GL_ARRAY_BUFFER, 0);

#       undef VB
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

    void UIRenderer::DrawArraysActually(unsigned int primitiveType, PixelMode pixelMode, int numberOfVertices, Texture2D* texture, Texture2D* mask)
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

#endif