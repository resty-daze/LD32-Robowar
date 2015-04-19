#include "StartMenu.h"
#include "MainGame.h"

StartMenu::StartMenu()
	: bg_(tex::title), hint_("Press Z or J...", misc::font) {
	hint_.setPosition(80, 200);
	pre = false;
	show_ = true;
	cnt_ = 0;
}


StartMenu::~StartMenu()
{
}

void StartMenu::Update() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::J) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		if (pre)  {
			MainGame* main_game = new MainGame;
			main_game->Init();
			main_game->Update();
			current_module = main_game;
			delete this;
		}
	}
	else {
		pre = true;
	}

	if (++cnt_ >= 45) {
		cnt_ = 0;
		show_ = !show_;
	}
}

void StartMenu::Render() {
	window->draw(bg_); 
	if (show_) {
		window->draw(hint_);
	}
}