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
                BBForwardDeclareSmartPointerClass(Stream);
                    BBForwardDeclareSmartPointerClass(MemoryStream);
                class StreamReader;
                class StreamWriter;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Mathematics
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Utility
                template <typename T> class Property;
                class RectangleStorage;
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
                class AssetProvider;
                    class PipedAssetProvider;
                    class FileAssetProvider;
                class AssetReader;
                BBForwardDeclareSmartPointerClass(GameAsset);
                class GameAssetStorage;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Framework
                class GameFrameworkBase;
                    class GameFramework;
                class GameWindow;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Graphics
                class DisplaySwapChain;
                class GraphicsDevice;
                BBForwardDeclareSmartPointerClass(Texture2D);
                    BBForwardDeclareSmartPointerClass(DynamicTexture2D);
                    BBForwardDeclareSmartPointerClass(MemoryTexture2D);
                    BBForwardDeclareSmartPointerClass(SourceTexture2D);
                class Window;
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // IPC
                BBForwardDeclareSmartPointerClass(PipeStream);
                    BBForwardDeclareSmartPointerClass(PipeClientStream);
                    BBForwardDeclareSmartPointerClass(PipeServerStream);
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            // Time
                class Clock;
                class UpdateableGameModule;
                    class Timeline;
                        class SubTimeline;
                    class TimelineGameModule;
    }

#endif