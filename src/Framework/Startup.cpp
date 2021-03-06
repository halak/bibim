﻿#include <Bibim/Startup.h>
#include <Bibim/All.h>
#include <Bibim/CrashDump.h>

namespace Bibim
{
    void Startup::All()
    {
        CrashDump::Initialize();

        GameAssetFactory::AddEntry<EvalBoard>();
        GameAssetFactory::AddEntry<BoolSequence>();
        GameAssetFactory::AddEntry<ShortIntSequence>();
        GameAssetFactory::AddEntry<IntSequence>();
        GameAssetFactory::AddEntry<LongIntSequence>();
        GameAssetFactory::AddEntry<FloatSequence>();
        GameAssetFactory::AddEntry<DoubleSequence>(); 
        GameAssetFactory::AddEntry<ColorSequence>();
        GameAssetFactory::AddEntry<Point2Sequence>();
        GameAssetFactory::AddEntry<Point3Sequence>();
        GameAssetFactory::AddEntry<Point4Sequence>();
        GameAssetFactory::AddEntry<RectSequence>();
        GameAssetFactory::AddEntry<RectFSequence>();
        GameAssetFactory::AddEntry<Vector2Sequence>();
        GameAssetFactory::AddEntry<Vector3Sequence>();
        GameAssetFactory::AddEntry<Vector4Sequence>();
        GameAssetFactory::AddEntry<GameAssetSequence>();

        GameAssetFactory::AddEntry<Image>();
        GameAssetFactory::AddEntry<ImageSet>();
        GameAssetFactory::AddEntry<CCParticleSystem>();
        GameAssetFactory::AddEntry<CCParticleSystemSet>();
        GameAssetFactory::AddEntry<Sprite>();
        GameAssetFactory::AddEntry<SpriteSet>();
        GameAssetFactory::AddEntry<Script>();
        GameAssetFactory::AddEntry<BitMask>();
        GameAssetFactory::AddEntry<SourceTexture2D>();
        GameAssetFactory::AddEntry<ShaderEffect>();
        GameAssetFactory::AddEntry<UILayout>();
        GameAssetFactory::AddEntry<UIDocument::StyleSheet>();
        GameAssetFactory::SortEntries();

        GameComponentFactory::AddEntry<EvalBoolConstant>();
        GameComponentFactory::AddEntry<EvalShortIntConstant>();
        GameComponentFactory::AddEntry<EvalIntConstant>();
        GameComponentFactory::AddEntry<EvalLongIntConstant>();  
        GameComponentFactory::AddEntry<EvalFloatConstant>(); 
        GameComponentFactory::AddEntry<EvalDoubleConstant>();  
        GameComponentFactory::AddEntry<EvalColorConstant>(); 
        GameComponentFactory::AddEntry<EvalPoint2Constant>(); 
        GameComponentFactory::AddEntry<EvalPoint3Constant>(); 
        GameComponentFactory::AddEntry<EvalPoint4Constant>();   
        GameComponentFactory::AddEntry<EvalRectConstant>();  
        GameComponentFactory::AddEntry<EvalRectFConstant>();
        GameComponentFactory::AddEntry<EvalVector2Constant>();
        GameComponentFactory::AddEntry<EvalVector3Constant>();
        GameComponentFactory::AddEntry<EvalVector4Constant>();
        GameComponentFactory::AddEntry<EvalGameAssetConstant>();
        GameComponentFactory::AddEntry<EvalBoolVariable>();
        GameComponentFactory::AddEntry<EvalShortIntVariable>();
        GameComponentFactory::AddEntry<EvalIntVariable>();
        GameComponentFactory::AddEntry<EvalLongIntVariable>();  
        GameComponentFactory::AddEntry<EvalFloatVariable>(); 
        GameComponentFactory::AddEntry<EvalDoubleVariable>();  
        GameComponentFactory::AddEntry<EvalColorVariable>(); 
        GameComponentFactory::AddEntry<EvalPoint2Variable>(); 
        GameComponentFactory::AddEntry<EvalPoint3Variable>(); 
        GameComponentFactory::AddEntry<EvalPoint4Variable>();   
        GameComponentFactory::AddEntry<EvalRectVariable>();  
        GameComponentFactory::AddEntry<EvalRectFVariable>();
        GameComponentFactory::AddEntry<EvalVector2Variable>();
        GameComponentFactory::AddEntry<EvalVector3Variable>();
        GameComponentFactory::AddEntry<EvalVector4Variable>();
        GameComponentFactory::AddEntry<EvalGameAssetVariable>();
        GameComponentFactory::AddEntry<EvalBoolSequence>();
        GameComponentFactory::AddEntry<EvalShortIntSequence>();
        GameComponentFactory::AddEntry<EvalIntSequence>();
        GameComponentFactory::AddEntry<EvalLongIntSequence>();  
        GameComponentFactory::AddEntry<EvalFloatSequence>();
        GameComponentFactory::AddEntry<EvalDoubleSequence>();  
        GameComponentFactory::AddEntry<EvalColorSequence>(); 
        GameComponentFactory::AddEntry<EvalPoint2Sequence>(); 
        GameComponentFactory::AddEntry<EvalPoint3Sequence>(); 
        GameComponentFactory::AddEntry<EvalPoint4Sequence>();   
        GameComponentFactory::AddEntry<EvalRectSequence>();  
        GameComponentFactory::AddEntry<EvalRectFSequence>();
        GameComponentFactory::AddEntry<EvalVector2Sequence>();
        GameComponentFactory::AddEntry<EvalVector3Sequence>();
        GameComponentFactory::AddEntry<EvalVector4Sequence>();
        GameComponentFactory::AddEntry<EvalGameAssetSequence>(); 
        GameComponentFactory::AddEntry<EvalBoolRangedSequence>();
        GameComponentFactory::AddEntry<EvalShortIntRangedSequence>();
        GameComponentFactory::AddEntry<EvalIntRangedSequence>();
        GameComponentFactory::AddEntry<EvalLongIntRangedSequence>();
        GameComponentFactory::AddEntry<EvalFloatRangedSequence>();
        GameComponentFactory::AddEntry<EvalDoubleRangedSequence>();
        GameComponentFactory::AddEntry<EvalColorRangedSequence>();
        GameComponentFactory::AddEntry<EvalPoint2RangedSequence>();
        GameComponentFactory::AddEntry<EvalPoint3RangedSequence>();
        GameComponentFactory::AddEntry<EvalPoint4RangedSequence>();
        GameComponentFactory::AddEntry<EvalRectRangedSequence>();
        GameComponentFactory::AddEntry<EvalRectFRangedSequence>();
        GameComponentFactory::AddEntry<EvalVector2RangedSequence>();
        GameComponentFactory::AddEntry<EvalVector3RangedSequence>();
        GameComponentFactory::AddEntry<EvalVector4RangedSequence>();
        GameComponentFactory::AddEntry<EvalGameAssetRangedSequence>();
        GameComponentFactory::AddEntry<EvalShortIntInterpolator>();
        GameComponentFactory::AddEntry<EvalIntInterpolator>();
        GameComponentFactory::AddEntry<EvalLongIntInterpolator>();
        GameComponentFactory::AddEntry<EvalFloatInterpolator>();
        GameComponentFactory::AddEntry<EvalDoubleInterpolator>();
        GameComponentFactory::AddEntry<EvalColorInterpolator>();
        GameComponentFactory::AddEntry<EvalPoint2Interpolator>();
        GameComponentFactory::AddEntry<EvalPoint3Interpolator>();
        GameComponentFactory::AddEntry<EvalPoint4Interpolator>();
        GameComponentFactory::AddEntry<EvalVector2Interpolator>();
        GameComponentFactory::AddEntry<EvalVector3Interpolator>();
        GameComponentFactory::AddEntry<EvalVector4Interpolator>();
        GameComponentFactory::AddEntry<EvalBoolSelector>();
        GameComponentFactory::AddEntry<EvalShortIntSelector>();
        GameComponentFactory::AddEntry<EvalIntSelector>();
        GameComponentFactory::AddEntry<EvalLongIntSelector>();
        GameComponentFactory::AddEntry<EvalFloatSelector>();
        GameComponentFactory::AddEntry<EvalDoubleSelector>();
        GameComponentFactory::AddEntry<EvalColorSelector>();
        GameComponentFactory::AddEntry<EvalPoint2Selector>();
        GameComponentFactory::AddEntry<EvalPoint3Selector>();
        GameComponentFactory::AddEntry<EvalPoint4Selector>();
        GameComponentFactory::AddEntry<EvalRectSelector>();
        GameComponentFactory::AddEntry<EvalRectFSelector>();
        GameComponentFactory::AddEntry<EvalVector2Selector>();
        GameComponentFactory::AddEntry<EvalVector3Selector>();
        GameComponentFactory::AddEntry<EvalVector4Selector>();
        GameComponentFactory::AddEntry<EvalGameAssetSelector>();
        GameComponentFactory::AddEntry<EvalBoolCache>();
        GameComponentFactory::AddEntry<EvalShortIntCache>();
        GameComponentFactory::AddEntry<EvalIntCache>();
        GameComponentFactory::AddEntry<EvalLongIntCache>();
        GameComponentFactory::AddEntry<EvalFloatCache>();
        GameComponentFactory::AddEntry<EvalDoubleCache>();
        GameComponentFactory::AddEntry<EvalColorCache>();
        GameComponentFactory::AddEntry<EvalPoint2Cache>();
        GameComponentFactory::AddEntry<EvalPoint3Cache>();
        GameComponentFactory::AddEntry<EvalPoint4Cache>();
        GameComponentFactory::AddEntry<EvalRectCache>();
        GameComponentFactory::AddEntry<EvalRectFCache>();
        GameComponentFactory::AddEntry<EvalVector2Cache>();
        GameComponentFactory::AddEntry<EvalVector3Cache>();
        GameComponentFactory::AddEntry<EvalVector4Cache>();
        GameComponentFactory::AddEntry<EvalShortIntToIntCast>(); 
        GameComponentFactory::AddEntry<EvalLongIntToIntCast>();  
        GameComponentFactory::AddEntry<EvalIntToFloatCast>();    
        GameComponentFactory::AddEntry<EvalDoubleToFloatCast>(); 
        GameComponentFactory::AddEntry<EvalBoolNegation>();      
        GameComponentFactory::AddEntry<EvalIntNegation>();       
        GameComponentFactory::AddEntry<EvalFloatNegation>();     
        GameComponentFactory::AddEntry<EvalPoint2Negation>();    
        GameComponentFactory::AddEntry<EvalPoint3Negation>();    
        GameComponentFactory::AddEntry<EvalPoint4Negation>();
        GameComponentFactory::AddEntry<EvalVector2Negation>();
        GameComponentFactory::AddEntry<EvalVector3Negation>();   
        GameComponentFactory::AddEntry<EvalVector4Negation>();
        GameComponentFactory::AddEntry<EvalBoolAND>();
        GameComponentFactory::AddEntry<EvalBoolOR>();
        GameComponentFactory::AddEntry<EvalIntAddition>();
        GameComponentFactory::AddEntry<EvalIntSubtraction>();
        GameComponentFactory::AddEntry<EvalIntMultiplication>();
        GameComponentFactory::AddEntry<EvalIntDivision>();
        GameComponentFactory::AddEntry<EvalIntModulus>();
        GameComponentFactory::AddEntry<EvalFloatAddition>();
        GameComponentFactory::AddEntry<EvalFloatSubtraction>();
        GameComponentFactory::AddEntry<EvalFloatMultiplication>();
        GameComponentFactory::AddEntry<EvalFloatDivision>();
        GameComponentFactory::AddEntry<EvalFloatModulus>();
        GameComponentFactory::AddEntry<EvalPoint2Addition>();
        GameComponentFactory::AddEntry<EvalPoint2Subtraction>();
        GameComponentFactory::AddEntry<EvalPoint2Multiplication>();
        GameComponentFactory::AddEntry<EvalPoint2Division>();
        GameComponentFactory::AddEntry<EvalPoint3Addition>();
        GameComponentFactory::AddEntry<EvalPoint3Subtraction>();
        GameComponentFactory::AddEntry<EvalPoint3Multiplication>();
        GameComponentFactory::AddEntry<EvalPoint3Division>();
        GameComponentFactory::AddEntry<EvalPoint4Addition>();
        GameComponentFactory::AddEntry<EvalPoint4Subtraction>();
        GameComponentFactory::AddEntry<EvalPoint4Multiplication>();
        GameComponentFactory::AddEntry<EvalPoint4Division>();
        GameComponentFactory::AddEntry<EvalVector2Addition>();
        GameComponentFactory::AddEntry<EvalVector2Subtraction>();
        GameComponentFactory::AddEntry<EvalVector2Multiplication>();
        GameComponentFactory::AddEntry<EvalVector2Division>();
        GameComponentFactory::AddEntry<EvalVector3Addition>();
        GameComponentFactory::AddEntry<EvalVector3Subtraction>();
        GameComponentFactory::AddEntry<EvalVector3Multiplication>();
        GameComponentFactory::AddEntry<EvalVector3Division>();
        GameComponentFactory::AddEntry<EvalVector4Addition>();
        GameComponentFactory::AddEntry<EvalVector4Subtraction>();
        GameComponentFactory::AddEntry<EvalVector4Multiplication>();
        GameComponentFactory::AddEntry<EvalVector4Division>();
        GameComponentFactory::AddEntry<EvalUnitRandom>();
        GameComponentFactory::AddEntry<EvalTimeflow>();

        GameComponentFactory::AddSingletonEntry<LinearCurve>();
        GameComponentFactory::AddSingletonEntry<EaseInQuadraticCurve>();
        GameComponentFactory::AddSingletonEntry<EaseOutQuadraticCurve>();
        GameComponentFactory::AddSingletonEntry<EaseInOutQuadraticCurve>();
        GameComponentFactory::AddSingletonEntry<EaseInCubicCurve>();
        GameComponentFactory::AddSingletonEntry<EaseOutCubicCurve>();
        GameComponentFactory::AddSingletonEntry<EaseInOutCubicCurve>();
        GameComponentFactory::AddSingletonEntry<EaseInQuarticCurve>();
        GameComponentFactory::AddSingletonEntry<EaseOutQuarticCurve>();
        GameComponentFactory::AddSingletonEntry<EaseInOutQuarticCurve>();
        GameComponentFactory::AddSingletonEntry<EaseInQuinticCurve>();
        GameComponentFactory::AddSingletonEntry<EaseOutQuinticCurve>();
        GameComponentFactory::AddSingletonEntry<EaseInOutQuinticCurve>();
        GameComponentFactory::AddSingletonEntry<EaseInSinusoidalCurve>();
        GameComponentFactory::AddSingletonEntry<EaseOutSinusoidalCurve>();
        GameComponentFactory::AddSingletonEntry<EaseInOutSinusoidalCurve>();
        GameComponentFactory::AddSingletonEntry<EaseInExponentialCurve>();
        GameComponentFactory::AddSingletonEntry<EaseOutExponentialCurve>();
        GameComponentFactory::AddSingletonEntry<EaseInOutExponentialCurve>();
        GameComponentFactory::AddSingletonEntry<EaseInCircularCurve>();
        GameComponentFactory::AddSingletonEntry<EaseOutCircularCurve>();
        GameComponentFactory::AddSingletonEntry<EaseInOutCircularCurve>();
        GameComponentFactory::AddEntry<EaseInElasticCurve>();
        GameComponentFactory::AddEntry<EaseOutElasticCurve>();
        GameComponentFactory::AddEntry<EaseInOutElasticCurve>();
        GameComponentFactory::AddEntry<OscillationCurve>();
        
        GameComponentFactory::AddEntry<UIAfterImageEffect>();
        GameComponentFactory::AddEntry<UISineCurveEffect>();
        GameComponentFactory::AddEntry<UITintEffect>();
        GameComponentFactory::AddEntry<UIBlendingEffect>();
        GameComponentFactory::AddEntry<UIColorMatrixEffect>();
        GameComponentFactory::AddEntry<UIOpacityMaskEffect>();
        GameComponentFactory::AddEntry<UIEffectMap>();
        GameComponentFactory::AddEntry<UIFunctionEventHandler>();
        GameComponentFactory::AddEntry<UISequentialEventHandler>();
        GameComponentFactory::AddEntry<UIEventMap>();
        GameComponentFactory::AddEntry<UILabel>();
        GameComponentFactory::AddEntry<UIEditText>();
        GameComponentFactory::AddEntry<UIPanel>();
        GameComponentFactory::AddEntry<UIDocument>();
        GameComponentFactory::AddEntry<UIButton>();
        GameComponentFactory::AddEntry<UICheckBox>();
        GameComponentFactory::AddEntry<UIRadioButton>();
        GameComponentFactory::AddEntry<UIScrollablePanel>();
        GameComponentFactory::AddEntry<UIWindow>();
        GameComponentFactory::AddEntry<UIImage>();
        GameComponentFactory::AddEntry<UISprite>();
        GameComponentFactory::AddEntry<UIVideo>();
        GameComponentFactory::AddEntry<UIRect>();
        GameComponentFactory::AddEntry<UIRoundedRect>();
        GameComponentFactory::AddEntry<UIEllipse>();
        GameComponentFactory::SortEntries();

        Key::Setup();
    }
}