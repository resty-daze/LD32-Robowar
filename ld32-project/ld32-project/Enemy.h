#pragma once
#include "Common.h"

class MainGame;

class Router {
public:
	virtual ~Router() {}
	virtual bool Update() = 0; // t for still alive, f for disappear
	virtual float GetX() const = 0;
	virtual float GetY() const = 0;
	virtual bool Strong() const = 0;
	virtual float Rotate() const { return 0; }
};

class Shooter {
public:
	virtual void Update(float x, float y, MainGame* game) = 0;
};

class Enemy {
public:
	Enemy(int hp, float size, const sf::Texture& texutre, const std::vector<sf::IntRect>& fs, shared_ptr<Router> router, shared_ptr<Shooter> shooter, bool hp_line = false);
	~Enemy();
	bool Update(); // t for alive, f for disappear
	void Render();

	void SetMainGame(MainGame* game) {
		game_ = game;
	}

	float GetX() const { return x_; }
	float GetY() const { return y_; }
	float GetSize() const { return size_;  }

	bool dead() const { return hp_ <= 0; }

	int hit(int damage) {
		if (!router_->Strong()) {
			hp_ -= damage; 
			if (hp_ < 0) hp_ = 0;
		}
		return hp_;
	}
private:
	shared_ptr<Router> router_;
	shared_ptr<Shooter> shooter_;
	float x_, y_, size_;
	sf::Sprite sprite_;
	MainGame* game_;

	int hp_;
	int max_hp_;
	std::vector<sf::IntRect> fs_;
	int curr_;
};