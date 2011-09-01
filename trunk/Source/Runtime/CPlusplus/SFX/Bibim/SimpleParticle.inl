namespace Bibim
{
    SimpleParticle::SimpleParticle(float lifespan,
                                   Vector3 position, Vector3 linearVelocity, Vector3 linearAcceleration,
                                   float rotation, float angularVelocity, float angularAcceleration,
                                   Vector2 scale, Vector2 strainVelocity, Vector2 strainAcceleration,
                                   Vector4 startTint, Vector4 endTint,
                                   const Sprite& spriteInstance)
                                   : Particle(lifespan, position, linearVelocity, Color(startTint)),
                                     LinearAcceleration(linearAcceleration),
                                     Rotation(rotation),
                                     AngularVelocity(angularVelocity),
                                     AngularAcceleration(angularAcceleration),
                                     Scale(scale),
                                     StrainVelocity(strainVelocity),
                                     StrainAcceleration(strainAcceleration),
                                     StartTint(startTint),
                                     EndTint(endTint),
                                     SpriteInstance(spriteInstance)
    {
    }
    
    SimpleParticle::~SimpleParticle()
    {
    }
}