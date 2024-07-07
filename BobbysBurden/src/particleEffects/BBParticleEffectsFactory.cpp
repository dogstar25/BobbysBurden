#include "BBParticleEffectsFactory.h"
#include "GameParticleEffects.h"


ParticleEffect BBParticleEffectsFactory::create(std::string particleType)
{
    ParticleEffect particleEffect;

    if (particleType == "spark") {

        particleEffect = ParticleEffects::spark;
    }
    else if (particleType == "fireFlame") {

        particleEffect = ParticleEffects::fireFlame;
    }
    else if (particleType == "fireFlame2") {

        particleEffect = ParticleEffects::fireFlame2;
    }

    else if (particleType == "rain") {

        particleEffect = ParticleEffects::rain;
    }


    else {
        particleEffect = ParticleEffectsFactory::create(particleType);
    }

    return particleEffect;
}
