#pragma once
#include "Module.h"
#include "Common.h"

class GameEnding :
	public Module
{
public:
	GameEnding(const char* reason, int score, int multiple, int seconds);
	~GameEnding();

	void Update();
	void Render();
private:
	sf::Text tr_, ts_, tm_, tt_;
	bool pre;
};

