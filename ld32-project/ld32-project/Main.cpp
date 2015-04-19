#include <Windows.h>

#include "Common.h"
#include "StartMenu.h"


Module* current_module;
sf::RenderWindow *window;
const char* title =  "Robowar";

int last_tick = 0;
int expect = 16;

void Update() {
	current_module->Update();
}

void Render() {
	current_module->Render();
}

namespace tex {
	sf::Texture player;
	sf::Texture enemy1;
	sf::Texture enemy2;
	sf::Texture enemy3;
	sf::Texture enemy4;
	sf::Texture bullet;
	sf::Texture expl;
	sf::Texture title;
	sf::Texture ufo;
	sf::Texture warn;
}

namespace se {
	sf::SoundBuffer shoot;
	sf::SoundBuffer explosion1;
	sf::SoundBuffer explosion2;
	sf::SoundBuffer explosion_l;
	sf::SoundBuffer start;
	sf::SoundBuffer sth;
	sf::SoundBuffer ref;
	sf::SoundBuffer warn;
}

namespace misc {
	sf::Font font;
}

void init() {
	window = new sf::RenderWindow(sf::VideoMode(W, H), title, sf::Style::Titlebar | sf::Style::Close);
	
	tex::player.loadFromFile("pic/self.png");
	tex::enemy1.loadFromFile("pic/enemy1.png");
	tex::enemy2.loadFromFile("pic/enemy2.png");
	tex::enemy3.loadFromFile("pic/enemy3.png");
	tex::enemy4.loadFromFile("pic/enemy4.png");
	tex::bullet.loadFromFile("pic/bullets.png");
	tex::expl.loadFromFile("pic/expl.png");
	tex::title.loadFromFile("pic/title.png");
	tex::ufo.loadFromFile("pic/ufo.png");
	tex::warn.loadFromFile("pic/warning.png");

	se::shoot.loadFromFile("se/shoot.wav");
	se::explosion1.loadFromFile("se/explosion1.wav");
	se::explosion2.loadFromFile("se/explosion2.wav");
	se::explosion_l.loadFromFile("se/explosion_long.wav");
	se::start.loadFromFile("se/start.wav");
	se::sth.loadFromFile("se/sth.wav");
	se::ref.loadFromFile("se/ref.wav");
	se::warn.loadFromFile("se/warning.wav");

	misc::font.loadFromFile("misc/FreeMono.ttf");

	current_module = new StartMenu;
}

#define WINSYS
#ifndef WINSYS
int main()
#else
int CALLBACK WinMain(
	_In_  HINSTANCE hInstance,
	_In_  HINSTANCE hPrevInstance,
	_In_  LPSTR lpCmdLine,
	_In_  int nCmdShow
	)
#endif

{

	try {

		init();
	
		sf::Clock clock_;
		while (window->isOpen())
		{
			sf::Event event;
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window->close();
			}

			if (clock_.getElapsedTime().asMicroseconds() < 16667) continue;
		
			clock_.restart();
			//expect = 33 - expect;
			Update();

			window->clear();
			Render();
			window->display();
		}
	}
	catch (std::exception& e) {
		printf("err: %s\n", e.what());
	}

	return 0;
}

static const int MAX_CHANNEL = 16;
sf::Sound snds[MAX_CHANNEL];
void PlaySoundEffect(sf::SoundBuffer& sb, int vol) {
	for (int i = 0; i < MAX_CHANNEL; ++i) {
		if (snds[i].getStatus() == sf::SoundSource::Stopped) {
			snds[i].setBuffer(sb);
			snds[i].setVolume(vol);
			snds[i].play();
		}
	}
}