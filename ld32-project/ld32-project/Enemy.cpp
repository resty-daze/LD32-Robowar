#include "Enemy.h"
#include "MainGame.h"

Enemy::Enemy(int hp, float size, const sf::Texture& texture, const std::vector<sf::IntRect>& fs, shared_ptr<Router> router, shared_ptr<Shooter> shooter, bool hp_line)
 	: router_(router), shooter_(shooter), sprite_(texture), fs_(fs), size_(size), hp_(hp) {
	curr_ = 0;
	sprite_.setOrigin(size / 2, size / 2);
	x_ = -100;
	y_ = -100;
	if (hp_line) {
		max_hp_ = hp;
	}
	else {
		max_hp_ = 0;
	}
}

Enemy::~Enemy() {
}

bool Enemy::Update() {
	if (dead()) {
		game_->AddEffects(make_shared<ExplosionEffect>(x_, y_));
		if (size_ < 80) {
			PlaySoundEffect(se::explosion2, 2);
		}
		else {
			PlaySoundEffect(se::explosion_l, 4);
		}
	}

	if (dead() || !router_->Update()) {
		return false;
	}
	x_ = router_->GetX();
	y_ = router_->GetY();
	shooter_->Update(x_, y_, game_);
	return true;
}


void Enemy::Render() {
	sprite_.setPosition(x_ , y_ );
	sprite_.setTextureRect(fs_[curr_ / 4]);
	sprite_.setRotation(router_->Rotate());
	window->draw(sprite_);

	curr_ += 1;
	if (curr_ / 4 >= fs_.size()) { curr_ = 0; }

	if (max_hp_ > 0 && hp_ < max_hp_) {
		// show hp bar
		sf::RectangleShape rect(sf::Vector2f(250.0 / max_hp_ * hp_, 15));
		rect.setPosition(75, 60);
		rect.setFillColor(sf::Color(145, 255, 145));
		window->draw(rect);
	}
}
