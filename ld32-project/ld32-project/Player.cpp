#include "Player.h"
#include "MainGame.h"
#include <math.h>

double speed = 4.5;



Player::Player()
	: self_(tex::player, sf::IntRect(0, 0, 48, 48))
{
	x_ = y_ = 0;
	status_ = 0;
	game_ = nullptr;
	cool_down_ = 0;
	flat_angle_ = 0;
}


Player::~Player()
{
}

void Player::Update() 
{
	if (status_ == 1) {
		y_ -= 5.0;
		if (y_ < H - 120) {
			status_ = 0;
			strong_cnt_ = 60;
		}
		return;
	}

	if (strong_cnt_ > 0) {
		strong_cnt_--;
	}

	// slow mode
	bool slow_mode = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) || sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
		slow_mode = true;
	}

	// movement handle
	int dx = 0, dy = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		dx -= 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		dx += 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		dy -= 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		dy += 1;
	}

	float rate = slow_mode ? 0.5 : 1;
	if (dx != 0 && dy != 0) rate /= 1.4142;
	x_ += dx * speed * rate;
	y_ += dy * speed * rate;

	int mar = 15;
	if (x_ < mar) { x_ = mar; }
	if (y_ < mar) { y_ = mar; }
	if (x_ > W - mar) { x_ = W - mar; }
	if (y_ > H - mar) { y_ = H - mar; }

	// Shoot handle
	if (cool_down_ == 0) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
			game_->AddPlayerBullet(x_, y_ - 20);
			cool_down_ = 8;
		}
	}
	else {
		cool_down_ -= 1;
	}

	// blocker
	if (!slow_mode && (dx != 0 || dy != 0)) {
		float target_angle = atan2(dy, dx) + PI;
		float dt = target_angle - flat_angle_;
		reg(dt);
		if (abs(dt) > ROT_SPEED) {
			dt = sgn(dt) * ROT_SPEED;
			flat_angle_ += dt;
			reg(flat_angle_);
		}
		else {
			flat_angle_ = target_angle;
		}
	}

	float r = 30;
	line_x_ = x_ + r * cos(flat_angle_);
	line_y_ = y_ + r * sin(flat_angle_);

	line_vec_.x = cos(flat_angle_ - PI / 2);
	line_vec_.y = sin(flat_angle_ - PI / 2);
}

bool Player::Strong() {
	return status_ == 1 || strong_cnt_ > 0;
}

void Player::Render() 
{
	self_.setPosition(x_ - 24, y_ - 24);
	window->draw(self_);

	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(line_x_ + line_vec_.x * BL, line_y_ + line_vec_.y * BL)),
		sf::Vertex(sf::Vector2f(line_x_ - line_vec_.x * BL, line_y_ - line_vec_.y * BL))
	};

	window->draw(line, 2, sf::Lines);
}