#include "GameEnding.h"
#include "StartMenu.h"
#include <sstream>

GameEnding::GameEnding(const char* reason, int score, int multiple, int seconds)
{
	tr_.setFont(misc::font);
	tr_.setScale(0.8, 0.8);
	tr_.setString(reason);
	tr_.setPosition(10, 100);

	ts_.setFont(misc::font);
	ts_.setScale(1, 1);
	std::stringstream ss;
	ss << "SCORE: " << score;
	ts_.setString(ss.str());
	ts_.setPosition(10, 130);
	ts_.setColor(sf::Color(175, 175, 255));
    
	tm_.setFont(misc::font);
	tm_.setScale(0.7, 0.7);
	std::stringstream s2;
	s2 << "x" << multiple;
	tm_.setString(s2.str());
	tm_.setPosition(10, 180);
	tm_.setColor(sf::Color(175, 255, 175));

	tt_.setFont(misc::font);
	tt_.setScale(0.6, 0.6);
	int m = seconds / 60;
	int s = seconds % 60;
	char buf[64];
	sprintf_s(buf, "Time used: %d:%02d", m, s);
	tt_.setString(buf);;
	tt_.setPosition(10, 220);

	pre = false;
}


GameEnding::~GameEnding()
{
}

void GameEnding::Update() 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::J) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		if (pre)  {
			current_module = new StartMenu;
			delete this;
		}
	}
	else {
		pre = true;
	}
}

void GameEnding::Render() 
{
	window->draw(tr_);
	window->draw(ts_);
	window->draw(tm_);
	window->draw(tt_);
}
