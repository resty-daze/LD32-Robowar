#pragma once
#include "Common.h"

class MainGame;
class Player
{
public:
	Player();
	~Player();

	void Update();
	void Render();

	float GetX() const { return x_;  }
	float GetY() const { return y_;  }

	void SetPos(float x, float  y) {
		x_ = x;
		y_ = y;
	}

	bool Strong();

	void EnteringStatus() {
		status_ = 1;
	}

	void SetMainGame(MainGame* game) {
		game_ = game;
	}
	
	void GetFlapInfo(sf::Vector2<float>* midpoint, sf::Vector2<float>* dir_vec) {
		midpoint->x = line_x_;
		midpoint->y = line_y_;
		*dir_vec = line_vec_;
	}

private:
	int status_;
	float x_, y_;
	float flat_angle_;
	sf::Sprite self_;
	MainGame* game_;
	int cool_down_;

	float line_x_, line_y_;
	sf::Vector2<float> line_vec_;
	int strong_cnt_;
};

