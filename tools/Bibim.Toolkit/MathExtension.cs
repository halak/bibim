using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim
{
    public static class MathExtension
    {
        public static double DegreeToRadian(int angle)
        {
            return DegreeToRadian((double)angle);
        }

        public static double DegreeToRadian(double angle)
        {
            return angle / 180.0 * Math.PI;
        }

        public static double RadianToDegree(double angle)
        {
            return angle / Math.PI * 180.0;
        }

        public static byte Lerp(byte value1, byte value2, float amount)
        {
            return (byte)Lerp((int)value1, (int)value2, amount);
        }

        public static short Lerp(short value1, short value2, float amount)
        {
            return (short)Lerp((int)value1, (int)value2, amount);
        }

        public static int Lerp(int value1, int value2, float amount)
        {
            return value1 + (int)((float)(value2 - value1) * amount);
        }

        public static float Lerp(float value1, float value2, float amount)
        {
            return value1 + (value2 - value1) * amount;
        }

        public static long Lerp(long value1, long value2, float amount)
        {
            return value1 + (long)((float)(value2 - value1) * amount);
        }

        public static int Clamp(int value, int min, int max)
        {
            return value < min ? min : (max < value ? max : value);
        }

        public static float Clamp(float value, float min, float max)
        {
            return value < min ? min : (max < value ? max : value);
        }

        public static double Clamp(double value, double min, double max)
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
