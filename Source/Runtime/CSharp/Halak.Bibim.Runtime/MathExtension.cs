using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim
{
    public static class MathExtension
    {
        public static int Clamp(int value, int min, int max)
        {
            return value < min ? min : (max < value ? max : value);
        }

        /// <summary>
        /// 입력한 수 보다 큰 2의 멱수 중 가장 작은 차를 가진 수를 가져옵니다.
        /// </summary>
        /// <param name="value">멱수를 구할 정수</param>
        /// <returns>2의 멱수 중 하나</returns>
        public static int GetNearestPowerOfTwo(int value)
        {
            if (value > 0)
                return (int)GetNearestPowerOfTwo((uint)value);
            else
                return 0;
        }

        /// <summary>
        /// 입력한 수 보다 큰 2의 멱수 중 가장 작은 차를 가진 수를 가져옵니다.
        /// </summary>
        /// <param name="value">멱수를 구할 정수</param>
        /// <returns>2의 멱수 중 하나</returns>
        /// <seealso cref="http://www.gamedev.net/topic/229831-nearest-power-of-2/"/>
        public static uint GetNearestPowerOfTwo(uint value)
        {
            value--;
            value |= (value >> 1);
            value |= (value >> 2);
            value |= (value >> 4);
            value |= (value >> 8);
            value |= (value >> 16);
            value++;
            return value;
        }
    }
}
