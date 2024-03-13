#pragma once
#include "MobyDick.h"
#include <queue>

enum class LightningStrikeType {

	FAR_BACK,
	MID_BACK,
	FRONT,
	

};

enum class ThunderType {

	RUMBLE_1,
	RUMBLE_2,
	RUMBLE_3,
	BOOM_1,
	BOOM_2

};

enum class RainType {

	RAIN_MEDIUM_LOOP,
	RAIN_HEAVY_LOOP

};

enum class StormComponentType {

	LIGHTNING,
	THUNDER,
	WINDOW_FLASH,
	RAIN

};

struct stormComponent {

	std::optional<StormComponentType> stormComponentType;
	std::optional <ThunderType> thunderType;
	std::optional <RainType> rainType;
	std::optional <LightningStrikeType> lightningStrikeType;
	Timer durationTimer;

};

struct StormSequence{

	std::map < std::string, stormComponent> components;

};


const stormComponent stormCompDistantBeginning[] = {

	{ 
		.stormComponentType = StormComponentType::LIGHTNING, 
		.thunderType = std::nullopt, 
		.rainType = std::nullopt, 
		.lightningStrikeType = LightningStrikeType::FAR_BACK, 
		.durationTimer = Timer(0.2F)
	},
	{ 
		StormComponentType::RAIN, 
		std::nullopt, 
		RainType::
		RAIN_HEAVY_LOOP, 
		std::nullopt, 
		0.2F
	}

};

class BBEnvironmentComponent : public EnvironmentComponent
{

public:
	BBEnvironmentComponent(Json::Value definitionJSON);

	virtual void update() override;
	virtual void postInit() override;
	virtual void setParent(GameObject* gameObject) override;

protected:


private:

	bool m_isStorming{};

	Timer testLightningTimer{ 1.0, true };
	Timer testLightningTimer2{ 1.2, true };
	Timer testLightningTimer3{ 1.4, true };
	
	void _lightningStrike(LightningStrikeType lightningType, float seconds);
	void _rain(RainType rainType);

	std::queue<stormComponent> m_stormComponenets{};



	



	


};

