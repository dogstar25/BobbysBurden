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
		.forceMax = 0.1F,
		.lifetimeMin = 0.2F,
		.lifetimeMax = 1.5F,
		.alphaFade = true,
		.angleMin = 90,
		.angleMax = 90,
		.particleSizeMin = 5.F,
		.particleSizeMax = 35.F,
		.colorRangeBegin = {255,0,0,255},
		.colorRangeEnd = {255,255,0,255},
		.particleSpawnCountMin = 10,
		.particleSpawnCountMax = 20
	};

	//static const ParticleEffect rain = {
	//	.poolId = "RAIN_SHEET_PARTICLE_POOL",
	//	//.poolId = "ROUND_PARTICLE_POOL",
	//	.originMin = {-100,2845},
	//	.originMax = {-100,2845},
	//	.forceMin = 61.2F,
	//	//.forceMax = 20.0F,
	//	.lifetimeMin = 3.0F,
	//	.lifetimeMax = 3.0F,
	//	.alphaFade = false,
	//	.angleMin = 75,
	//	.angleMax = 75,
	//	.particleSizeMin = 2000.F,
	//	.particleSizeMax = 2000.F,
	//	.colorRangeBegin = {255,255,255,100},
	//	.colorRangeEnd = {255,255,255,200},
	//	.particleSpawnCountMin = 1,
	//	.particleSpawnCountMax = 1
	//};

	static const ParticleEffect rain = {
		//.poolId = "RAIN_SHEET_PARTICLE_POOL",
		.poolId = "RAIN_DROP_PARTICLE_POOL",
		.originMin = {-500,3890},
		.originMax = {3000,5000},
		.forceMin = 100.2F,
		.forceMax = 120.0F,
		.lifetimeMin = 1.0F,
		.lifetimeMax = 3.0F,
		.alphaFade = false,
		.angleMin = 42,
		.angleMax = 47,
		.particleSizeMinWidth = 10.F,
		.particleSizeMaxWidth = 10.F,
		.particleSizeMinHeight = 20.F,
		.particleSizeMaxHeight = 90.F,
		.colorRangeBegin = {255,255,255,100},
		.colorRangeEnd = {255,255,255,200},
		.particleSpawnCountMin = 200,
		.particleSpawnCountMax = 500
	};

}
