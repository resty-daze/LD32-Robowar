#pragma once

#include <SFML/Graphics.hpp>

class Effect {
public:
	virtual ~Effect() {}
	virtual bool Update() = 0;
	virtual void Render() = 0;
};

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
	float x_, y_;
};