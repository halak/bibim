#include <Bibim/PCH.h>
#include <Bibim/UIRenderer.Windows.h>
#include <Bibim/Assert.h>
#include <Bibim/CheckedRelease.h>
#include <Bibim/Color.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/Math.h>
#include <Bibim/Matrix4.h>
#include <Bibim/Texture2D.h>

#if (defined(BIBIM_PLATFORM_WINDOWS))

    namespace Bibim
    {
        UIRenderer::Vertex::Vertex()
            : Position(0.0f, 0.0f, 0.0f),
              Color(D3DCOLOR_XRGB(255, 255, 255))
        {
        }

        UIRenderer::Vertex::Vertex(D3DXVECTOR3 position)
            : Position(position),
              Color(D3DCOLOR_XRGB(255, 255, 255))
        {
        }

        UIRenderer::Vertex::Vertex(D3DXVECTOR3 position, D3DCOLOR color)
            : Position(position),
              Color(color)
        {
        }

        UIRenderer::Vertex::Vertex(D3DXVECTOR3 position, D3DCOLOR color, D3DXVECTOR2 texture)
            : Position(position),
              Color(color),
              Texture(texture)
        {
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        UIRenderer::AlphaTexturedVertex::AlphaTexturedVertex()
            : Vertex()
        {
        }

        UIRenderer::AlphaTexturedVertex::AlphaTexturedVertex(D3DXVECTOR3 position)
            : Vertex(position)
        {
        }

        UIRenderer::AlphaTexturedVertex::AlphaTexturedVertex(D3DXVECTOR3 position, D3DCOLOR color)
            : Vertex(position, color)
        {
        }

        UIRenderer::AlphaTexturedVertex::AlphaTexturedVertex(D3DXVECTOR3 position, D3DCOLOR color, D3DXVECTOR2 texture, D3DXVECTOR2 alphaTexture)
            : Vertex(position, color, texture),
              AlphaTexture(alphaTexture)
        {
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        const unsigned short UIRenderer::TrianglesPerQuad = 2;
        const unsigned short UIRenderer::VerticesPerQuad  = 4;
        const unsigned short UIRenderer::IndicesPerQuad   = 6;

        UIRenderer::UIRenderer()
            : graphicsDevice(nullptr),
              fieldOfView(Math::PiOver4),
              vb(nullptr),
              ib(nullptr),
              numberOfActiveQuadSets(0),
              lastViewport(-1, -1, -1, -1)
        {
        }

        UIRenderer::UIRenderer(GraphicsDevice* graphicsDevice)
            : graphicsDevice(nullptr),
              fieldOfView(Math::PiOver4),
              vb(nullptr),
              ib(nullptr),
              numberOfActiveQuadSets(0),
              lastViewport(-1, -1, -1, -1)
        {
            SetGraphicsDevice(graphicsDevice);
        }

        UIRenderer::~UIRenderer()
        {
            CheckedRelease(vb);
            CheckedRelease(ib);
        }

        void UIRenderer::Begin()
        {
            struct SetParameter
            {
                UIRenderer* renderer;
                IDirect3DDevice9* d3dDevice;

                SetParameter(UIRenderer* renderer, IDirect3DDevice9* d3dDevice)
                    : renderer(renderer),
                      d3dDevice(d3dDevice)
                {
                }

                void RenderState(D3DRENDERSTATETYPE type, DWORD value, bool revertable)
                {
                    DWORD oldValue = 0;
                    d3dDevice->GetRenderState(type, &oldValue);

                    if (oldValue != value)
                    {
                        d3dDevice->SetRenderState(type, value);
                        if (revertable)
                            renderer->oldRenderStates.push_back(OldRenderState(type, oldValue));
                    }
                }
                void TextureStageState(DWORD stage, D3DTEXTURESTAGESTATETYPE type, DWORD value, bool revertable)
                {
                    DWORD oldValue = 0;
                    d3dDevice->GetTextureStageState(stage, type, &oldValue);

                    if (oldValue != value)
                    {
                        d3dDevice->SetTextureStageState(stage, type, value);
                        if (revertable)
                            renderer->oldTextureStageStates.push_back(OldTextureStageState(stage, type, oldValue));
                    }
                }
                void SetSamplerState(DWORD sampler, D3DSAMPLERSTATETYPE type, DWORD value, bool revertable)
                {
                    DWORD oldValue = 0;
                    d3dDevice->GetSamplerState(sampler, type, &oldValue);

                    if (oldValue != value)
                    {
                        d3dDevice->SetSamplerState(sampler, type, value);
                        if (revertable)
                            renderer->oldSamplerStates.push_back(OldSamplerState(sampler, type, oldValue));
                    }
                }
            };

            IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();

            D3DXMATRIX d3dIdentityMatrix;
            D3DXMatrixIdentity(&d3dIdentityMatrix);

            d3dDevice->SetTransform(D3DTS_VIEW, &d3dIdentityMatrix);
            d3dDevice->SetTransform(D3DTS_PROJECTION, &d3dIdentityMatrix);

            SetParameter set(this, d3dDevice);
            set.RenderState(D3DRS_ALPHABLENDENABLE, TRUE, false);
            set.RenderState(D3DRS_ALPHAFUNC, TRUE, false);
            set.RenderState(D3DRS_ALPHAREF, 0x00, false);
            set.RenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD, false);
            set.RenderState(D3DRS_CLIPPING, TRUE, false);
            set.RenderState(D3DRS_CULLMODE, D3DCULL_NONE, true);
            set.RenderState(D3DRS_CLIPPLANEENABLE, FALSE, false);
            set.RenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALPHA | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_RED, false);
            set.RenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA, false);
            set.RenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1, true);
            set.RenderState(D3DRS_ENABLEADAPTIVETESSELLATION, FALSE, true);
            set.RenderState(D3DRS_FILLMODE, D3DFILL_SOLID, false);
            set.RenderState(D3DRS_FOGENABLE, FALSE, true);
            set.RenderState(D3DRS_INDEXEDVERTEXBLENDENABLE, FALSE, true);
            set.RenderState(D3DRS_LIGHTING, FALSE, true);
            set.RenderState(D3DRS_RANGEFOGENABLE, FALSE, true);
            set.RenderState(D3DRS_SEPARATEALPHABLENDENABLE, FALSE, true);
            set.RenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD, false);
            set.RenderState(D3DRS_SPECULARENABLE, FALSE, true);
            set.RenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA, false);
            set.RenderState(D3DRS_SRGBWRITEENABLE, FALSE, false);
            set.RenderState(D3DRS_STENCILENABLE, FALSE, true);
            set.RenderState(D3DRS_VERTEXBLEND, FALSE, true);
            set.RenderState(D3DRS_WRAP0, 0, false);
            set.RenderState(D3DRS_SEPARATEALPHABLENDENABLE, FALSE, true);

            set.TextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE, false);
            set.TextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE, false);
            set.TextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE, false);
            set.TextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE, false);
            set.TextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE, false);
            set.TextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE, false);
            set.TextureStageState(0, D3DTSS_TEXCOORDINDEX, 0, false);
            set.TextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE, false);
            set.TextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE, false);
            set.TextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE, false);

            set.SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP, false);
            set.SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP, false);
            set.SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR, false);
            set.SetSamplerState(0, D3DSAMP_MAXMIPLEVEL, 0, false);
            set.SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR, false);
            set.SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR, false);
            set.SetSamplerState(0, D3DSAMP_MIPMAPLODBIAS, 0, false);
            set.SetSamplerState(0, D3DSAMP_SRGBTEXTURE, 0, false);

            d3dDevice->SetStreamSource(0, vb, 0, sizeof(Vertex));
            d3dDevice->SetIndices(ib);

            vb->Lock(0, vbSize, reinterpret_cast<void**>(&lockedVertices), D3DLOCK_DISCARD);
        }

        void UIRenderer::End()
        {
            Flush();

            IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();

            for (std::deque<OldSamplerState>::const_reverse_iterator it = oldSamplerStates.rbegin(); it != oldSamplerStates.rend(); it++)
                d3dDevice->SetSamplerState((*it).Sampler, (*it).Type, (*it).Value);                
                
            for (std::deque<OldTextureStageState>::const_reverse_iterator it = oldTextureStageStates.rbegin(); it != oldTextureStageStates.rend(); it++)
                d3dDevice->SetTextureStageState((*it).Stage, (*it).Type, (*it).Value);

            for (std::deque<OldRenderState>::const_reverse_iterator it = oldRenderStates.rbegin(); it != oldRenderStates.rend(); it++)
                d3dDevice->SetRenderState((*it).State, (*it).Value);

            oldSamplerStates.clear();
            oldTextureStageStates.clear();
            oldRenderStates.clear();
        }

        void UIRenderer::EnterStringRenderMode()
        {
            FlushAndLock();

            IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();
            d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
            d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
            d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
            d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
            d3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
            d3dDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);

            d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
            d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
            d3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
        }

        void UIRenderer::LeaveStringRenderMode()
        {
            IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();
            d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
            d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
            d3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

            d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
            d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
            d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
            d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
            d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
            d3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
            d3dDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);

            FlushAndLock();
        }

        void UIRenderer::Draw(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3, const RectangleF& clippingRectangle, Texture2D* texture, Color color)
        {
            const RectangleF bounds = RectangleF(Vector2(Math::Min(p0.X, p1.X, p2.X, p3.X), Math::Min(p0.Y, p1.Y, p2.Y, p3.Y)),
                                                 Vector2(Math::Max(p0.X, p1.X, p2.X, p3.X), Math::Max(p0.Y, p1.Y, p2.Y, p3.Y)));

            int quadSetIndex = numberOfActiveQuadSets;
            for (int i = 0; i < numberOfActiveQuadSets; i++)
            {
                if (cachedQuadSets[i].Texture == texture)
                {
                    quadSetIndex = i;

                    // 이미 용량이 꽉찼다면 Flush한다.
                    BBAssertDebug(cachedQuadSets[i].Count <= capacityPerQuad);
                    if (cachedQuadSets[i].Count == capacityPerQuad)
                        FlushAndLock();

                    break;
                }
                else
                {
                    if (cachedQuadSets[i].Bounds.Intersects(bounds))
                    {
                        FlushAndLock();
                        quadSetIndex = 0;
                        break;
                    }
                }
            }

            if (numberOfActiveQuadSets == quadSetIndex)
            {
                numberOfActiveQuadSets++;

                static const int MaximumCachedQuadSets = sizeof(cachedQuadSets) / sizeof(cachedQuadSets[0]);
                if (numberOfActiveQuadSets == MaximumCachedQuadSets)
                {
                    FlushAndLock();
                    quadSetIndex = 0;
                    numberOfActiveQuadSets = 1;
                }

                cachedQuadSets[quadSetIndex].Texture = texture;
                cachedQuadSets[quadSetIndex].Bounds = bounds;
            }
            else
                cachedQuadSets[quadSetIndex].Bounds = RectangleF::Union(cachedQuadSets[quadSetIndex].Bounds, bounds);

            QuadSet& quadSet = cachedQuadSets[quadSetIndex];

            BBAssertDebug(quadSet.Count < capacityPerQuad);

            const D3DCOLOR d3dColor = color.ToARGB();
            Vertex* localLockedVertices = &lockedVertices[quadSet.StartIndex + quadSet.Count * VerticesPerQuad];
            localLockedVertices[0] = Vertex(D3DXVECTOR3(p0.X, p0.Y, 0.0f), d3dColor, D3DXVECTOR2(clippingRectangle.GetLeft(),  clippingRectangle.GetTop()));
            localLockedVertices[1] = Vertex(D3DXVECTOR3(p1.X, p1.Y, 0.0f), d3dColor, D3DXVECTOR2(clippingRectangle.GetRight(), clippingRectangle.GetTop()));
            localLockedVertices[2] = Vertex(D3DXVECTOR3(p2.X, p2.Y, 0.0f), d3dColor, D3DXVECTOR2(clippingRectangle.GetLeft(),  clippingRectangle.GetBottom()));
            localLockedVertices[3] = Vertex(D3DXVECTOR3(p3.X, p3.Y, 0.0f), d3dColor, D3DXVECTOR2(clippingRectangle.GetRight(), clippingRectangle.GetBottom()));
            quadSet.Count++;
        }

        void UIRenderer::Draw(int count, const Vector2* points, Color color)
        {
        }

        void UIRenderer::SetGraphicsDevice(GraphicsDevice* value)
        {
            if (graphicsDevice != value)
            {
                graphicsDevice = value;
                ReserveCachedQuads(64);
            }
        }

        void UIRenderer::SetFieldOfView(float value)
        {
            value = Math::Clamp(value, 0.0001f, Math::Pi);

            if (fieldOfView != value)
            {
                fieldOfView = value;
                lastViewport = Rectangle(-1, -1, -1, -1);
            }
        }

        void UIRenderer::Flush()
        {
            if (numberOfActiveQuadSets == 0)
                return;

            if (lockedVertices)
            {
                lockedVertices = nullptr;
                vb->Unlock();
            }

            IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();

            for (int i = 0; i < numberOfActiveQuadSets; i++)
            {
                QuadSet& item = cachedQuadSets[i];

                if (cachedQuadSets[i].Count > 0)
                {
                    if (item.Texture)
                    {
                        d3dDevice->SetFVF(Vertex::FVF);
                        d3dDevice->SetTexture(0, item.Texture->GetD3DTexture());
                    }
                    else
                    {
                        d3dDevice->SetFVF(Vertex::NoTexturedFVF);
                        d3dDevice->SetTexture(0, nullptr);
                    }

                    d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, item.StartIndex, 0, item.Count * VerticesPerQuad, 0, item.Count * TrianglesPerQuad);
                    item.Texture.Reset();
                    item.Count = 0;
                }
            }

            numberOfActiveQuadSets = 0;
        }

        void UIRenderer::FlushAndLock()
        {
            Flush();

            vb->Lock(0, vbSize, reinterpret_cast<void**>(&lockedVertices), D3DLOCK_DISCARD);
        }

        void UIRenderer::ReserveCachedQuads(int capacity)
        {
            BBAssert(capacity >= 0);

            CheckedRelease(ib);
            CheckedRelease(vb);

            HRESULT result = D3D_OK;

            static const int MaximumQuadSets = sizeof(cachedQuadSets) / sizeof(cachedQuadSets[0]);

            const int totalCapacity = capacity * MaximumQuadSets;
            const int vbSize = sizeof(Vertex) * VerticesPerQuad * totalCapacity;
            const int ibSize = sizeof(WORD) * IndicesPerQuad * capacity;

            IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();

            result = d3dDevice->CreateVertexBuffer(vbSize, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, Vertex::FVF, D3DPOOL_DEFAULT, &vb, nullptr);
            result = d3dDevice->CreateIndexBuffer(ibSize, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &ib, nullptr);
            if (result == D3D_OK)
            {
                WORD* indices = nullptr;
                if (ib->Lock(0, ibSize, reinterpret_cast<void**>(&indices), 0) == D3D_OK)
                {
                    const int numberOfIndices = IndicesPerQuad * capacity;
                    for (WORD i = 0, v = 0; i < numberOfIndices; i += IndicesPerQuad, v += VerticesPerQuad)
                    {
                        indices[i + 0] = v + 0;
                        indices[i + 1] = v + 1;
                        indices[i + 2] = v + 2;
                        indices[i + 3] = v + 3;
                        indices[i + 4] = v + 2;
                        indices[i + 5] = v + 1;
                    }
                    ib->Unlock();
                }
            }

            const int sizePerQuadSet = VerticesPerQuad * capacity;
            for (int i = 0, vi = 0; i < MaximumQuadSets; i++, vi += sizePerQuadSet)
            {
                BBAssertDebug(cachedQuadSets[i].Count == 0); // ReserveCachedQuads 호출 전 Flush가 선행되어 Count는 반드시 0이어야합니다.
                cachedQuadSets[i].StartIndex = vi;
            }

            capacityPerQuad = capacity;
            this->vbSize = vbSize;
        }
        
        void UIRenderer::UpdateViewProjectionTransform()
        {
            if (graphicsDevice == nullptr)
            {
                viewTransform = Matrix4::Identity;
                viewTransformInv = Matrix4::Identity;
                projectionTransform = Matrix4::Identity;
                projectionTransformInv = Matrix4::Identity;
                return;
            }

            const Rectangle currentViewport = graphicsDevice->GetViewport();
            if (currentViewport != lastViewport)
            {
                const D3DXVECTOR2 viewportSize = D3DXVECTOR2(static_cast<float>(currentViewport.Width), static_cast<float>(currentViewport.Height));
                const D3DXVECTOR2 halfViewportSize = D3DXVECTOR2(viewportSize.x * 0.5f, viewportSize.y * 0.5f);
                const float aspect = viewportSize.x / viewportSize.y;

                D3DXMATRIX d3dViewTransform;
                D3DXMATRIX d3dProjectionTransform;

                const float distance = Math::Tan(Math::PiOver2 - (fieldOfView * 0.5f)) * halfViewportSize.x / aspect;
                const D3DXVECTOR3 eye = D3DXVECTOR3(halfViewportSize.x, halfViewportSize.y, -distance);
                const D3DXVECTOR3 at = D3DXVECTOR3(halfViewportSize.x, halfViewportSize.y, 0.0f);
                const D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
                D3DXMatrixLookAtLH(&d3dViewTransform, &eye, &at, &up);
                D3DXMATRIX t;
                D3DXMATRIX r;
                D3DXMatrixTranslation(&t, 0.0f, -viewportSize.y, 0.0f);
                D3DXMatrixRotationX(&r, Math::Pi);
                D3DXMATRIX viewResult;
                D3DXMatrixMultiply(&d3dViewTransform, &r, &d3dViewTransform);
                D3DXMatrixMultiply(&d3dViewTransform, &t, &d3dViewTransform);

                D3DXMatrixPerspectiveFovLH(&d3dProjectionTransform, fieldOfView, aspect, 0.1f, 10000.0f);

                D3DXMATRIX d3dViewTransformInv;
                D3DXMATRIX d3dProjectionTransformInv;
                D3DXMatrixInverse(&d3dViewTransformInv, nullptr, &d3dViewTransform);
                D3DXMatrixInverse(&d3dProjectionTransformInv, nullptr, &d3dProjectionTransform);

                viewTransform = Matrix4(d3dViewTransform);
                viewTransformInv = Matrix4(d3dViewTransformInv);
                projectionTransform = Matrix4(d3dProjectionTransform);
                projectionTransformInv = Matrix4(d3dProjectionTransformInv);

                lastViewport = currentViewport;
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        UIRenderer::QuadSet::QuadSet()
            : Count(0),
              StartIndex(0),
              Texture(),
              Effect(nullptr)
        {
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        UIRenderer::OldRenderState::OldRenderState(D3DRENDERSTATETYPE state, DWORD value)
            : State(state), Value(value)
        {
        }

        UIRenderer::OldTextureStageState::OldTextureStageState(DWORD stage, D3DTEXTURESTAGESTATETYPE type, DWORD value)
            : Stage(stage), Type(type), Value(value)
        {
        }

        UIRenderer::OldSamplerState::OldSamplerState(DWORD sampler, D3DSAMPLERSTATETYPE type, DWORD value)
            : Sampler(sampler), Type(type), Value(value)
        {
        }
    }

#endif