namespace Bibim
{
    Particle::Particle()
        : Age(0.0f),
          Lifespan(0.0f),
          Position(Vector3::Zero),
          LinearVelocity(Vector3::Zero),
          Tint(Color(255, 255, 255, 255))
    {
    }

    Particle::Particle(float lifespan, Vector3 position)
        : Age(0.0f),
          Lifespan(lifespan),
          Position(position),
          LinearVelocity(Vector3::Zero),
          Tint(Color(255, 255, 255, 255))
    {
    }

    Particle::Particle(float lifespan, Vector3 position, Vector3 linearVelocity, Color tint)
        : Age(0.0f),
          Lifespan(lifespan),
          Position(position),
          LinearVelocity(linearVelocity),
          Tint(tint)
    {
    }

    Particle::~Particle()
    {
    }
}