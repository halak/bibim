using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using Bibim.Asset.Pipeline.Recipes;
using Bibim.Json.Serialization;

namespace Bibim.Asset.Pipeline
{
	public sealed partial class GameAssetKitchen
	{
        private List<string> extensionPriorities;
        private Dictionary<string, GameAssetRecipe> builtinRecipes;

        private GameAssetRecipe FindBuiltinRecipe(string path)
        {
            string firstExtension = GuessFirstExtension(path);

            GameAssetRecipe recipe = null;
            if (builtinRecipes.TryGetValue(firstExtension, out recipe))
                return recipe;
            else
                return null;
        }

        private GameAssetRecipe CreateBuiltinRecipe(string path, Dictionary<string, object> data)
        {
            string firstExtension = GuessFirstExtension(path).ToLower();
            string usage = (data.Get<string>("usage") ?? string.Empty).ToLower();
            switch (usage)
            {
                case "ui":
                    return CreatePSDToUIRecipe(data.Get<string>("source") ?? "$(AssetName).psd",
                                               data.Get<double>("scale", 1.0));
                case "texture":
                    if (firstExtension == "psd")
                        return CreatePSDTextureRecipe();
                    else
                        return CreateTextureRecipe();
                case "backgroundtexture":
                    if (firstExtension == "psd")
                        return CreatePSDTextureRecipe(true);
                    else
                        return CreateTextureRecipe(true);
                case "masktexture":
                    if (firstExtension == "psd")
                        return CreatePSDMaskTextureRecipe();
                    else
                        return CreateMaskTextureRecipe();
                case "dirimageset":
                    return CreateDirectoryImageSetRecipe(data.Get<string>("source") ?? "$(AssetName)",
                                                         data.Get("uniformSize", System.Drawing.Size.Empty));
                case "dirspriteset":
                    return CreateDirectorySpriteSetRecipe(data.Get<string>("source") ?? "$(AssetName)");
                case "imageset":
                    return CreatePSDImageSetRecipe(data.Get<string>("source") ?? "$(AssetName).psd");
                case "spriteset":
                    return CreatePSDSpriteSetRecipe(data.Get<string>("source") ?? "$(AssetName).psd");
                case "sparkset":
                    return CreateSparkSetRecipe(data.Get<string>("source") ?? "$(AssetName).eff");
                case "dirparticle":
                    return CreateDirectoryParticleSystemSetRecipe(data.Get<string>("source") ?? "$(AssetName)");
                case "hlsl":
                    return CreateCompileHLSLShaderEffect(
                        data.Get<string>("base") ?? "UI.fx",
                        data.Get<string>("defines") ?? string.Empty
                    );
                case "glsl":
                    return CreateCompileGLSLShaderEffect(
                        data.Get<string>("base") ?? "UI.glsl",
                        data.Get<string>("defines") ?? string.Empty
                    );
                case "lua":
                    return CreateLuaRecipe(data.Get<string>("source") ?? "$(AssetName).lua");
                case "hex":
                    return CreateHexRecipe(data.Get<string>("data") ?? string.Empty);
            }

            string read = data.Get<string>("read");
            if (string.IsNullOrEmpty(read) == false)
                return CreateReadRecipe(read);

            return null;
        }

        private string GuessFirstExtension(string path)
        {
            List<string> extensions = new List<string>();

            string directory = Path.GetDirectoryName(path);
            string searchPattern = string.Format("{0}.*", Path.GetFileNameWithoutExtension(path));
            foreach (var item in Directory.GetFiles(directory, searchPattern, SearchOption.TopDirectoryOnly))
            {
                extensions.Add(Path.GetExtension(item).Substring(1).ToLower());
            }

            if (extensions.Count == 0)
                return null;

            extensions.Sort(CompareByPriority);
            return extensions[0];
        }

        private void LoadBuiltinRecipes()
        {
            extensionPriorities = new List<string>()
            {
                "png", "jpg", "psd", "lua", "ttf", "eff",
            };

            builtinRecipes = new Dictionary<string, GameAssetRecipe>()
            {
                { "lua", CreateLuaRecipe() },
                { "ttf", CreateStreamingAssetRecipe("ttf") },
                { "png", CreateTextureRecipe() },
                { "jpg", CreateTextureRecipe(true) },
                { "psd", CreatePSDToUIRecipe() },
                { "eff", CreateSparkSetRecipe() },
            };
        }

