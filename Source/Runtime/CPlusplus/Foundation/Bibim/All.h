#pragma once
#ifndef __BIBIM_ALL_H__
#define __BIBIM_ALL_H__

   // This file was "AUTOMATICALLY GENERATED" by Bibim Console.
   // > Halak.Bibim.Toolkit.Console.exe CppHeaderGenerator full [Library-Name] [Source-Directory] [Header-File]


   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Animation
#  include <Bibim/ColorRangeSequence.h>
#  include <Bibim/ColorSequence.h>
#  include <Bibim/EvaluableBlenderTemplate.h>
#  include <Bibim/EvaluableConstants.h>
#  include <Bibim/EvaluableFloatBlender.h>
#  include <Bibim/EvaluableFloatConstant.h>
#  include <Bibim/EvaluableFloatPrioritySelector.h>
#  include <Bibim/EvaluableFloatRangeSequence.h>
#  include <Bibim/EvaluableFloatSequence.h>
#  include <Bibim/EvaluablePointSequence.h>
#  include <Bibim/EvaluablePrioritySelectorTemplate.h>
#  include <Bibim/EvaluableRangeSequenceTemplate.h>
#  include <Bibim/EvaluableSequences.h>
#  include <Bibim/EvaluableSequenceTemplate.h>
#  include <Bibim/EvaluableSpriteConstant.h>
#  include <Bibim/EvaluableSpriteSequence.h>
#  include <Bibim/FloatRangeSequence.h>
#  include <Bibim/FloatSequence.h>
#  include <Bibim/IBoolEvaluable.h>
#  include <Bibim/ICharEvaluable.h>
#  include <Bibim/IColorEvaluable.h>
#  include <Bibim/IDoubleEvaluable.h>
#  include <Bibim/IEvaluables.h>
#  include <Bibim/IFloatEvaluable.h>
#  include <Bibim/IFloatRangeEvaluable.h>
#  include <Bibim/IIntEvaluable.h>
#  include <Bibim/ILongEvaluable.h>
#  include <Bibim/IPointEvaluable.h>
#  include <Bibim/IQuaternionEvaluable.h>
#  include <Bibim/IRectangleEvaluable.h>
#  include <Bibim/IShortEvaluable.h>
#  include <Bibim/ISpriteEvaluable.h>
#  include <Bibim/IUCharEvaluable.h>
#  include <Bibim/IUIntEvaluable.h>
#  include <Bibim/IULongEvaluable.h>
#  include <Bibim/IUShortEvaluable.h>
#  include <Bibim/IVector2Evaluable.h>
#  include <Bibim/IVector3Evaluable.h>
#  include <Bibim/IVector4Evaluable.h>
#  include <Bibim/PointSequence.h>
#  include <Bibim/SequenceTemplate.h>
#  include <Bibim/SpriteSequence.h>
#  include <Bibim/Vector2RangeSequence.h>
#  include <Bibim/Vector2Sequence.h>
#  include <Bibim/Vector3RangeSequence.h>
#  include <Bibim/Vector3Sequence.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // App
#  include <Bibim/GameFramework.h>
#  include <Bibim/GameFramework.Windows.h>
#  include <Bibim/GameWindow.h>
#  include <Bibim/GameWindow.Windows.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Asset
#  include <Bibim/Asset.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Collision2D
#  include <Bibim/AxisAlignedBoxShape2D.h>
#  include <Bibim/BoxShape2D.h>
#  include <Bibim/CollisionSpace2D.h>
#  include <Bibim/IntersectShapes2D.h>
#  include <Bibim/PointShape2D.h>
#  include <Bibim/RaycastReport2D.h>
#  include <Bibim/SegmentShape2D.h>
#  include <Bibim/Shape2D.h>
#  include <Bibim/SphereShape2D.h>
#  include <Bibim/UserShape2D.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Command
#  include <Bibim/BatchCommand.h>
#  include <Bibim/Command.h>
#  include <Bibim/CommandHistory.h>
#  include <Bibim/CommandQueue.h>
#  include <Bibim/RestorableCommand.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // ComponentBase
#  include <Bibim/CloningContext.h>
#  include <Bibim/GameComponent.h>
#  include <Bibim/GameComponentFactory.h>
#  include <Bibim/GameModule.h>
#  include <Bibim/GameNode.h>
#  include <Bibim/GameStructure.h>
#  include <Bibim/IClassQueryable.h>
#  include <Bibim/ICloneable.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // FileSystem
#  include <Bibim/FileStream.h>
#  include <Bibim/FileStream.Windows.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Foundation
#  include <Bibim/All.h>
#  include <Bibim/Any.h>
#  include <Bibim/Assert.h>
#  include <Bibim/CheckedRelease.h>
#  include <Bibim/Color.h>
#  include <Bibim/Colors.h>
#  include <Bibim/Delete.h>
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
#  include <Bibim/Rectangle.h>
#  include <Bibim/RectangleF.h>
#  include <Bibim/RectangleStorage.h>
#  include <Bibim/SequenceDictionary.h>
#  include <Bibim/SharedObject.h>
#  include <Bibim/SharedObjectLife.h>
#  include <Bibim/SharedPointer.h>
#  include <Bibim/Signal.h>
#  include <Bibim/Stream.h>
#  include <Bibim/String.h>
#  include <Bibim/URI.h>
#  include <Bibim/UUID.h>
#  include <Bibim/Vector2.h>
#  include <Bibim/Vector3.h>
#  include <Bibim/Vector4.h>
#  include <Bibim/WeakPointer.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Graphics
#  include <Bibim/DisplaySwapChain.h>
#  include <Bibim/DynamicTexture2D.h>
#  include <Bibim/GraphicsDevice.h>
#  include <Bibim/MemoryTexture2D.h>
#  include <Bibim/SourceTexture2D.h>
#  include <Bibim/Sprite.h>
#  include <Bibim/Texture2D.h>
#  include <Bibim/Window.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Input
#  include <Bibim/IGamePad.h>
#  include <Bibim/IKeyboard.h>
#  include <Bibim/IMouse.h>
#  include <Bibim/ITouchPad.h>
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
   // Script
