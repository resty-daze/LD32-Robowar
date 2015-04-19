#pragma once

#include "Common.h"

class BackGround
{
public:
	BackGround();
	~BackGround();

	void Update();
	void Render();
private:
	sf::CircleShape cs_[5];

	struct Star {
		float x, y;
		float vy;
		float bri;
		float r;
		int level;
	};

	std::vector<Star> stars_;
};

