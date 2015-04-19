#pragma once
#include "Module.h"
#include "Common.h"

class StartMenu :
	public Module
{
public:
	StartMenu();
	~StartMenu();

	void Update();
	void Render();

private:
	sf::Sprite bg_;
	sf::Sound se_;
	sf::Text hint_;
	bool pre;
	bool show_;
	int cnt_;
};

