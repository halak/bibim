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
                struct Rect;
                struct RectF;
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
                typedef Range<Rect>       RectRange;
                typedef Range<RectF> RectFRange;
                typedef Range<Vector2>    Vector2Range;
                typedef Range<Vector3>    Vector3Range;
                typedef Range<Vector4>    Vector4Range;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // (SmartPointer)
                BBForwardDeclareSmartPointerClass(SharedObject);
                template <typename T> class SharedPointer;
                template <typename T> class WeakPointer;
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
                    BBForwardDeclareSmartPointerClass(MemoryStream);
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Mathematics
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Utility
                template <typename T> class Property;
                class RectStorage;
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // 02. Framework
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // (Module)
                class GameModule;
                class GameModuleFactory;
                class GameModuleNode;
                class GameModuleTree;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Asset
                class AssetLoadingTask;
                    class AssetPreloadingTask;
                class AssetStreamReader;
                BBForwardDeclareSmartPointerClass(GameAsset);
                class GameAssetFactory;
                class GameAssetStorage;
                ////////////////////////////////////////////////////////////////////////////////////////////////////
                // Providers
                    class AssetProvider;
                        class PipedAssetProvider;
                        class FileAssetProvider;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // FileSystem
                BBForwardDeclareSmartPointerClass(FileStream);
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Framework
                class GameFrameworkBase;
                    class GameFramework;
                class GameWindow;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Gameplay
                BBForwardDeclareSmartPointerClass(Command);
                    BBForwardDeclareSmartPointerClass(RestorableCommand);
                        BBForwardDeclareSmartPointerClass(BatchCommand);
                class CommandHistory;
                class CommandQueue;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Graphics
                class DisplaySwapChain;
                class GraphicsDevice;
                BBForwardDeclareSmartPointerClass(Texture2D);
                    BBForwardDeclareSmartPointerClass(DynamicTexture2D);
                    BBForwardDeclareSmartPointerClass(SourceTexture2D);
                class Window;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Input
                class GamePad;
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
            // Threading
                class AutoLocker;
                class Lock;
                class ManualLocker;
                class Thread;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Time
                class Clock;
                class UpdateableGameModule;
                    class Timeline;
                        class SubTimeline;
                    class TimelineGameModule;
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
                    BBForwardDeclareSmartPointerClass(UIImage);
                BBForwardDeclareSmartPointerClass(UILayout);
                class UIMarkupText;
                class UIRenderer;
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
                // Frames
                    BBForwardDeclareSmartPointerClass(UIFrame);
                        BBForwardDeclareSmartPointerClass(UIAlignedFrame);
                        BBForwardDeclareSmartPointerClass(UIAnchoredFrame);
                        BBForwardDeclareSmartPointerClass(UIFittedFrame);
                        BBForwardDeclareSmartPointerClass(UIFixedFrame);
                ////////////////////////////////////////////////////////////////////////////////////////////////////
                // Transforms
                    BBForwardDeclareSmartPointerClass(UITransform);
                        BBForwardDeclareSmartPointerClass(UITransform3D);
                ////////////////////////////////////////////////////////////////////////////////////////////////////
                // Visitors
                    class UIVisualVisitor;
                        class UIDrawingContext;
                            class UIHandledDrawingContext;
                        class UIPickingContext;
                ////////////////////////////////////////////////////////////////////////////////////////////////////
                // Visuals
                    BBForwardDeclareSmartPointerClass(UIVisual);
                        BBForwardDeclareSmartPointerClass(UILabel);
                        BBForwardDeclareSmartPointerClass(UIMarkupTextBox);
                        BBForwardDeclareSmartPointerClass(UIPanel);
                            BBForwardDeclareSmartPointerClass(UIButton);
                                BBForwardDeclareSmartPointerClass(UICheckBox);
                            BBForwardDeclareSmartPointerClass(UIWindow);
                        BBForwardDeclareSmartPointerClass(UISprite);
                        BBForwardDeclareSmartPointerClass(UIVideo);
    }

#endif