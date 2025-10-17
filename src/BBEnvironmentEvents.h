#pragma once
#include "MobyDick.h"

namespace EnvironmentEventType {

	inline constexpr int LIGHTNING_MAKER = 10;
}


namespace EnvironmentEventId {

	inline constexpr int LIGHTNING_FLASH_BACK = 2;
	inline constexpr int LIGHTNING_FLASH_MIDDLE = 3;
	inline constexpr int LIGHTNING_FLASH_FRONT = 4;
	inline constexpr int LIGHTNING_BOLT_1_BACK = 5;
	inline constexpr int LIGHTNING_BOLT_1_MIDDLE = 6;
	inline constexpr int LIGHTNING_BOLT_1_FRONT = 7;

	inline constexpr int THUNDER_RUMBLE_1 = 11;
	inline constexpr int THUNDER_RUMBLE_2 = 12;
	inline constexpr int THUNDER_RUMBLE_3 = 13;
	inline constexpr int THUNDER_BOOM_1 = 14;
	inline constexpr int THUNDER_BOOM_2 = 15;

	inline constexpr int RAIN_LIGHT = 21;
	inline constexpr int RAIN_MEDIUM = 22;
	inline constexpr int RAIN_HEAVY = 23;

	inline constexpr int WINDOW_FLASH = 30;

	inline constexpr int LIGHTING_MAKER_DISTANT = 40;
	inline constexpr int LIGHTING_MAKER_LIGHT = 41;
	inline constexpr int LIGHTING_MAKER_MEDIUM = 42;
	inline constexpr int LIGHTING_MAKER_HEAVY = 43;

	inline constexpr int APPROACHING_STORM_TRACK = 50;
	inline constexpr int LIGHT_STORM_TRACK = 51;
	inline constexpr int HEAVY_STORM_TRACK = 52;
	inline constexpr int LEAVING_STORM_TRACK = 53;

	inline constexpr int PEACEFULL_1_TRACK = 60;

}

namespace EnvironmentSequence {

	inline constexpr int STORM_1 = 0;
	inline constexpr int STORM_2 = 1;
	inline constexpr int PEACFULL_1 = 2;
	inline constexpr int PEACFULL_2 = 3;
	inline constexpr int RAIN_1 = 4;
	inline constexpr int RAIN_2 = 5;

	inline constexpr int CYCLE_COUNT = 6;
}

std::vector <std::vector<EnvironmentEventInstruction>> environmentCycle = {

	{ //Approaching Storm
		{ "soundLoop", "APPROACHING_STORM", Timer(60.0f)},
		{ "lightningMaker", EventLevel::MILD, Timer(60.0f)}
	},
	{ //Near Storm
		{ "soundLoop", "NEAR_STORM", Timer(60.0f)},
		{ "lightningMaker", EventLevel::MODERATE, Timer(60.0f)},
		{ "rainEvent", EventLevel::MILD, Timer(60.0f) }
	},
	{ //Heavy Storm
		{ "soundLoop", "HEAVY_STORM", Timer(60.0f)},
		{ "lightningMaker", EventLevel::INTENSE, Timer(60.0f)},
		{ "rainEvent", EventLevel::MODERATE, Timer(60.0f) }
	},
	{ //Heavy Storm
		{ "soundLoop", "HEAVY_STORM", Timer(60.0f)},
		{ "lightningMaker", EventLevel::INTENSE, Timer(60.0f)},
		{ "rainEvent", EventLevel::INTENSE, Timer(60.0f) }
	},
	{ //Near Storm 2
		{ "soundLoop", "NEAR_STORM", Timer(60.0f)},
		{ "lightningMaker", EventLevel::MILD, Timer(60.0f)},
		{ "rainEvent", EventLevel::MILD, Timer(60.0f) }
	},
	{ //leaving Storm
		{ "soundLoop", "APPROACHING_STORM", Timer(60.0f) },
		{ "lightningMaker", EventLevel::MILD, Timer(60.0f)}
	},

};

//EnvironmentEventAction peacefull1Cycle[] = {
//
//	{ EnvironmentEventType::PEACEFULL_1_TRACK, Timer(120.0F) },
//
//};