#  include <Bibim/Flowchart.h>
#  include <Bibim/FlowchartBlock.h>
#  include <Bibim/FlowingContext.h>
#  include <Bibim/IFlowchartProcess.h>
#  include <Bibim/LuaRuntimeEnvironment.h>
#  include <Bibim/VariableStorage.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // SFX
#  include <Bibim/Particle.h>
#  include <Bibim/ParticleControllers.h>
#  include <Bibim/ParticleEmitter.h>
#  include <Bibim/ParticleRenderer.h>
#  include <Bibim/ParticleSpace.h>
#  include <Bibim/ParticleSpawnPoints.h>
#  include <Bibim/SequentialParticle.h>
#  include <Bibim/SequentialParticleEmitter.h>
#  include <Bibim/SimpleParticle.h>
#  include <Bibim/SimpleParticleEmitter.h>
#  include <Bibim/SimpleParticleRenderer.h>

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Time
#  include <Bibim/Clock.h>
#  include <Bibim/IUpdateable.h>
#  include <Bibim/ParallelTimeline.h>
#  include <Bibim/ParallelTimeline.Windows.h>
#  include <Bibim/SubTimeline.h>
#  include <Bibim/Timeline.h>
#  include <Bibim/Timer.h>
#  include <Bibim/UpdateableGameComponent.h>
#  include <Bibim/UpdateableObject.h>

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
#  include <Bibim/UIEditBox.h>
#  include <Bibim/UIEffect.h>
#  include <Bibim/UIEffectMap.h>
#  include <Bibim/UIElement.h>
#  include <Bibim/UIEventArgs.h>
#  include <Bibim/UIEventDispatcher.h>
#  include <Bibim/UIEventHandler.h>
#  include <Bibim/UIEventID.h>
#  include <Bibim/UIEventMap.h>
#  include <Bibim/UIFittedFrame.h>
#  include <Bibim/UIFixedFrame.h>
#  include <Bibim/UIFlowPanel.h>
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
#  include <Bibim/UIListBox.h>
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
#  include <Bibim/UITouchEventArgs.h>
#  include <Bibim/UITouchEventDispatcher.h>
#  include <Bibim/UITransform.h>
#  include <Bibim/UITransform3D.h>
#  include <Bibim/UIVideo.h>
#  include <Bibim/UIVisual.h>
#  include <Bibim/UIVisualVisitor.h>
#  include <Bibim/UIWindow.h>

#endif