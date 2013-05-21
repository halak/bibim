#pragma once
#ifndef __BIBIM_FWD_H__
#define __BIBIM_FWD_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/NullPointer.h>
#   include <Bibim/PointerCasts.h>
#   include <Bibim/SharedPointer.h>

    namespace Bibim
    {
#       define BBForwardDeclareSmartPointerClass(name) class name; \
                                                       typedef Bibim::SharedPointer<name> name##Ptr;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // 01. Foundation
            // (Fundamental)
                class Any;
                struct Color;
                struct Matrix4;
                struct Point2;
                struct Point3;
                struct Point4;
                template <typename T> struct Range;
                struct Rect;
                struct RectF;
                class String;
                struct Vector2;
                struct Vector3;
                struct Vector4;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // (Object)
                class Object;
                    BBForwardDeclareSmartPointerClass(SharedObject);
                template <typename T> class SharedPointer;
                template <typename T> class ObjectFactoryTemplate;
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
                    class InvalidOperationException;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // IO
                class BinaryReader;
                class BinaryWriter;
                BBForwardDeclareSmartPointerClass(Stream);
                    BBForwardDeclareSmartPointerClass(DumpStream);
                    BBForwardDeclareSmartPointerClass(MemoryStream);
                    BBForwardDeclareSmartPointerClass(Win32Stream);
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Mathematics
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Utility
                BBForwardDeclareSmartPointerClass(AnyStorage);
                class RectStorage;
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // 02. Framework
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // (Asset)
                class AssetLoadingTask;
                    class AssetPreloadingTask;
                class AssetStreamReader;
                BBForwardDeclareSmartPointerClass(GameAsset);
                class GameAssetFactory;
                class GameAssetStorage;
                ////////////////////////////////////////////////////////////////////////////////////////////////////
                // Providers
                    class AssetProvider;
                        class FileAssetProvider;
                        class MPQAssetProvider;
                        class PipedAssetProvider;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // (Module)
                class GameModule;
                class GameModuleFactory;
                class GameModuleNode;
                class GameModuleTree;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // (Component)
                class CloningContext;
                class ComponentStreamReader;
                BBForwardDeclareSmartPointerClass(GameComponent);
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Animation
                BBForwardDeclareSmartPointerClass(Sprite);
                BBForwardDeclareSmartPointerClass(SpriteSet);
                ////////////////////////////////////////////////////////////////////////////////////////////////////
                // Evaluation
                    BBForwardDeclareSmartPointerClass(EvalBase);
                    BBForwardDeclareSmartPointerClass(EvalBoard);
                    class EvalContext;
                ////////////////////////////////////////////////////////////////////////////////////////////////////
                // Easing
                    BBForwardDeclareSmartPointerClass(EasingCurve);
                        BBForwardDeclareSmartPointerClass(LinearCurve);
                        BBForwardDeclareSmartPointerClass(EaseInQuadraticCurve);
                        BBForwardDeclareSmartPointerClass(EaseOutQuadraticCurve);
                        BBForwardDeclareSmartPointerClass(EaseInOutQuadraticCurve);
                        BBForwardDeclareSmartPointerClass(EaseInCubicCurve);
                        BBForwardDeclareSmartPointerClass(EaseOutCubicCurve);
                        BBForwardDeclareSmartPointerClass(EaseInOutCubicCurve);
                        BBForwardDeclareSmartPointerClass(EaseInQuarticCurve);
                        BBForwardDeclareSmartPointerClass(EaseOutQuarticCurve);
                        BBForwardDeclareSmartPointerClass(EaseInOutQuarticCurve);
                        BBForwardDeclareSmartPointerClass(EaseInQuinticCurve);
                        BBForwardDeclareSmartPointerClass(EaseOutQuinticCurve);
                        BBForwardDeclareSmartPointerClass(EaseInOutQuinticCurve);
                        BBForwardDeclareSmartPointerClass(EaseInSinusoidalCurve);
                        BBForwardDeclareSmartPointerClass(EaseOutSinusoidalCurve);
                        BBForwardDeclareSmartPointerClass(EaseInOutSinusoidalCurve);
                        BBForwardDeclareSmartPointerClass(EaseInExponentialCurve);
                        BBForwardDeclareSmartPointerClass(EaseOutExponentialCurve);
                        BBForwardDeclareSmartPointerClass(EaseInOutExponentialCurve);
                        BBForwardDeclareSmartPointerClass(EaseInCircularCurve);
                        BBForwardDeclareSmartPointerClass(EaseOutCircularCurve);
                        BBForwardDeclareSmartPointerClass(EaseInOutCircularCurve);
                        BBForwardDeclareSmartPointerClass(ElasticEasingCurve);
                            BBForwardDeclareSmartPointerClass(EaseInElasticCurve);
                            BBForwardDeclareSmartPointerClass(EaseOutElasticCurve);
                            BBForwardDeclareSmartPointerClass(EaseInOutElasticCurve);
                        BBForwardDeclareSmartPointerClass(OscillationCurve);
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Audio
                class AudioDevice;
                class BGM;
                class SoundFX;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Collision
                class CollisionSpace2D;
                class IRaycastCallback2D;
                struct RaycastReport2D;
                BBForwardDeclareSmartPointerClass(Shape2D);
                    BBForwardDeclareSmartPointerClass(AxisAlignedBoxShape2D);
                    BBForwardDeclareSmartPointerClass(BoxShape2D);
                    BBForwardDeclareSmartPointerClass(PointShape2D);
                    BBForwardDeclareSmartPointerClass(SegmentShape2D);
                    BBForwardDeclareSmartPointerClass(SphereShape2D);
                    BBForwardDeclareSmartPointerClass(UserShape2D);
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Diagnostics
                class Logger;
                    class FileLogger;
                    class OutputWindowLogger;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // FileSystem
                BBForwardDeclareSmartPointerClass(FileStream);
                BBForwardDeclareSmartPointerClass(MPQ);
                BBForwardDeclareSmartPointerClass(MPQStream);
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Framework
                class Clipboard;
                class GameFrameworkBase;
                    class GameFramework;
                        class StandardGame;
                class GameWindow;
                class Lua;
                class Preferences;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Gameplay
                BBForwardDeclareSmartPointerClass(Command);
                    BBForwardDeclareSmartPointerClass(RestorableCommand);
                        BBForwardDeclareSmartPointerClass(BatchCommand);
                class CommandHistory;
                class CommandQueue;
                BBForwardDeclareSmartPointerClass(PathFinder);
                    BBForwardDeclareSmartPointerClass(JumpPointPathFinder);
                BBForwardDeclareSmartPointerClass(SpatialObject2D);
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // GFX
                class SparkParticleEngine;

            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Graphics
                class GraphicsCapabilities;
                class GraphicsDevice;
                BBForwardDeclareSmartPointerClass(Image);
                BBForwardDeclareSmartPointerClass(ImageSet);
                class ScreenshotPrinter;
                BBForwardDeclareSmartPointerClass(BitMask);
                BBForwardDeclareSmartPointerClass(ShaderEffect);
                BBForwardDeclareSmartPointerClass(Texture2D);
                    BBForwardDeclareSmartPointerClass(DynamicTexture2D);
                    BBForwardDeclareSmartPointerClass(RenderTargetTexture2D);
                    BBForwardDeclareSmartPointerClass(SourceTexture2D);
                class Window;

            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Input
                class GamePad;
                class IME;
                class Keyboard;
                struct KeyboardState;
                class Mouse;
                struct MouseState;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // IPC
                BBForwardDeclareSmartPointerClass(PipeStream);
                    BBForwardDeclareSmartPointerClass(PipeClientStream);
                    BBForwardDeclareSmartPointerClass(PipeServerStream);
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Net
                class HttpClient;

            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Scripting
                class LuaRuntimeEnvironment;
                BBForwardDeclareSmartPointerClass(Script);
                class ScriptingContext;
                BBForwardDeclareSmartPointerClass(ScriptThread);
                class ScriptStack;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Threading
                class AutoLocker;
                class Lock;
                class ManualLocker;
                class Thread;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Time
                class Clock;
                class IUpdateable;
                class UpdateableGameModule;
                    class Timeline;
                        class SubTimeline;
                    class TimelineGameModule;
                        class AlarmClock;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Typography
                BBForwardDeclareSmartPointerClass(Font);
                BBForwardDeclareSmartPointerClass(FontCache);
                struct FontCacheParameters;
                class FontLibrary;
                class FontString;
                class Glyph;
                class GlyphSurface;
                class GlyphTable;
                class TypingContext;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // UI
                class UIDomain;
                    class UISimpleDomain;
                BBForwardDeclareSmartPointerClass(UIElement);
                BBForwardDeclareSmartPointerClass(UILayout);
                BBForwardDeclareSmartPointerClass(UIRenderBuffer);
                class UIRenderer;
                ////////////////////////////////////////////////////////////////////////////////////////////////////
                // Effects
                    BBForwardDeclareSmartPointerClass(UIEffectMap);
                    BBForwardDeclareSmartPointerClass(UIEffectStack);
                    BBForwardDeclareSmartPointerClass(UIGeometryEffect);
                        BBForwardDeclareSmartPointerClass(UIAfterImageEffect);
                        BBForwardDeclareSmartPointerClass(UISineCurveEffect);
                        BBForwardDeclareSmartPointerClass(UITintEffect);
                    BBForwardDeclareSmartPointerClass(UIPixelEffect);
                        BBForwardDeclareSmartPointerClass(UIBlendingEffect);
                        BBForwardDeclareSmartPointerClass(UIColorMatrixEffect);
                        BBForwardDeclareSmartPointerClass(UIMaskEffect);
                            BBForwardDeclareSmartPointerClass(UIOpacityMaskEffect);
                ////////////////////////////////////////////////////////////////////////////////////////////////////
                // Events
                    class UIAsyncEventQueue;
                    BBForwardDeclareSmartPointerClass(UIEventArgs);
                        BBForwardDeclareSmartPointerClass(UIGamePadEventArgs);
                        BBForwardDeclareSmartPointerClass(UIKeyboardEventArgs);
                        BBForwardDeclareSmartPointerClass(UIMouseEventArgs);
                            BBForwardDeclareSmartPointerClass(UIMouseButtonEventArgs);
                            BBForwardDeclareSmartPointerClass(UIMouseWheelEventArgs);
                    class UIEventDispatcher;
                        class UIAppEventDispatcher;
                        class UIGamePadEventDispatcher;
                        class UIKeyboardEventDispatcher;
                        class UIMouseEventDispatcher;
                    class UIEventID;
                    BBForwardDeclareSmartPointerClass(UIEventHandler);
                        BBForwardDeclareSmartPointerClass(UIFunctionEventHandler);
                        BBForwardDeclareSmartPointerClass(UISequentialEventHandler);
                    BBForwardDeclareSmartPointerClass(UIEventMap);
                    class UIFunctionTable;
                ////////////////////////////////////////////////////////////////////////////////////////////////////
                // Transforms
                    BBForwardDeclareSmartPointerClass(UITransform);
                        BBForwardDeclareSmartPointerClass(UITransform2D);
                        BBForwardDeclareSmartPointerClass(UITransform3D);
                ////////////////////////////////////////////////////////////////////////////////////////////////////
                // Visitors
                    class UIVisualVisitor;
                        class UIBoundsContext;
                        class UIDrawingContext;
                            class UIHandledDrawingContext;
                        class UIPickingContext;
                ////////////////////////////////////////////////////////////////////////////////////////////////////
                // Visuals
                    BBForwardDeclareSmartPointerClass(UIVisual);
                        BBForwardDeclareSmartPointerClass(UIImage);
                        BBForwardDeclareSmartPointerClass(UILabel);
                            BBForwardDeclareSmartPointerClass(UIEditText);
                        BBForwardDeclareSmartPointerClass(UIPanel);
                            BBForwardDeclareSmartPointerClass(UIButton);
                                BBForwardDeclareSmartPointerClass(UICheckBox);
                                    BBForwardDeclareSmartPointerClass(UIRadioButton);
                            BBForwardDeclareSmartPointerClass(UIDocument);
                            BBForwardDeclareSmartPointerClass(UIScrollablePanel);
                            BBForwardDeclareSmartPointerClass(UIWindow);
                        BBForwardDeclareSmartPointerClass(UIRect);
                        BBForwardDeclareSmartPointerClass(UISprite);
                        BBForwardDeclareSmartPointerClass(UIVideo);
                        BBForwardDeclareSmartPointerClass(UISpark);
    }

#endif