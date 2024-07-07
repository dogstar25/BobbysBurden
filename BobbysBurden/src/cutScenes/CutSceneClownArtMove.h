#pragma once
#include "MobyDick.h"

class CutSceneClownArtMove : public CutScene
{

public:
	void run(Scene* scene) override;
	void start() override;
	void update() override;
	void end() override;

private:

	int m_currentAct{ 1 };
	int m_numberOfActs{ 1 };

	static inline std::optional<SDL_FPoint> _targetLocation{};

	std::weak_ptr<GameObject> _player;
	std::weak_ptr<GameObject> _clownArtObject;
	Timer scene1Timer{};


};
