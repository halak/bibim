using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;

namespace Halak.Bibim
{
    public sealed class RectangleStorage
    {
        #region Fields
        private LinkedList<Rectangle> allocatedRectangles;
        private LinkedList<Rectangle> freeRectangles;
        #endregion

        #region Properties
        public int Width
        {
            get;
            private set;
        }

        public int Height
        {
            get;
            private set;
        }

        public ICollection<Rectangle> AllocatedRectangles
        {
            get { return allocatedRectangles; }
        }

        public ICollection<Rectangle> FreeRectangles
        {
            get { return freeRectangles; }
        }
        #endregion

        #region Constructors
        public RectangleStorage(int width, int height)
        {
            Trace.Assert(width > 0 && height > 0);

            Width = width;
            Height = height;
            allocatedRectangles = new LinkedList<Rectangle>();
            freeRectangles = new LinkedList<Rectangle>();
        }

        public RectangleStorage(RectangleStorage original)
        {
            Trace.Assert(original != null);

            Width = original.Width;
            Height = original.Height;
            allocatedRectangles = new LinkedList<Rectangle>(original.allocatedRectangles);
            freeRectangles = new LinkedList<Rectangle>(original.freeRectangles);
        }
        #endregion

        #region Methods
        public void Clear()
        {
            allocatedRectangles.Clear();
            freeRectangles.Clear();
            freeRectangles.AddLast(new Rectangle(0, 0, Width, Height));
        }

        public Rectangle Allocate(int width, int height)
        {
            if (width == 0 || height == 0)
                return Rectangle.Empty;

            // 1. 빈 영역중에 크기 같은 영역이 있으면 바로 할당합니다.
            // 2. 빈 영역중에 가로크기나, 세로크기가 같은것이 있으면 분할해 할당합니다.
            // 3. 빈 영역중 가장 가까운 영역을 찾아서 분할해 할당합니다.

            Rectangle nearest = Rectangle.Empty;
            LinkedListNode<Rectangle> nearestNode = null;

            for (LinkedListNode<Rectangle> node = freeRectangles.First; node != null; node = node.Next)
            {
                Rectangle current = node.Value;
                if (current.Width == width && current.Height == height)
                {
                    freeRectangles.Remove(node);
                    allocatedRectangles.AddLast(current);
                    return current;
                }

                if (current.Width == width && current.Height >= height)
                {
                    Rectangle result = current;
                    result.Height = height;

                    node.Value = new Rectangle(current.X, current.Y + height,
                                               current.Width, current.Height - height);
                    allocatedRectangles.AddLast(result);

                    return result;
                }

                if (current.Width >= width && current.Height == height)
                {
                    Rectangle result = current;
                    result.Width = width;

                    node.Value = new Rectangle(current.X + width, current.Y,
                                               current.Width - width, current.Height);
                    allocatedRectangles.AddLast(result);

                    return result;
                }

                if (current.Width >= width && current.Height >= height)
                {
                    if (nearest.IsEmpty || (current.Width <= nearest.Width && current.Height <= nearest.Height))
                    {
                        nearest = current;
                        nearestNode = node;
                    }
                }
            }

            if (nearest.IsEmpty == false)
            {
                int xPoint1 = nearest.Left;
                int xPoint2 = nearest.Left + width;
                int xPoint3 = nearest.Right;
                int yPoint1 = nearest.Top;
                int yPoint2 = nearest.Top + height;
                int yPoint3 = nearest.Bottom;

                Rectangle leftUp = Rectangle.FromLTRB(xPoint1, yPoint1, xPoint2, yPoint2);
                Rectangle rightUp = Rectangle.FromLTRB(xPoint2, yPoint1, xPoint3, yPoint2);
                Rectangle down = Rectangle.FromLTRB(xPoint1, yPoint2, xPoint3, yPoint3);

                freeRectangles.Remove(nearestNode);
                freeRectangles.AddLast(rightUp);
                freeRectangles.AddLast(down);
                allocatedRectangles.AddLast(leftUp);

                return leftUp;
            }
            else
                return Rectangle.Empty;
        }

        public void Deallocate(Rectangle rectangle)
        {
            LinkedListNode<Rectangle> node = allocatedRectangles.Find(rectangle);
            if (node != null)
            {
                freeRectangles.AddLast(rectangle);
                Merge(freeRectangles, freeRectangles.First);
                allocatedRectangles.Remove(node);
            }
            else
                Trace.WriteLine("RectangleStorage.Deallocate > 할당되지 않은 Rect를 Deallocate 하였습니다. ({0})", rectangle.ToString());
        }

        public static void Merge(LinkedList<Rectangle> rectangles, LinkedListNode<Rectangle> targetNode)
        {
            // targetIterator와 통합 가능한 영역을 찾아서 통합하고,
            // 그렇게 통합된 영역을 다른 영역과 통합해보기 위해 Merge를 재귀호출합니다.

            Rectangle target = targetNode.Value;
            for (LinkedListNode<Rectangle> node = rectangles.First; node != null; node = node.Next)
            {
                if (node == targetNode)
                    continue;

                Rectangle current = node.Value;

                if (current.Left == target.Left && current.Right == target.Right)
                {
                    if (current.Top == target.Bottom)
                    {
                        node.Value = Rectangle.FromLTRB(current.Left, target.Top, current.Right, current.Bottom);
                        rectangles.Remove(targetNode);
                        Merge(rectangles, node);
                        return;
                    }

                    if (current.Bottom == target.Top)
                    {
                        node.Value = Rectangle.FromLTRB(current.Left, current.Top, current.Right, target.Bottom);
                        rectangles.Remove(targetNode);
                        Merge(rectangles, node); 
                        return;
                    }
                }

                if (current.Top == target.Bottom && current.Bottom == target.Bottom)
                {
                    if (current.Left == target.Right)
                    {
                        node.Value = Rectangle.FromLTRB(target.Left, current.Top, current.Right, current.Bottom);
                        rectangles.Remove(targetNode);
                        Merge(rectangles, node);
                        return;
                    }

                    if (current.Right == target.Left)
                    {
                        node.Value = Rectangle.FromLTRB(current.Left, current.Top, target.Right, target.Bottom);
                        rectangles.Remove(targetNode);
                        Merge(rectangles, node);
                        return;
                    }
                }
            }
        }
        #endregion
    }
}
