#pragma once


namespace ParticleEffects {


	static const ParticleEffect spark = {
		.poolId = "ROUND_LIT_PARTICLE_POOL",
		.originMin = {0,0},
		.originMax = {0,0},
		.forceMin = 0.F,
		.forceMax = 0.1F,
		.lifetimeMin = 0.5F,
		.lifetimeMax = 3.5F,
		.alphaFade = true,
		.angleMin = 70,
		.angleMax = 125,
		.particleSizeMin = 4.F,
		.particleSizeMax = 8.F,
		.colorRangeBegin = {255,255,255,255},
		.colorRangeEnd = {255,255,255,255},
		.particleSpawnCountMin = 0,
		.particleSpawnCountMax = 5
	};

	static const ParticleEffect fireFlame = {
		.poolId = "ROUND_PARTICLE_POOL",
		.originMin = {0,0},
		.originMax = {0,0},
		.forceMin = 0.F,
		.forceMax = 0.1,
		.lifetimeMin = 0.2F,
		.lifetimeMax = 1.5F,
		.alphaFade = true,
		.angleMin = 90,
		.angleMax = 90,
		.particleSizeMin = 1.F,
		.particleSizeMax = 35.F,
		.colorRangeBegin = {255,0,0,255},
		.colorRangeEnd = {255,255,0,255},
		.particleSpawnCountMin = 10,
		.particleSpawnCountMax = 20
	};

}
