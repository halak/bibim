// Automatically generated in 2014-01-23 18:18:22.864000

#include <zlib.h>
#include "Animation/Ease.cpp"
#include "Animation/EasingCurves.cpp"
#include "Animation/ElasticEasingCurves.cpp"
#include "Animation/EvalBoard.cpp"
#include "Animation/EvalConstants.cpp"
#include "Animation/EvalContext.cpp"
#include "Animation/Evals.cpp"
#include "Animation/EvalTimeflow.cpp"
#include "Animation/EvalUnitRandom.cpp"
#include "Animation/OscillationCurve.cpp"
#include "Animation/Sprite.cpp"
#include "Animation/SpriteSet.cpp"
#include "Asset/AssetLoadingTask.cpp"
#include "Asset/AssetProvider.cpp"
#include "Asset/AssetStreamReader.cpp"
#include "Asset/FileAssetProvider.Default.cpp"
#include "Asset/FileAssetProviderBase.cpp"
#include "Asset/GameAsset.cpp"
#include "Asset/GameAssetFactory.cpp"
#include "Asset/GameAssetStorage.cpp"
#include "Asset/MPQAssetProvider.cpp"
#include "Asset/NetworkAssetProvider.cpp"
#include "Audio/AudioDevice.Android.cpp"
#include "Audio/AudioDevice.Emscripten.cpp"
#include "Audio/AudioDevice.iOS.cpp"
#include "Audio/AudioDevice.PC.cpp"
#include "Audio/BGM.Android.cpp"
#include "Audio/BGM.Emscripten.cpp"
#include "Audio/BGM.iOS.cpp"
#include "Audio/BGM.PC.cpp"
#include "Audio/SoundFX.Android.cpp"
#include "Audio/SoundFX.Emscripten.cpp"
#include "Audio/SoundFX.iOS.cpp"
#include "Audio/SoundFX.PC.cpp"
#include "Collision2D/AxisAlignedBoxShape2D.cpp"
#include "Collision2D/BoxShape2D.cpp"
#include "Collision2D/CollisionSpace2D.cpp"
#include "Collision2D/IntersectShapes2D.cpp"
#include "Collision2D/PointShape2D.cpp"
#include "Collision2D/SegmentShape2D.cpp"
#include "Collision2D/Shape2D.cpp"
#include "Collision2D/SphereShape2D.cpp"
#include "Collision2D/UserShape2D.cpp"
#include "Component/CloningContext.cpp"
#include "Component/ComponentStreamReader.cpp"
#include "Component/GameComponent.cpp"
#include "Component/GameComponentFactory.cpp"
#include "Diagnostics/CrashDump.cpp"
#include "Diagnostics/Log.cpp"
#include "Diagnostics/Logger.cpp"
#include "Diagnostics/Performance.cpp"
#include "Diagnostics/Statistics.cpp"
#include "Diagnostics/SystemLogger.cpp"
#include "FileSystem/FileStream.Android.cpp"
#include "FileSystem/FileStream.Emscripten.cpp"
#include "FileSystem/FileStream.iOS.cpp"
#include "FileSystem/FileStream.Windows.cpp"
#include "FileSystem/MPQ.cpp"
#include "FileSystem/MPQStream.cpp"
#include "FileSystem/Path.cpp"
#include "Foundation/Any.cpp"
#include "Foundation/AnyStorage.cpp"
#include "Foundation/ClassHierarchy.cpp"
#include "Foundation/ClassInfo.cpp"
#include "Foundation/Color.cpp"
#include "Foundation/Environment.Android.cpp"
#include "Foundation/Environment.Emscripten.cpp"
#include "Foundation/Environment.iOS.cpp"
#include "Foundation/Environment.Windows.cpp"
#include "Foundation/Geom2D.cpp"
#include "Foundation/Math.cpp"
#include "Foundation/Matrix4.cpp"
#include "Foundation/Memory.cpp"
#include "Foundation/Numerics.cpp"
#include "Foundation/Object.cpp"
#include "Foundation/Point2.cpp"
#include "Foundation/Point3.cpp"
#include "Foundation/Point4.cpp"
#include "Foundation/Random.cpp"
#include "Foundation/Rect.cpp"
#include "Foundation/RectF.cpp"
#include "Foundation/RectStorage.cpp"
#include "Foundation/SequenceDictionary.cpp"
#include "Foundation/SharedObject.cpp"
#include "Foundation/String.cpp"
#include "Foundation/Vector2.cpp"
#include "Foundation/Vector3.cpp"
#include "Foundation/Vector4.cpp"
#include "Framework/Clipboard.Android.cpp"
#include "Framework/Clipboard.Emscripten.cpp"
#include "Framework/Clipboard.iOS.cpp"
#include "Framework/Clipboard.Windows.cpp"
#include "Framework/Dashboard.cpp"
#include "Framework/GameFramework.Android.cpp"
#include "Framework/GameFramework.Emscripten.cpp"
#include "Framework/GameFramework.iOS.cpp"
#include "Framework/GameFramework.Windows.cpp"
#include "Framework/GameFrameworkBase.cpp"
#include "Framework/GameWindow.Mobile.cpp"
#include "Framework/GameWindow.Windows.cpp"
#include "Framework/Lua.cpp"
#include "Framework/Preferences.cpp"
#include "Framework/StandardGame.cpp"
#include "Framework/Startup.cpp"
#include "Gameplay/BatchCommand.cpp"
#include "Gameplay/Command.cpp"
#include "Gameplay/CommandHistory.cpp"
#include "Gameplay/CommandQueue.cpp"
#include "Gameplay/JumpPointPathFinder.cpp"
#include "Gameplay/PathFinder.cpp"
#include "Gameplay/RestorableCommand.cpp"
#include "Gameplay/SpatialObject2D.cpp"
#include "GFX/CCParticleEmitter.cpp"
#include "GFX/CCParticleSystem.cpp"
#include "GFX/CCParticleSystemSet.cpp"
#include "GFX/Spark.cpp"
#include "GFX/SparkParticleEngine.cpp"
#include "GFX/SparkSet.cpp"
#include "Graphics/BitMask.cpp"
#include "Graphics/DynamicTexture2D.DX9.cpp"
#include "Graphics/DynamicTexture2D.GLES2.cpp"
#include "Graphics/GLES2.cpp"
#include "Graphics/GraphicsCapabilities.cpp"
#include "Graphics/GraphicsDevice.DX9.cpp"
#include "Graphics/GraphicsDevice.GLES2.cpp"
#include "Graphics/GraphicsDeviceBase.cpp"
#include "Graphics/Image.cpp"
#include "Graphics/ImageSet.cpp"
#include "Graphics/JPEG.cpp"
#include "Graphics/PNG.cpp"
#include "Graphics/RenderTargetTexture2D.DX9.cpp"
#include "Graphics/RenderTargetTexture2D.GLES2.cpp"
#include "Graphics/ScreenshotPrinter.cpp"
#include "Graphics/ShaderEffect.DX9.cpp"
#include "Graphics/ShaderEffect.GLES2.cpp"
#include "Graphics/SourceTexture2D.DX9.cpp"
#include "Graphics/SourceTexture2D.GLES2.cpp"
#include "Graphics/Texture2D.DX9.cpp"
#include "Graphics/Texture2D.GLES2.cpp"
#include "Graphics/Window.cpp"
#include "Input/IME.Mobile.cpp"
#include "Input/IME.Windows.cpp"
#include "Input/IMEBase.cpp"
#include "Input/Key.cpp"
#include "Input/Keyboard.cpp"
#include "Input/KeyboardState.cpp"
#include "Input/Mouse.cpp"
#include "Input/Mouse.Mobile.cpp"
#include "Input/Mouse.Windows.cpp"
#include "Input/MouseState.cpp"
#include "Module/GameModule.cpp"
#include "Module/GameModuleFactory.cpp"
#include "Module/GameModuleNode.cpp"
#include "Module/GameModuleTree.cpp"
#include "Net/HttpClient.Curl.cpp"
#include "Net/HttpClient.Emscripten.cpp"
#include "Net/HttpClientBase.cpp"
#include "Net/IPEndPoint.cpp"
#include "Net/NetworkStream.cpp"
#include "Net/Socket.Default.cpp"
#include "Scripting/Script.cpp"
#include "Scripting/ScriptingContext.cpp"
#include "Scripting/ScriptNativeFunctionTable.cpp"
#include "Scripting/ScriptStack.cpp"
#include "Scripting/ScriptThread.cpp"
#include "Threading/Lock.Unix.cpp"
#include "Threading/Lock.Windows.cpp"
#include "Threading/ManualLocker.cpp"
#include "Threading/Thread.Unix.cpp"
#include "Threading/Thread.Windows.cpp"
#include "Time/AlarmClock.cpp"
#include "Time/Clock.Unix.cpp"
#include "Time/Clock.Windows.cpp"
#include "Time/SubTimeline.cpp"
#include "Time/Timeline.cpp"
#include "Time/TimelineGameComponent.cpp"
#include "Time/TimelineGameModule.cpp"
#include "Time/UpdateableGameComponent.cpp"
#include "Time/UpdateableGameModule.cpp"
#include "Typography/Font.cpp"
#include "Typography/FontCache.cpp"
#include "Typography/FontFace.cpp"
#include "Typography/FontLibrary.cpp"
#include "Typography/FontString.cpp"
#include "Typography/Glyph.cpp"
#include "Typography/GlyphSurface.cpp"
#include "Typography/GlyphTable.cpp"
#include "Typography/TypingContext.cpp"
#include "UI/UIAfterImageEffect.cpp"
#include "UI/UIAppEventDispatcher.cpp"
#include "UI/UIAsyncEventQueue.cpp"
#include "UI/UIBlendingEffect.cpp"
#include "UI/UIBoundsContext.cpp"
#include "UI/UIButton.cpp"
#include "UI/UICCParticleSystem.cpp"
#include "UI/UICheckBox.cpp"
#include "UI/UIColorMatrixEffect.cpp"
#include "UI/UIDebugDrawMixin.cpp"
#include "UI/UIDocument.cpp"
#include "UI/UIDomain.cpp"
#include "UI/UIDrawingContext.cpp"
#include "UI/UIEditText.cpp"
#include "UI/UIEffectMap.cpp"
#include "UI/UIEffectStack.cpp"
#include "UI/UIElement.cpp"
#include "UI/UIEllipse.cpp"
#include "UI/UIEventArgs.cpp"
#include "UI/UIEventDispatcher.cpp"
#include "UI/UIEventHandler.cpp"
#include "UI/UIEventID.cpp"
#include "UI/UIEventMap.cpp"
#include "UI/UIForceGridEffect.cpp"
#include "UI/UIFunctionEventHandler.cpp"
#include "UI/UIFunctionTable.cpp"
#include "UI/UIGamePadEventArgs.cpp"
#include "UI/UIGamePadEventDispatcher.cpp"
#include "UI/UIGeometryEffect.cpp"
#include "UI/UIHandledDrawingContext.cpp"
#include "UI/UIImage.cpp"
#include "UI/UIInverseTransform.cpp"
#include "UI/UIKeyboardEventArgs.cpp"
#include "UI/UIKeyboardEventDispatcher.cpp"
#include "UI/UILabel.cpp"
#include "UI/UILayout.cpp"
#include "UI/UILiveWindow.cpp"
#include "UI/UIMaskEffect.cpp"
#include "UI/UIMouseButtonEventArgs.cpp"
#include "UI/UIMouseEventArgs.cpp"
#include "UI/UIMouseEventDispatcher.cpp"
#include "UI/UIMouseWheelEventArgs.cpp"
#include "UI/UIOpacityMaskEffect.cpp"
#include "UI/UIPanel.cpp"
#include "UI/UIPickingContext.cpp"
#include "UI/UIPixelEffect.cpp"
#include "UI/UIRadioButton.cpp"
#include "UI/UIRect.cpp"
#include "UI/UIRenderer.DX9.cpp"
#include "UI/UIRenderer.GLES2.cpp"
#include "UI/UIRendererBase.cpp"
#include "UI/UIRoundedRect.cpp"
#include "UI/UIScrollablePanel.cpp"
#include "UI/UISequentialEventHandler.cpp"
#include "UI/UIShape.cpp"
#include "UI/UISimpleDomain.cpp"
#include "UI/UISineCurveEffect.cpp"
#include "UI/UISpark.cpp"
#include "UI/UISprite.cpp"
#include "UI/UITintEffect.cpp"
#include "UI/UITrail.cpp"
#include "UI/UITransform.cpp"
#include "UI/UITransform2D.cpp"
#include "UI/UITransform3D.cpp"
#include "UI/UIVideo.cpp"
#include "UI/UIVisual.cpp"
#include "UI/UIVisualVisitor.cpp"
#include "UI/UIWindow.cpp"