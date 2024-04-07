#pragma once
#include "MobyDick.h"

namespace EnvironmentEventType {

	inline constexpr int LIGHTNING_FLASH_BACK = 1;
	inline constexpr int LIGHTNING_FLASH_MIDDLE = 2;
	inline constexpr int LIGHTNING_FLASH_FRONT = 3;
	inline constexpr int LIGHTNING_BOLT_1_BACK = 4;
	inline constexpr int LIGHTNING_BOLT_1_MIDDLE = 5;
	inline constexpr int LIGHTNING_BOLT_1_FRONT = 6;

	inline constexpr int THUNDER_RUMBLE_1 = 10;
	inline constexpr int THUNDER_RUMBLE_2 = 11;
	inline constexpr int THUNDER_RUMBLE_3 = 12;
	inline constexpr int THUNDER_BOOM_1 = 13;
	inline constexpr int THUNDER_BOOM_2 = 14;

	inline constexpr int RAIN_LIGHT = 20;
	inline constexpr int RAIN_MEDIUM = 21;
	inline constexpr int RAIN_HEAVY = 22;

	inline constexpr int WINDDOW_FLASH = 30;

}

namespace enviornmentSequence {

	inline constexpr int APPROACHING_STORM = 0;
	inline constexpr int CLOSE_STORM = 1;
	inline constexpr int ACTIVE_STORM = 2;
	inline constexpr int STORM_LEAVING = 3;
	inline constexpr int PEACFULL = 4;

	inline constexpr int CYCLE_COUNT = 5;
}

int enviornmentSequenceRepeat[]{

	2,	//APPROACHING_STORM
	5	//CLOSE_STORM

};

int enviornmentSequenceRepeatCount[enviornmentSequence::CYCLE_COUNT];

EnvironmentEvent stormCycleDistantApproaching[] = {

	{ EnvironmentEventType::WAIT_EVENT, Timer(2.0F) },
	{ EnvironmentEventType::LIGHTNING_FLASH_BACK, Timer(0.1F, true) },
	{ EnvironmentEventType::WAIT_EVENT, Timer(2.0F) },
	{ EnvironmentEventType::LIGHTNING_FLASH_BACK, Timer(0.5F)},
	{ EnvironmentEventType::WAIT_EVENT, Timer(0.1F) },
	{ EnvironmentEventType::LIGHTNING_FLASH_BACK, Timer(2.2F)},
	{ EnvironmentEventType::WAIT_EVENT, Timer(0.1F) },
	{ EnvironmentEventType::LIGHTNING_FLASH_BACK, Timer(0.2F)},
	{ EnvironmentEventType::THUNDER_RUMBLE_1, Timer(0.0F)},
	{ EnvironmentEventType::LIGHTNING_FLASH_BACK, Timer(0.4F) },
	{ EnvironmentEventType::WAIT_EVENT, Timer(0.1F) },
	{ EnvironmentEventType::LIGHTNING_FLASH_BACK, Timer(0.3F) },
	{ EnvironmentEventType::RAIN_LIGHT, Timer(0.3F) }

};

EnvironmentEvent stormCycleCloseStorm[] = {
	{ EnvironmentEventType::LIGHTNING_FLASH_MIDDLE, Timer(0.5F)},
	{ EnvironmentEventType::THUNDER_RUMBLE_2, Timer(0.0F)},
	{ EnvironmentEventType::WAIT_EVENT, Timer(2.1F) },
	{ EnvironmentEventType::LIGHTNING_FLASH_BACK, Timer(2.2F)},
};

