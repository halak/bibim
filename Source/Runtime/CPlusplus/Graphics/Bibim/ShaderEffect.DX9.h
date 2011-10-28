#pragma once
#ifndef __BIBIM_SHADEREFFECT_DX9_H__
#define __BIBIM_SHADEREFFECT_DX9_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameAsset.h>
#   include <d3dx9.h>

    namespace Bibim
    {
        class ShaderEffect : public GameAsset
        {
            BBSerializableAssetClass(ShaderEffect, GameAsset, 'S', 'H', 'E', 'F');
            public:
                ShaderEffect(GraphicsDevice* graphicsDevice);
                virtual ~ShaderEffect();

            private:
                GraphicsDevice* graphicsDevice;
                ID3DXEffect* d3dEffect;
        };
    }

#   include <Bibim/ShaderEffect.DX9.inl>

#endif