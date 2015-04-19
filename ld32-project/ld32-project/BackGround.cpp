#include "BackGround.h"


const int str_nums[] = { 30, 16, 12, 8, 8 };

BackGround::BackGround()
{
	for (int i = 0; i < 5; ++i) {
		for (int n = 0; n < str_nums[i]; ++n) {
			Star star;
			star.bri = rand() % (i * 3 + 5) / 25.0;
			star.x = rand() % W;
			star.y = rand() % H;
			star.vy = 0.1 * (i + 2) * (0.8 + rand() % 10 / 100.0);
			star.r = (rand() % 50 / 100.0 + 1.5) * (i + 5) / 10;
			star.level = i;
			stars_.push_back(star); 
		}
	}
}


BackGround::~BackGround()
{
}

void BackGround::Update() {
	for (auto& s : stars_) {
		s.y += s.vy;
		if (s.y > H + 10) {
			s.x = rand() % W;
			s.y = rand() % 10 - 20;
		}
	}
}

void BackGround::Render() {
	for (auto& s : stars_) {
		cs_[s.level].setPosition(s.x, s.y);
		int c = 255 * s.bri;
		cs_[s.level].setFillColor(sf::Color(c, c, c));
		cs_[s.level].setRadius(s.r);
		window->draw(cs_[s.level]);
	}
}