        private int CompareByPriority(string a, string b)
        {
            int ap = extensionPriorities.IndexOf(a);
            int bp = extensionPriorities.IndexOf(b);
            if (ap == -1)
                ap = extensionPriorities.Count;
            if (bp == -1)
                bp = extensionPriorities.Count;
            return ap.CompareTo(bp);
        }

        private static GameAssetRecipe CreateLuaRecipe(string source = "$(AssetName).lua")
        {
            return Wrap(new CompileLuaScript(source));
        }

        private static GameAssetRecipe CreateStreamingAssetRecipe(string extension)
        {
            return Wrap(new LoadStreamingAsset(string.Format("$(AssetName).{0}", extension)));
        }

        private static GameAssetRecipe CreateHexRecipe(string data)
        {
            return Wrap(new CompileHexData(data));
        }

        private static GameAssetRecipe CreateTextureRecipe(bool forceOpaque = false)
        {
            return Wrap(new BitmapToTexture2D()
            {
                Input = new ImportBitmap()
                {
                    Input = new FileToStream("$(AssetName).png", "$(AssetName).jpg", "$(AssetName).bmp")
                },
            });
        }

        private static GameAssetRecipe CreatePSDTextureRecipe(bool forceOpaque = false)
        {
            return Wrap(new BitmapToTexture2D()
            {
                Input = new PhotoshopDocumentToBitmap()
                {
                    Input = new ImportPhotoshopDocument()
                    {
                        Input = new FileToStream()
                        {
                            Input1 = "$(AssetName).psd"
                        },
                        IgnoreImageResources = true,
                        IgnoreLayers = true,
                        IgnoreMergedBitmap = false,
                        Scale = 1.0,
                    },
                },
                ForceOpaque = forceOpaque,
            });
        }

        private static GameAssetRecipe CreateMaskTextureRecipe()
        {
            return Wrap(new BitmapToMaskTexture2D()
            {
                Input = new ImportBitmap()
                {
                    Input = new FileToStream("$(AssetName).png", "$(AssetName).jpg", "$(AssetName).bmp")
                },
            });
        }

        private static GameAssetRecipe CreatePSDMaskTextureRecipe()
        {
            return Wrap(new BitmapToMaskTexture2D()
            {
                Input = new PhotoshopDocumentToBitmap()
                {
                    Input = new ImportPhotoshopDocument()
                    {
                        Input = new FileToStream()
                        {
                            Input1 = "$(AssetName).psd"
                        },
                        IgnoreImageResources = true,
                        IgnoreLayers = true,
                        IgnoreMergedBitmap = false,
                        Scale = 1.0,
                    },
                },
            });
        }

        private static GameAssetRecipe CreatePSDToUIRecipe(string source = "$(AssetName).psd", double scale = 1.0)
        {
            return Wrap(new ExportUILayoutAssets()
            {
                Input = new PhotoshopDocumentToUILayout1()
                {
                    Input = new ImportPhotoshopDocument()
                    {
                        Input = new FileToStream()
                        {
                            Input1 = source,
                        },
                        IgnoreImageResources = false,
                        IgnoreLayers = false,
                        IgnoreMergedBitmap = true,
                        Scale = scale,
                    },
                    ForceShowAll = true,
                },
                BitmapSheetSize = new System.Drawing.Size(1024, 1024),
                BitmapSheetClusterSize = new System.Drawing.Size(16, 16),
                TextureOutput = "gen\\$(AssetName)_TEXTURE{0}",
                ImageOutput = "gen\\$(AssetName)_IMG{0}",
                MaskOutput = "gen\\$(AssetName)_MASK{0}",
            });
        }

