#pragma once
#ifndef __BIBIM_FWD_H__
#define __BIBIM_FWD_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/NullPointer.h>
#   include <Bibim/PointerCasts.h>
#   include <Bibim/SharedPointer.h>
#   include <Bibim/WeakPointer.h>

    namespace Bibim
    {
#       define BBForwardDeclareSmartPointerClass(name) class name; \
                                                       typedef Bibim::SharedPointer<name> name##Ptr; \
                                                       typedef Bibim::WeakPointer<name>   name##WeakPtr;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // 01. Foundation
            // (Fundamental)
                class Any;
                struct Color;
                struct Colors;
                struct Matrix4;
                struct Point;
                struct Quaternion;
                template <typename T> struct Range;
                struct Rectangle;
                struct RectangleF;
                class String;
                class URI;
                struct UUID;
                struct Vector2;
                struct Vector3;
                struct Vector4;
                typedef Range<char>       CharRange;
                typedef Range<uchar>      UCharRange;
                typedef Range<short>      ShortRange;
                typedef Range<ushort>     UShortRange;
                typedef Range<int>        IntRange;
                typedef Range<uint>       UIntRange;
                typedef Range<long>       LongRange;
                typedef Range<ulong>      ULongRange;
                typedef Range<int64>      Int64Range;
                typedef Range<uint64>     UInt64Range;
                typedef Range<float>      FloatRange;
                typedef Range<double>     DoubleRange;
                typedef Range<Color>      ColorRange;
                typedef Range<Point>      PointRange;
                typedef Range<Quaternion> QuaternionRange;
                typedef Range<Rectangle>  RectangleRange;
                typedef Range<RectangleF> RectangleFRange;
                typedef Range<Vector2>    Vector2Range;
                typedef Range<Vector3>    Vector3Range;
                typedef Range<Vector4>    Vector4Range;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Assert
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Container
                class SequenceDictionary;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Exception
                class Exception;
                    class BadArgumentException;
                    class BadCastException;
                    class NotSupportedException;
                    class OutOfRangeException;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // IO
                BBForwardDeclareSmartPointerClass(Stream);
                    BBForwardDeclareSmartPointerClass(MemoryStream);
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Mathematics
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // SmartPointer
                BBForwardDeclareSmartPointerClass(SharedObject);
                template <typename T> class SharedPointer;
                template <typename T> class WeakPointer;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Utility
                template <typename T> class Property;
                class RectangleStorage;
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // 02. GameComponent
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // (Structure)
                class GameComponent;
                    class GameModule;
                class GameNode;
                class GameStructure;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Asset
                class Asset;
                class AssetStorage;
                class IAssetStorage;
                BBForwardDeclareSmartPointerClass(IReloadable);
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Cloning
                class CloningContext;
                BBForwardDeclareSmartPointerClass(ICloneable);
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Diagnostics
                ////////////////////////////////////////////////////////////////////////////////////////////////////
                // Logger
                    class GlobalLogger;
                    class Logger;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Disposal
                class GarbageMan;
                BBForwardDeclareSmartPointerClass(IDisposable);
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // FileSystem
                class FileSystem;
                class GlobalFileSystem;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Time
                BBForwardDeclareSmartPointerClass(IUpdateable);
                class Timeline;
                    class ParallelTimeline;
                    class SubTimeline;
                class UpdateableGameComponent;
                BBForwardDeclareSmartPointerClass(UpdateableObject);
                    BBForwardDeclareSmartPointerClass(Timer);
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // 03. Graphics
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // (Core)
                class DisplaySwapChain;
                class GraphicsDevice;
                class Window;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Assets
                BBForwardDeclareSmartPointerClass(Texture2D);
                    BBForwardDeclareSmartPointerClass(DynamicTexture2D);
                    BBForwardDeclareSmartPointerClass(MemoryTexture2D);
                    BBForwardDeclareSmartPointerClass(SourceTexture2D);
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Drawing
                class DrawingContext;
                BBForwardDeclareSmartPointerClass(IDrawable);
                class Sprite;
                class SpriteRenderer;
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // 03. Input
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Device
                class IGamePad;
                class IKeyboard;
                class IMouse;
                class ITouchPad;
                class Keyboard;
                struct KeyboardState;
                class Mouse;
                struct MouseState;
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // 04. Application
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Animation
                BBForwardDeclareSmartPointerClass(ColorRangeSequence);
                BBForwardDeclareSmartPointerClass(ColorSequence);
                BBForwardDeclareSmartPointerClass(ColorSequence);
                template <typename T> class EvaluableBlenderTemplate;
                BBForwardDeclareSmartPointerClass(EvaluableConstants);
                BBForwardDeclareSmartPointerClass(EvaluableFloatBlender);
                BBForwardDeclareSmartPointerClass(EvaluableFloatConstant);
                BBForwardDeclareSmartPointerClass(EvaluableFloatPrioritySelector);
                BBForwardDeclareSmartPointerClass(EvaluableFloatRangeSequence);
                BBForwardDeclareSmartPointerClass(EvaluableFloatSequence);
                BBForwardDeclareSmartPointerClass(EvaluablePointSequence);
                template <typename T> class EvaluablePrioritySelectorTemplate;
                template <typename T> class EvaluableRangeSequenceTemplate;
                BBForwardDeclareSmartPointerClass(EvaluableSequences);
                template <typename T> class EvaluableSequenceTemplate;
                BBForwardDeclareSmartPointerClass(EvaluableSpriteConstant);
                BBForwardDeclareSmartPointerClass(EvaluableSpriteSequence);
                BBForwardDeclareSmartPointerClass(FloatRangeSequence);
                BBForwardDeclareSmartPointerClass(FloatSequence);
                BBForwardDeclareSmartPointerClass(IBoolEvaluable);
                BBForwardDeclareSmartPointerClass(ICharEvaluable);
                BBForwardDeclareSmartPointerClass(IColorEvaluable);
                BBForwardDeclareSmartPointerClass(IDoubleEvaluable);
                BBForwardDeclareSmartPointerClass(IEvaluables);
                BBForwardDeclareSmartPointerClass(IFloatEvaluable);
                BBForwardDeclareSmartPointerClass(IFloatRangeEvaluable);
                BBForwardDeclareSmartPointerClass(IIntEvaluable);
                BBForwardDeclareSmartPointerClass(ILongEvaluable);
                BBForwardDeclareSmartPointerClass(IPointEvaluable);
                BBForwardDeclareSmartPointerClass(IQuaternionEvaluable);
                BBForwardDeclareSmartPointerClass(IRectangleEvaluable);
                BBForwardDeclareSmartPointerClass(IShortEvaluable);
                BBForwardDeclareSmartPointerClass(ISpriteEvaluable);
                BBForwardDeclareSmartPointerClass(IUCharEvaluable);
                BBForwardDeclareSmartPointerClass(IUIntEvaluable);
                BBForwardDeclareSmartPointerClass(IULongEvaluable);
                BBForwardDeclareSmartPointerClass(IUShortEvaluable);
                BBForwardDeclareSmartPointerClass(IVector2Evaluable);
                BBForwardDeclareSmartPointerClass(IVector3Evaluable);
                BBForwardDeclareSmartPointerClass(IVector4Evaluable);
                BBForwardDeclareSmartPointerClass(PointSequence);
                template <typename T> class SequenceTemplate;
                BBForwardDeclareSmartPointerClass(SpriteSequence);
                BBForwardDeclareSmartPointerClass(Vector2RangeSequence);
                BBForwardDeclareSmartPointerClass(Vector2Sequence);
                BBForwardDeclareSmartPointerClass(Vector3RangeSequence);
                BBForwardDeclareSmartPointerClass(Vector3Sequence);
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Collision
                BBForwardDeclareSmartPointerClass(IPickable);
                class PickingContext;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Collision2D
                class CollisionSpace2D;
                class IRaycastCallback2D;
                BBForwardDeclareSmartPointerClass(IUserShape2D);
                struct RaycastReport2D;
                BBForwardDeclareSmartPointerClass(Shape2D);
                    BBForwardDeclareSmartPointerClass(AxisAlignedBoxShape2D);
                    BBForwardDeclareSmartPointerClass(BoxShape2D);
                    BBForwardDeclareSmartPointerClass(PointShape2D);
                    BBForwardDeclareSmartPointerClass(SegmentShape2D);
                    BBForwardDeclareSmartPointerClass(SphereShape2D);
                    BBForwardDeclareSmartPointerClass(UserShape2D);
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Command
                class Command;
                    class RestorabelCommand;
                        class BatchCommand;
                class CommandHistory;
                class CommandQueue;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Entity
                BBForwardDeclareSmartPointerClass(Entity);
                class EntityComponent;
                class EntityWorld;
                class ObjectOperator;
                    class GameComponentOperator;
                    class SharedObjectOperator;
                    template <typename T, uint32 ClassID> class StructOperator;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Framework
                class GameFramework;
                class GameWindow;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Gameplay
                BBForwardDeclareSmartPointerClass(SpatialObject);
                BBForwardDeclareSmartPointerClass(SpatialObject2D);
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // JSON
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Lua
                class LuaRuntimeEnvironment;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // OS
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // SFX
                ////////////////////////////////////////////////////////////////////////////////////////////////////
                // Particle
                class Particle;
                BBForwardDeclareSmartPointerClass(ParticleEmitter);
                BBForwardDeclareSmartPointerClass(ParticleRenderer);
                BBForwardDeclareSmartPointerClass(ParticleSpace);
                class ParticleSpawnPoint;
                class ParticleSpawnSegment;
                class ParticleSpawnBox;
                class ParticleSpawnSphere;
                class SequentialParticle;
                BBForwardDeclareSmartPointerClass(SequentialParticleEmitter);
                class SimpleParticle;
                BBForwardDeclareSmartPointerClass(SimpleParticleEmitter);
                BBForwardDeclareSmartPointerClass(SimpleParticleRenderer);
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Script
                BBForwardDeclareSmartPointerClass(Flowchart);
                BBForwardDeclareSmartPointerClass(FlowchartBlock);
                class FlowingContext;
                BBForwardDeclareSmartPointerClass(IFlowchartProcess);
                BBForwardDeclareSmartPointerClass(VariableStorage);
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Typography
                BBForwardDeclareSmartPointerClass(Font);
                class FontString;
                class FontLibrary;
                class Glyph;
                class TypingContext;
                // (Internal)
                    BBForwardDeclareSmartPointerClass(FontCache);
                    struct FontCacheParameters;
                    class GlyphSurface;
                    class GlyphTable;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // UI
                class UIDomain;
                    class UISimpleDomain;
                BBForwardDeclareSmartPointerClass(UIElement);
                class UIFunctionTable;
                BBForwardDeclareSmartPointerClass(UIImage);
                class UIMarkupText;
                class UIRenderer;
                class UIVisualVisitor;
                    class UIDrawingContext;
                        class UIHandledDrawingContext;
                    class UIPickingContext;
                ////////////////////////////////////////////////////////////////////////////////////////////////////
                // Frames
                    BBForwardDeclareSmartPointerClass(UIFrame);
                        BBForwardDeclareSmartPointerClass(UIAlignedFrame);
                        BBForwardDeclareSmartPointerClass(UIAnchoredFrame);
                        BBForwardDeclareSmartPointerClass(UIFittedFrame);
                        BBForwardDeclareSmartPointerClass(UIFixedFrame);
                        BBForwardDeclareSmartPointerClass(UIFlowFrame);
                ////////////////////////////////////////////////////////////////////////////////////////////////////
                // Effects
                    BBForwardDeclareSmartPointerClass(UIEffect);
                        BBForwardDeclareSmartPointerClass(UITintEffect);
                    BBForwardDeclareSmartPointerClass(UIEffectMap);
                ////////////////////////////////////////////////////////////////////////////////////////////////////
                // Events
                    class UIAsyncEventQueue;
                    BBForwardDeclareSmartPointerClass(UIEventArgs);
                        BBForwardDeclareSmartPointerClass(UIGamePadEventArgs);
                        BBForwardDeclareSmartPointerClass(UIKeyboardEventArgs);
                        BBForwardDeclareSmartPointerClass(UIMouseEventArgs);
                            BBForwardDeclareSmartPointerClass(UIMouseButtonEventArgs);
                            BBForwardDeclareSmartPointerClass(UIMouseWheelEventArgs);
                        BBForwardDeclareSmartPointerClass(UITouchEventArgs);
                    class UIEventDispatcher;
                        class UIAppEventDispatcher;
                        class UIGamePadEventDispatcher;
                        class UIKeyboardEventDispatcher;
                        class UIMouseEventDispatcher;
                        class UITouchEventDispatcher;
                    class UIEventID;
                    BBForwardDeclareSmartPointerClass(UIEventMap);
                    ////////////////////////////////////////////////////////////////////////////////////////////////////
                    // Handlers
                        BBForwardDeclareSmartPointerClass(UIEventHandler);
                            BBForwardDeclareSmartPointerClass(UIFunctionEventHandler);
                            BBForwardDeclareSmartPointerClass(UISequentialEventHandler);
                ////////////////////////////////////////////////////////////////////////////////////////////////////
                // Transforms
                    BBForwardDeclareSmartPointerClass(UITransform);
                        BBForwardDeclareSmartPointerClass(UITransform3D);
                ////////////////////////////////////////////////////////////////////////////////////////////////////
                // Visuals
                    BBForwardDeclareSmartPointerClass(UIVisual);
                        BBForwardDeclareSmartPointerClass(UILabel);
                        BBForwardDeclareSmartPointerClass(UIPanel);
                            BBForwardDeclareSmartPointerClass(UIButton);
                                BBForwardDeclareSmartPointerClass(UICheckBox);
                            BBForwardDeclareSmartPointerClass(UIEditBox);
                            BBForwardDeclareSmartPointerClass(UIFlowPanel);
                                BBForwardDeclareSmartPointerClass(UIListBox);
                            BBForwardDeclareSmartPointerClass(UIMarkupTextBox);
                            BBForwardDeclareSmartPointerClass(UIWindow);
                        BBForwardDeclareSmartPointerClass(UISprite);
                        BBForwardDeclareSmartPointerClass(UIVideo);
    }

#endif