#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Module.h"

#include <memory>
using std::shared_ptr;
using std::weak_ptr; 
using std::make_shared;

extern const char* title;
const int W = 400;
const int H = 640;
const int BULLET_SPEED = 15;
const int BL = 15;

extern sf::RenderWindow *window;
extern Module* current_module;

// textures
namespace tex {
extern sf::Texture player;
extern sf::Texture enemy1;
extern sf::Texture enemy2;
extern sf::Texture enemy3;
extern sf::Texture enemy4;
extern sf::Texture bullet;
extern sf::Texture expl;
extern sf::Texture title;
extern sf::Texture ufo;
extern sf::Texture warn;
}

namespace se {
extern sf::SoundBuffer shoot;
extern sf::SoundBuffer explosion1;
extern sf::SoundBuffer explosion2;
extern sf::SoundBuffer explosion_l;
extern sf::SoundBuffer ref;
extern sf::SoundBuffer start;
extern sf::SoundBuffer sth;
extern sf::SoundBuffer warn;
}

namespace misc {
	extern sf::Font font;
}
#define PI 3.14159265
#define ROT_SPEED 0.12

inline int sgn(float x) {
	if (x < -1e-7) { return -1; }
	if (x > 1e-7) { return 1; }
	return 0;
}

inline void reg(float &x) {
	while (1) {
		if (x < -PI - 1e-7) x += 2 * PI;
		else if (x > PI + 1e-7) x -= 2 * PI;
		else break;
	}
}

inline float sqr(float x) { return x * x;  }

void PlaySoundEffect(sf::SoundBuffer& sb, int vol = 50);