        private static GameAssetRecipe CreateDirectoryImageSetRecipe(string input, System.Drawing.Size uniformSize)
        {
            return Wrap(new ExportImageSet()
            {
                Input = new DirectoryToImageSet()
                {
                    Input = input,
                    UniformSize = uniformSize,
                },
                BitmapSheetSize = new System.Drawing.Size(1024, 1024),
                BitmapSheetClusterSize = new System.Drawing.Size(16, 16),
                TextureOutput = "gen\\$(AssetName)_TEXTURE{0}",
            });
        }

        private static GameAssetRecipe CreateDirectorySpriteSetRecipe(string input)
        {
            return Wrap(new ExportSpriteSet()
            {
                Input = new DirectoryToSpriteSet()
                {
                    Input = input,
                },
                BitmapSheetSize = new System.Drawing.Size(1024, 1024),
                BitmapSheetClusterSize = new System.Drawing.Size(16, 16),
                TextureOutput = "gen\\$(AssetName)_TEXTURE{0}",
            });
        }

        private static GameAssetRecipe CreateDirectoryParticleSystemSetRecipe(string input)
        {
            return Wrap(new ExportParticleSystemSet()
            {
                Input = new DirectoryToParticleSystemSet()
                {
                    Input = input,
                },
                BitmapSheetSize = new System.Drawing.Size(1024, 1024),
                BitmapSheetClusterSize = new System.Drawing.Size(16, 16),
                TextureOutput = "gen\\$(AssetName)_TEXTURE{0}",
            });
        }

        private static GameAssetRecipe CreatePSDImageSetRecipe(string input)
        {
            return Wrap(new ExportImageSet()
            {
                Input = new PhotoshopDocumentToImageSet()
                {
                    Input = new ImportPhotoshopDocument()
                    {
                        Input = new FileToStream()
                        {
                            Input1 = input,
                        },
                        IgnoreImageResources = false,
                        IgnoreLayers = false,
                        IgnoreMergedBitmap = true,
                    },
                },
                BitmapSheetSize = new System.Drawing.Size(1024, 1024),
                BitmapSheetClusterSize = new System.Drawing.Size(16, 16),
                TextureOutput = "gen\\$(AssetName)_TEXTURE{0}",
            });
        }

        private static GameAssetRecipe CreatePSDSpriteSetRecipe(string input)
        {
            return Wrap(new ExportSpriteSet()
            {
                Input = new PhotoshopDocumentToSpriteSet()
                {
                    Input = new ImportPhotoshopDocument()
                    {
                        Input = new FileToStream()
                        {
                            Input1 = input,
                        },
                        IgnoreImageResources = false,
                        IgnoreLayers = false,
                        IgnoreMergedBitmap = true,
                    },
                },
                BitmapSheetSize = new System.Drawing.Size(1024, 1024),
                BitmapSheetClusterSize = new System.Drawing.Size(16, 16),
                TextureOutput = "gen\\$(AssetName)_TEXTURE{0}",
            });
        }

        private static GameAssetRecipe CreateSparkSetRecipe(string source = "$(AssetName).eff")
        {
            return Wrap(new ExportSparkSet()
            {
                Input = new ImportTimelineFX()
                {
                    Input = source
                },
                BitmapSheetSize = new System.Drawing.Size(1024, 1024),
                BitmapSheetClusterSize = new System.Drawing.Size(16, 16),
                TextureOutput = "gen\\$(AssetName)_TEXTURE{0}",
            });
        }

        private static GameAssetRecipe CreateCompileHLSLShaderEffect(string input, string defines)
        {
            return Wrap(new CompileHLSLShaderEffect()
            {
                Input = input,
                Defines = defines,
            });
        }

        private static GameAssetRecipe CreateCompileGLSLShaderEffect(string input, string defines)
        {
            return Wrap(new CompileGLSLShaderEffect()
            {
                Input = input,
                Defines = defines,
            });
        }

        private static GameAssetRecipe CreateReadRecipe(string input)
        {
            return Wrap(new ReadRecipe(input));
        }

        private static GameAssetRecipe Wrap(CookingNode cookingNode)
        {
            return new GameAssetRecipe()
            {
                Cook = cookingNode,
                Author = "Halak",
                Comment = "",
                CanHotload = false,
            };
        }
	}
}
