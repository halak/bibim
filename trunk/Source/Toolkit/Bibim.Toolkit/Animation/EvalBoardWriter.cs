using System;
using System.Collections.Generic;
using System.Reflection;
using System.Text;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(EvalBoard))]
    public sealed class EvalBoardWriter : GameAssetWriter<EvalBoard>
    {
        private static Dictionary<Type, MethodInfo> writeMethods;

        public sealed override void Write(AssetStreamWriter writer, EvalBoard asset)
        {
            List<object> objMap = new List<object>();
            writer.Write(asset.ClassID);
            writer.Write(asset.Duration);
            writer.Write((short)asset.Items.Count);
            foreach (var item in asset.Items)
            {
                writer.WriteBibimString(item.Name);
                Write(writer, item.Root, objMap);
            }
        }

        private static void Write(AssetStreamWriter writer, object o, IList<object> objMap)
        {
            if (o == null)
            {
                writer.Write((int)-1);
                return;
            }

            #region Generate WriteMethodTable
            if (writeMethods == null)
            {
                Type t = typeof(EvalBoardWriter);

                MethodInfo[] methods = t.GetMethods(BindingFlags.NonPublic | BindingFlags.Public | BindingFlags.Static);
                writeMethods = new Dictionary<Type, MethodInfo>(methods.Length);
                foreach (var item in methods)
                {
                    if (item.IsStatic && item.Name == "Write")
                    {
                        var parameters = item.GetParameters();
                        if (parameters.Length == 3)
                        {
                            if (parameters[0].ParameterType == typeof(AssetStreamWriter) &&
                                parameters[2].ParameterType == typeof(IList<object>))
                                writeMethods.Add(parameters[1].ParameterType, item);
                        }
                    }
                }
            }
            #endregion

            MethodInfo mi = null;
            if (writeMethods.TryGetValue(o.GetType(), out mi))
                mi.Invoke(null, new object[] { writer, o, objMap });
            else
                throw new ArgumentException(string.Format("Write Method가 정의되지 않은 형식입니다. {0}", o.GetType()), "o");
        }

        #region Write Templates
        private static bool WriteGameComponent(AssetStreamWriter writer, GameComponent o, IList<object> objMap)
        {
            int index = objMap.IndexOf(o);
            if (index != -1)
            {
                writer.Write(index);
                return false;
            }
            else
            {
                objMap.Add(o);
                writer.Write(objMap.Count - 1);
                writer.Write(o.ClassID);
                return true;
            }
        }

        private static bool WriteEval<V>(AssetStreamWriter writer, Eval<V> o, IList<object> objMap)
        {
            return WriteGameComponent(writer, o, objMap);
        }

        private static bool WriteConstant<V>(AssetStreamWriter writer, EvalConstantTemplate<V> o, IList<object> objMap)
        {
            return WriteEval(writer, o, objMap);
        }

        private static bool WriteVariable<V>(AssetStreamWriter writer, EvalVariableTemplate<V> o, IList<object> objMap)
        {
            if (WriteEval(writer, o, objMap) == false)
                return false;
          
            writer.WriteBibimString(o.Name);
  
            return true;
        }

        private static bool WriteUnaryOperator<V, VOperand>(AssetStreamWriter writer, EvalUnaryOperatorTemplate<V, VOperand> o, IList<object> objMap)
        {
            if (WriteEval(writer, o, objMap) == false)
                return false;

            Write(writer, o.Operand, objMap);

            return true;
        }

        private static bool WriteBinaryOperator<V, VLeft, VRight>(AssetStreamWriter writer, EvalBinaryOperatorTemplate<V, VLeft, VRight> o, IList<object> objMap)
        {
            if (WriteEval(writer, o, objMap) == false)
                return false;

            Write(writer, o.Left, objMap);
            Write(writer, o.Right, objMap);

            return true;
        }

        private static bool WriteSequenceBase<V>(AssetStreamWriter writer, EvalSequenceBaseTemplate<V> o, IList<object> objMap)
        {
            if (WriteEval(writer, o, objMap) == false)
                return false;

            writer.Write(o.Velocity);
            writer.Write(o.Looped);

            return true;
        }

        private static bool WriteSequence<V, VSequence>(AssetStreamWriter writer, EvalSequenceTemplate<V, VSequence> o, IList<object> objMap) where VSequence : SequenceTemplate<V>
        {
            if (WriteSequenceBase(writer, o, objMap) == false)
                return false;

            writer.Write(o.Source);

            return true;
        }

        private static bool WriteRangedSequence<V, VSequence>(AssetStreamWriter writer, EvalRangedSequenceTemplate<V, VSequence> o, IList<object> objMap) where VSequence : SequenceTemplate<V>
        {
            if (WriteSequenceBase(writer, o, objMap) == false)
                return false;

            writer.Write(o.Source1);
            writer.Write(o.Source2);

            return true;
        }

        private static bool WriteInterpolator<V>(AssetStreamWriter writer, EvalInterpolatorTemplate<V> o, IList<object> objMap)
        {
            if (WriteEval(writer, o, objMap) == false)
                return false;

            Write(writer, o.Value1, objMap);
            Write(writer, o.Value2, objMap);
            Write(writer, o.Weight, objMap);
            Write(writer, o.EasingCurve, objMap);

            return true;
        }

        private static bool WriteSelector<V>(AssetStreamWriter writer, EvalSelectorTemplate<V> o, IList<object> objMap)
        {
            if (WriteEval(writer, o, objMap) == false)
                return false;

            Write(writer, o.Condition, objMap);
            if (o.Cases != null)
            {
                writer.Write((short)o.Cases.Count);
                foreach (var item in o.Cases)
                {
                    writer.Write(item.Min);
                    writer.Write(item.Max);
                    Write(writer, item.Item, objMap);
                }
            }
            else
                writer.Write((short)0);

            Write(writer, o.DefaultCase, objMap);

            return true;
        }

        private static bool WriteCache<V>(AssetStreamWriter writer, EvalCacheTemplate<V> o, IList<object> objMap)
        {
            if (WriteEval(writer, o, objMap) == false)
                return false;

            Write(writer, o.Source, objMap);
            writer.Write((byte)o.UpdateMode);

            return true;
        }

        private static bool WriteEasingCurve(AssetStreamWriter writer, EasingCurve o, IList<object> objMap)
        {
            return WriteGameComponent(writer, o, objMap);
        }

        private static bool WriteElasticEasingCurve(AssetStreamWriter writer, ElasticEasingCurve o, IList<object> objMap)
        {
            if (WriteEasingCurve(writer, o, objMap) == false)
                return false;

            writer.Write(o.Amplitude);
            writer.Write(o.Period);

            return true;
        }
        #endregion

        #region Write EvalConstantTemplate<T> derived classes
        private static void Write(AssetStreamWriter writer, EvalBoolConstant o, IList<object> objMap)
        {
            if (WriteConstant(writer, o, objMap))
                writer.Write(o.Value);
        }

        private static void Write(AssetStreamWriter writer, EvalColorConstant o, IList<object> objMap)
        {
            if (WriteConstant(writer, o, objMap))
                writer.Write(o.Value);
        }

        private static void Write(AssetStreamWriter writer, EvalDoubleConstant o, IList<object> objMap)
        {
            if (WriteConstant(writer, o, objMap))
                writer.Write(o.Value);
        }

        private static void Write(AssetStreamWriter writer, EvalFloatConstant o, IList<object> objMap)
        {
            if (WriteConstant(writer, o, objMap))
                writer.Write(o.Value);
        }

        private static void Write(AssetStreamWriter writer, EvalGameAssetConstant o, IList<object> objMap)
        {
            if (WriteConstant(writer, o, objMap))
                writer.Write(o.Value);
        }

        private static void Write(AssetStreamWriter writer, EvalIntConstant o, IList<object> objMap)
        {
            if (WriteConstant(writer, o, objMap))
                writer.Write(o.Value);
        }

        private static void Write(AssetStreamWriter writer, EvalLongIntConstant o, IList<object> objMap)
        {
            if (WriteConstant(writer, o, objMap))
                writer.Write(o.Value);
        }

        private static void Write(AssetStreamWriter writer, EvalPoint2Constant o, IList<object> objMap)
        {
            if (WriteConstant(writer, o, objMap))
                writer.Write(o.Value);
        }

        private static void Write(AssetStreamWriter writer, EvalPoint3Constant o, IList<object> objMap)
        {
            if (WriteConstant(writer, o, objMap))
                writer.Write(o.Value);
        }

        private static void Write(AssetStreamWriter writer, EvalPoint4Constant o, IList<object> objMap)
        {
            if (WriteConstant(writer, o, objMap))
                writer.Write(o.Value);
        }

        private static void Write(AssetStreamWriter writer, EvalRectConstant o, IList<object> objMap)
        {
            if (WriteConstant(writer, o, objMap))
                writer.Write(o.Value);
        }

        private static void Write(AssetStreamWriter writer, EvalRectFConstant o, IList<object> objMap)
        {
            if (WriteConstant(writer, o, objMap))
                writer.Write(o.Value);
        }

        private static void Write(AssetStreamWriter writer, EvalShortIntConstant o, IList<object> objMap)
        {
            if (WriteConstant(writer, o, objMap))
                writer.Write(o.Value);
        }

        private static void Write(AssetStreamWriter writer, EvalVector2Constant o, IList<object> objMap)
        {
            if (WriteConstant(writer, o, objMap))
                writer.Write(o.Value);
        }

        private static void Write(AssetStreamWriter writer, EvalVector3Constant o, IList<object> objMap)
        {
            if (WriteConstant(writer, o, objMap))
                writer.Write(o.Value);
        }

        private static void Write(AssetStreamWriter writer, EvalVector4Constant o, IList<object> objMap)
        {
            if (WriteConstant(writer, o, objMap))
                writer.Write(o.Value);
        }
        #endregion

        #region Write EvalVariableTemplate<T> derived classes
        private static void Write(AssetStreamWriter writer, EvalBoolVariable o, IList<object> objMap) { WriteVariable(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalColorVariable o, IList<object> objMap) { WriteVariable(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalDoubleVariable o, IList<object> objMap) { WriteVariable(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalFloatVariable o, IList<object> objMap) { WriteVariable(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalGameAssetVariable o, IList<object> objMap) { WriteVariable(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalIntVariable o, IList<object> objMap) { WriteVariable(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalLongIntVariable o, IList<object> objMap) { WriteVariable(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalPoint2Variable o, IList<object> objMap) { WriteVariable(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalPoint3Variable o, IList<object> objMap) { WriteVariable(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalPoint4Variable o, IList<object> objMap) { WriteVariable(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalRectVariable o, IList<object> objMap) { WriteVariable(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalRectFVariable o, IList<object> objMap) { WriteVariable(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalShortIntVariable o, IList<object> objMap) { WriteVariable(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalVector2Variable o, IList<object> objMap) { WriteVariable(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalVector3Variable o, IList<object> objMap) { WriteVariable(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalVector4Variable o, IList<object> objMap) { WriteVariable(writer, o, objMap); }
        #endregion

        #region Write EvalSequenceTemplate<T, TSequence> derived classes
        private static void Write(AssetStreamWriter writer, EvalBoolSequence o, IList<object> objMap) { WriteSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalColorSequence o, IList<object> objMap) { WriteSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalDoubleSequence o, IList<object> objMap) { WriteSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalFloatSequence o, IList<object> objMap) { WriteSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalGameAssetSequence o, IList<object> objMap) { WriteSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalIntSequence o, IList<object> objMap) { WriteSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalLongIntSequence o, IList<object> objMap) { WriteSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalPoint2Sequence o, IList<object> objMap) { WriteSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalPoint3Sequence o, IList<object> objMap) { WriteSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalPoint4Sequence o, IList<object> objMap) { WriteSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalRectSequence o, IList<object> objMap) { WriteSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalRectFSequence o, IList<object> objMap) { WriteSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalShortIntSequence o, IList<object> objMap) { WriteSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalVector2Sequence o, IList<object> objMap) { WriteSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalVector3Sequence o, IList<object> objMap) { WriteSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalVector4Sequence o, IList<object> objMap) { WriteSequence(writer, o, objMap); }
        #endregion

        #region Write EvalRangedSequenceTemplate<T, TSequence> derived classes
        private static void Write(AssetStreamWriter writer, EvalBoolRangedSequence o, IList<object> objMap) { WriteRangedSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalColorRangedSequence o, IList<object> objMap) { WriteRangedSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalDoubleRangedSequence o, IList<object> objMap) { WriteRangedSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalFloatRangedSequence o, IList<object> objMap) { WriteRangedSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalGameAssetRangedSequence o, IList<object> objMap) { WriteRangedSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalIntRangedSequence o, IList<object> objMap) { WriteRangedSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalLongIntRangedSequence o, IList<object> objMap) { WriteRangedSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalPoint2RangedSequence o, IList<object> objMap) { WriteRangedSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalPoint3RangedSequence o, IList<object> objMap) { WriteRangedSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalPoint4RangedSequence o, IList<object> objMap) { WriteRangedSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalRectRangedSequence o, IList<object> objMap) { WriteRangedSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalRectFRangedSequence o, IList<object> objMap) { WriteRangedSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalShortIntRangedSequence o, IList<object> objMap) { WriteRangedSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalVector2RangedSequence o, IList<object> objMap) { WriteRangedSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalVector3RangedSequence o, IList<object> objMap) { WriteRangedSequence(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalVector4RangedSequence o, IList<object> objMap) { WriteRangedSequence(writer, o, objMap); }
        #endregion

        #region Write EvalUnaryOperator<T, TOperand> derived classes
        #region Bool
        private static void Write(AssetStreamWriter writer, EvalBoolNOT o, IList<object> objMap) { WriteUnaryOperator(writer, o, objMap); }
        #endregion
        #region Double
        private static void Write(AssetStreamWriter writer, EvalFloatToDouble o, IList<object> objMap) { WriteUnaryOperator(writer, o, objMap); }
        #endregion
        #region Float
        private static void Write(AssetStreamWriter writer, EvalFloatNegation o, IList<Object> objMap) { WriteUnaryOperator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalIntToFloat o, IList<object> objMap) { WriteUnaryOperator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalDoubleToFloat o, IList<object> objMap) { WriteUnaryOperator(writer, o, objMap); }
        #endregion
        #region Int
        private static void Write(AssetStreamWriter writer, EvalIntNegation o, IList<object> objMap) { WriteUnaryOperator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalShortIntToInt o, IList<object> objMap) { WriteUnaryOperator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalLongIntToInt o, IList<object> objMap) { WriteUnaryOperator(writer, o, objMap); }
        #endregion
        #region LongInt
        private static void Write(AssetStreamWriter writer, EvalIntToLongInt o, IList<object> objMap) { WriteUnaryOperator(writer, o, objMap); }
        #endregion
        #region ShortInt
        private static void Write(AssetStreamWriter writer, EvalIntToShortInt o, IList<object> objMap) { WriteUnaryOperator(writer, o, objMap); }
        #endregion
        #endregion

        #region Write EvalBinaryOperator<T, TLeft, TRight> derived classes
        #region Bool
        private static void Write(AssetStreamWriter writer, EvalBoolAND o, IList<object> objMap) { WriteBinaryOperator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalBoolOR o, IList<object> objMap) { WriteBinaryOperator(writer, o, objMap); }
        #endregion
        #region Float
        private static void Write(AssetStreamWriter writer, EvalFloatAddition o, IList<object> objMap) { WriteBinaryOperator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalFloatSubtraction o, IList<object> objMap) { WriteBinaryOperator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalFloatMultiplication o, IList<object> objMap) { WriteBinaryOperator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalFloatDivision o, IList<object> objMap) { WriteBinaryOperator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalFloatModulus o, IList<object> objMap) { WriteBinaryOperator(writer, o, objMap); }
        #endregion
        #region Int
        private static void Write(AssetStreamWriter writer, EvalIntAddition o, IList<object> objMap) { WriteBinaryOperator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalIntSubtraction o, IList<object> objMap) { WriteBinaryOperator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalIntMultiplication o, IList<object> objMap) { WriteBinaryOperator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalIntDivision o, IList<object> objMap) { WriteBinaryOperator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalIntModulus o, IList<object> objMap) { WriteBinaryOperator(writer, o, objMap); }
        #endregion
        #endregion

        #region Write EvalInterpolator<T> derived classes
        private static void Write(AssetStreamWriter writer, EvalColorInterpolator o, IList<object> objMap) { WriteInterpolator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalDoubleInterpolator o, IList<object> objMap) { WriteInterpolator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalFloatInterpolator o, IList<object> objMap) { WriteInterpolator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalIntInterpolator o, IList<object> objMap) { WriteInterpolator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalLongIntInterpolator o, IList<object> objMap) { WriteInterpolator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalPoint2Interpolator o, IList<object> objMap) { WriteInterpolator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalPoint3Interpolator o, IList<object> objMap) { WriteInterpolator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalPoint4Interpolator o, IList<object> objMap) { WriteInterpolator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalShortIntInterpolator o, IList<object> objMap) { WriteInterpolator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalVector2Interpolator o, IList<object> objMap) { WriteInterpolator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalVector3Interpolator o, IList<object> objMap) { WriteInterpolator(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalVector4Interpolator o, IList<object> objMap) { WriteInterpolator(writer, o, objMap); }
        #endregion

        #region Write EvalSelector<T> derived classes
        private static void Write(AssetStreamWriter writer, EvalColorSelector o, IList<object> objMap) { WriteSelector(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalDoubleSelector o, IList<object> objMap) { WriteSelector(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalFloatSelector o, IList<object> objMap) { WriteSelector(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalIntSelector o, IList<object> objMap) { WriteSelector(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalLongIntSelector o, IList<object> objMap) { WriteSelector(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalPoint2Selector o, IList<object> objMap) { WriteSelector(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalPoint3Selector o, IList<object> objMap) { WriteSelector(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalPoint4Selector o, IList<object> objMap) { WriteSelector(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalShortIntSelector o, IList<object> objMap) { WriteSelector(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalVector2Selector o, IList<object> objMap) { WriteSelector(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalVector3Selector o, IList<object> objMap) { WriteSelector(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalVector4Selector o, IList<object> objMap) { WriteSelector(writer, o, objMap); }
        #endregion

        #region Write EvalCache<T> derived classes
        private static void Write(AssetStreamWriter writer, EvalColorCache o, IList<object> objMap) { WriteCache(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalDoubleCache o, IList<object> objMap) { WriteCache(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalFloatCache o, IList<object> objMap) { WriteCache(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalIntCache o, IList<object> objMap) { WriteCache(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalLongIntCache o, IList<object> objMap) { WriteCache(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalPoint2Cache o, IList<object> objMap) { WriteCache(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalPoint3Cache o, IList<object> objMap) { WriteCache(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalPoint4Cache o, IList<object> objMap) { WriteCache(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalShortIntCache o, IList<object> objMap) { WriteCache(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalVector2Cache o, IList<object> objMap) { WriteCache(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalVector3Cache o, IList<object> objMap) { WriteCache(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EvalVector4Cache o, IList<object> objMap) { WriteCache(writer, o, objMap); }
        #endregion

        #region Write misc classes
        private static void Write(AssetStreamWriter writer, EvalTimeflow o, IList<object> objMap)
        {
            if (WriteEval(writer, o, objMap) == false)
                return;

            writer.Write(o.Timeline);
            writer.Write(o.Duration);
            writer.Write(o.Velocity);
            writer.Write((byte)o.StopBehavior);
            writer.Write(o.IsLooped);
            writer.Write(o.IsNormalized);
        }

        private static void Write(AssetStreamWriter writer, EvalUnitRandom o, IList<object> objMap)
        {
            if (WriteEval(writer, o, objMap) == false)
                return;

            writer.Write(o.InitialSeed);
        }
        #endregion

        #region Write EasingCurve derived classes
        private static void Write(AssetStreamWriter writer, LinearCurve o, IList<object> objMap) { WriteEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseInQuadraticCurve o, IList<object> objMap) { WriteEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseOutQuadraticCurve o, IList<object> objMap) { WriteEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseInOutQuadraticCurve o, IList<object> objMap) { WriteEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseInCubicCurve o, IList<object> objMap) { WriteEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseOutCubicCurve o, IList<object> objMap) { WriteEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseInOutCubicCurve o, IList<object> objMap) { WriteEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseInQuarticCurve o, IList<object> objMap) { WriteEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseOutQuarticCurve o, IList<object> objMap) { WriteEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseInOutQuarticCurve o, IList<object> objMap) { WriteEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseInQuinticCurve o, IList<object> objMap) { WriteEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseOutQuinticCurve o, IList<object> objMap) { WriteEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseInOutQuinticCurve o, IList<object> objMap) { WriteEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseInSinusoidalCurve o, IList<object> objMap) { WriteEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseOutSinusoidalCurve o, IList<object> objMap) { WriteEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseInOutSinusoidalCurve o, IList<object> objMap) { WriteEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseInExponentialCurve o, IList<object> objMap) { WriteEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseOutExponentialCurve o, IList<object> objMap) { WriteEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseInOutExponentialCurve o, IList<object> objMap) { WriteEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseInCircularCurve o, IList<object> objMap) { WriteEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseOutCircularCurve o, IList<object> objMap) { WriteEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseInOutCircularCurve o, IList<object> objMap) { WriteEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseInElasticCurve o, IList<object> objMap) { WriteElasticEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseOutElasticCurve o, IList<object> objMap) { WriteElasticEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, EaseInOutElasticCurve o, IList<object> objMap) { WriteElasticEasingCurve(writer, o, objMap); }
        private static void Write(AssetStreamWriter writer, OscillationCurve o, IList<object> objMap)
        {
            if (WriteEasingCurve(writer, o, objMap) == false)
                return;

            writer.Write((byte)o.Mode);
            writer.Write((short)o.Frequency);
            writer.Write(o.Strength);
        }
        #endregion
    }
}
