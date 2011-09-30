#pragma once
#ifndef __BIBIM_3A9684E8_86AC_4A8B_ADE5_834BD783EA8E_ALL_H__
#define __BIBIM_3A9684E8_86AC_4A8B_ADE5_834BD783EA8E_ALL_H__

   // This file was "AUTOMATICALLY GENERATED" by Bibim Console (9/26/2011 3:03:01 PM)
   // > Halak.Bibim.Toolkit.Console.exe CppHeaderGenerator full [Library-Name] [Source-Directory] [Header-File]


   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Asset
#  include <Bibim/AssetLoadingTask.h>
#  include <Bibim/AssetProvider.h>
#  include <Bibim/AssetStreamReader.h>
#  include <Bibim/FileAssetProvider.h>
#  include <Bibim/GameAsset.h>
#  include <Bibim/GameAssetFactory.h>
#  include <Bibim/GameAssetStorage.h>
#  include <Bibim/PipedAssetProvider.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // FileSystem
#  include <Bibim/FileStream.h>
#  include <Bibim/FileStream.Windows.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Foundation
#  include <Bibim/All.h>
#  include <Bibim/Any.h>
#  include <Bibim/Assert.h>
#  include <Bibim/BinaryReader.h>
#  include <Bibim/BinaryWriter.h>
#  include <Bibim/CheckedRelease.h>
#  include <Bibim/Color.h>
#  include <Bibim/Colors.h>
#  include <Bibim/Delete.h>
#  include <Bibim/Environment.h>
#  include <Bibim/Environment.Windows.h>
#  include <Bibim/Exception.h>
#  include <Bibim/Foundation.h>
#  include <Bibim/FWD.h>
#  include <Bibim/Geom2D.h>
#  include <Bibim/Math.h>
#  include <Bibim/Matrix4.h>
#  include <Bibim/MemoryStream.h>
#  include <Bibim/NullPointer.h>
#  include <Bibim/Numerics.h>
#  include <Bibim/PCH.h>
#  include <Bibim/Point.h>
#  include <Bibim/PointerCasts.h>
#  include <Bibim/Property.h>
#  include <Bibim/Quaternion.h>
#  include <Bibim/Range.h>
#  include <Bibim/Rect.h>
#  include <Bibim/RectF.h>
#  include <Bibim/RectStorage.h>
#  include <Bibim/SequenceDictionary.h>
#  include <Bibim/SharedObject.h>
#  include <Bibim/SharedPointer.h>
#  include <Bibim/Stream.h>
#  include <Bibim/String.h>
#  include <Bibim/URI.h>
#  include <Bibim/UUID.h>
#  include <Bibim/Vector2.h>
#  include <Bibim/Vector3.h>
#  include <Bibim/Vector4.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Framework
#  include <Bibim/GameFramework.h>
#  include <Bibim/GameFramework.Windows.h>
#  include <Bibim/GameWindow.h>
#  include <Bibim/GameWindow.Windows.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Gameplay
#  include <Bibim/BatchCommand.h>
#  include <Bibim/Command.h>
#  include <Bibim/CommandHistory.h>
#  include <Bibim/CommandQueue.h>
#  include <Bibim/RestorableCommand.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Graphics
#  include <Bibim/DisplaySwapChain.h>
#  include <Bibim/DynamicTexture2D.h>
#  include <Bibim/GraphicsDevice.h>
#  include <Bibim/SourceTexture2D.h>
#  include <Bibim/Texture2D.h>
#  include <Bibim/Window.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Input
#  include <Bibim/Key.h>
#  include <Bibim/Keyboard.h>
#  include <Bibim/KeyboardState.h>
#  include <Bibim/Mouse.h>
#  include <Bibim/MouseState.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // IPC
#  include <Bibim/PipeClientStream.h>
#  include <Bibim/PipeClientStream.Windows.h>
#  include <Bibim/PipeServerStream.h>
#  include <Bibim/PipeServerStream.Windows.h>
#  include <Bibim/PipeStream.h>
#  include <Bibim/PipeStream.Windows.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Module
#  include <Bibim/GameModule.h>
#  include <Bibim/GameModuleFactory.h>
#  include <Bibim/GameModuleNode.h>
#  include <Bibim/GameModuleTree.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Startup
#  include <Bibim/Startup.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Threading
#  include <Bibim/Atomic.h>
#  include <Bibim/Atomic.Windows.h>
#  include <Bibim/AutoLocker.h>
#  include <Bibim/Lock.h>
#  include <Bibim/Lock.Windows.h>
#  include <Bibim/ManualLocker.h>
#  include <Bibim/Thread.h>
#  include <Bibim/Thread.Windows.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Time
#  include <Bibim/Clock.h>
#  include <Bibim/SubTimeline.h>
#  include <Bibim/Timeline.h>
#  include <Bibim/TimelineGameModule.h>
#  include <Bibim/UpdateableGameModule.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Typography
#  include <Bibim/Font.h>
#  include <Bibim/FontCache.h>
#  include <Bibim/FontLibrary.h>
#  include <Bibim/FontString.h>
#  include <Bibim/Glyph.h>
#  include <Bibim/GlyphSurface.h>
#  include <Bibim/GlyphTable.h>
#  include <Bibim/TypingContext.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // UI
#  include <Bibim/UI.h>
#  include <Bibim/UIAlignedFrame.h>
#  include <Bibim/UIAnchoredFrame.h>
#  include <Bibim/UIAppEventDispatcher.h>
#  include <Bibim/UIAsyncEventQueue.h>
#  include <Bibim/UIButton.h>
#  include <Bibim/UICheckBox.h>
#  include <Bibim/UIDomain.h>
#  include <Bibim/UIDrawingContext.h>
#  include <Bibim/UIEffect.h>
#  include <Bibim/UIEffectMap.h>
#  include <Bibim/UIElement.h>
#  include <Bibim/UIElementFactory.h>
#  include <Bibim/UIEventArgs.h>
#  include <Bibim/UIEventDispatcher.h>
#  include <Bibim/UIEventHandler.h>
#  include <Bibim/UIEventID.h>
#  include <Bibim/UIEventMap.h>
#  include <Bibim/UIFittedFrame.h>
#  include <Bibim/UIFixedFrame.h>
#  include <Bibim/UIFrame.h>
#  include <Bibim/UIFunctionEventHandler.h>
#  include <Bibim/UIFunctionTable.h>
#  include <Bibim/UIGamePadEventArgs.h>
#  include <Bibim/UIGamePadEventDispatcher.h>
#  include <Bibim/UIHandledDrawingContext.h>
#  include <Bibim/UIImage.h>
#  include <Bibim/UIKeyboardEventArgs.h>
#  include <Bibim/UIKeyboardEventDispatcher.h>
#  include <Bibim/UILabel.h>
#  include <Bibim/UILayout.h>
#  include <Bibim/UIMarkupText.h>
#  include <Bibim/UIMarkupTextBox.h>
#  include <Bibim/UIMouseButtonEventArgs.h>
#  include <Bibim/UIMouseEventArgs.h>
#  include <Bibim/UIMouseEventDispatcher.h>
#  include <Bibim/UIMouseWheelEventArgs.h>
#  include <Bibim/UIPanel.h>
#  include <Bibim/UIPickingContext.h>
#  include <Bibim/UIRenderer.h>
#  include <Bibim/UIRenderer.Windows.h>
#  include <Bibim/UISequentialEventHandler.h>
#  include <Bibim/UISimpleDomain.h>
#  include <Bibim/UISprite.h>
#  include <Bibim/UITintEffect.h>
#  include <Bibim/UITransform.h>
#  include <Bibim/UITransform3D.h>
#  include <Bibim/UIVideo.h>
#  include <Bibim/UIVisual.h>
#  include <Bibim/UIVisualVisitor.h>
#  include <Bibim/UIWindow.h>

#endif