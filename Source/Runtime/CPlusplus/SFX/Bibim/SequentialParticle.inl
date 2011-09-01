namespace Bibim
{
    SequentialParticle::SequentialParticle(float lifespan, Vector3 position, int spriteSequenceIndex)
        : Particle(lifespan, position),
          Rotation(0.0f),
          Scale(Vector2::One),
          SpriteInstance(),
          SpriteSequenceIndex(spriteSequenceIndex),
          LastLinearVelocityKeyrameIndex(-2),
          LastRotationKeyframeIndex(-2),
          LastScaleKeyframeIndex(-2),
          LastTintKeyframeIndex(-2),
          LastSpriteKeyframeIndex(-2)
    {
    }
    
    SequentialParticle::~SequentialParticle()
    {
    }
}