#include "Effects.h"
#include "Common.h"

/*
class WarningEffect : public Effect {
public:
	WarningEffect();
	bool Update() override;
	void Render() override;
private:
	sf::Sprite s_;
	int cnt_;
};

class ExplosionEffect : public Effect {
public:
	ExplosionEffect(float x, float y);
	bool Update() override;
	void Render() override;
private:
	sf::Sprite s_;
	int cnt_;
};
*/

WarningEffect::WarningEffect() 
	: s_(tex::warn) {
	cnt_ = 300;
}

bool WarningEffect::Update() {
	return --cnt_ > 0;
}

void WarningEffect::Render() {
	window->draw(s_);
}

ExplosionEffect::ExplosionEffect(float x, float y) 
 : s_(tex::expl) {
	x_ = x;
	y_ = y;
	cnt_ = -1;
	s_.setPosition(x_ - 16, y_ - 16);
}

bool ExplosionEffect::Update() {
	cnt_++;
	return cnt_ <= 8;
}

void ExplosionEffect::Render() {
	s_.setTextureRect(sf::IntRect(32 * cnt_, 0, 32, 32));
	window->draw(s_);
}