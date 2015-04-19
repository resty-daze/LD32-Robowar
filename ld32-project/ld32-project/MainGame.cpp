#include "MainGame.h"
#include "GameEnding.h"

MainGame::MainGame()
	: player_bullet_(tex::bullet, sf::IntRect(96, 0, 32, 32)), enemy_bullet_(tex::bullet)
{
	player_.SetMainGame(this);
	level_.SetMainGame(this);
	player_bullet_sound_.setBuffer(se::shoot);
	player_bullet_sound_.setVolume(20);
	player_hit_sound_.setBuffer(se::sth);
	player_hit_sound_.setVolume(12);
	ref_sound_.setBuffer(se::ref);
	ref_sound_.setVolume(20);

	tlife_.setFont(misc::font);
	tlife_.setPosition(5, 20);
	tlife_.setColor(sf::Color(128, 128, 254));
	
	tscore_.setFont(misc::font);
	tscore_.setPosition(5, 5);
	tscore_.setScale(0.8, 0.8);

	tmultiple_.setFont(misc::font);
	tmultiple_.setPosition(5, 50);
	tmultiple_.setScale(0.6, 0.6);
	tmultiple_.setColor(sf::Color(128, 255, 128));
}


MainGame::~MainGame()
{
}

void MainGame::Init() {
	player_.SetPos(W / 2, H);
	player_.EnteringStatus();

	level_.Init();
	miss_count_ = 0;
	life_ = 5;

	score_ = 0;
	multiple_ = 50;

	clock_.restart();

	bgm_.openFromFile("bgm/1.ogg");
	bgm_.setLoop(true);
	bgm_.play();
}

void MainGame::Update() {
	bg_.Update();
	player_.Update();
	UpdateEnemies();
	UpdatePlayerBullets();
	UpdateEnemyBullets();
	UpdateEffects();

	level_.Update();

	if (fading_) {
		bgm_.setVolume(bgm_.getVolume() - 0.1);
	}
}

void MainGame::Render() {
	bg_.Render();
	level_.Render();

	for (auto& p : player_bullets_) {
		player_bullet_.setPosition(p.x - 16, p.y - 16);
		window->draw(player_bullet_);
	}

	player_.Render();

	for (auto& e : enemies_) {
		e->Render();
	}

	RenderEffects();
	RenderEnemyBullets();
}

void MainGame::EndGame(const char* reason) {
	current_module = new GameEnding(reason, score_, multiple_, clock_.getElapsedTime().asSeconds());
	delete this;
}

void MainGame::AddPlayerBullet(float x, float y) {
	player_bullets_.push_back(sf::Vector2<float>(x, y));
	player_bullet_sound_.play();
}

void MainGame::AddEnemy(shared_ptr<Enemy> enemy) {
	enemies_.push_back(enemy);
	enemy->SetMainGame(this);
}

void MainGame::AddEnemyBullet(int type, float x, float y, float dx, float dy, float ddx, float ddy, bool no_flap) {
	EnemyBullet bullet;
	bullet.type = type;
	bullet.mode = no_flap ? 2 : 0;
	bullet.x = x;
	bullet.y = y;
	bullet.dx = dx;
	bullet.dy = dy;
	bullet.ddx = ddx;
	bullet.ddy = ddy;
	bullet.da = 0;
	enemy_bullets_.push_back(bullet);
}

void MainGame::AddEffects(shared_ptr<Effect> effect) {
	effects_.push_back(effect);
}

void MainGame::HitPlayer() {
	if (!player_.Strong()) {
		player_.SetPos(W / 2, H + 60);
		player_.EnteringStatus();

		miss_count_ += 1;
		life_ -= 1;
		multiple_ *= 0.8;

		player_hit_sound_.play();
	}

	if (life_ <= 0) {
		EndGame("You lost all your life.");
	}
}

void MainGame::UpdatePlayerBullets() {
	int pre = 0;
	for (size_t i = 0; i < player_bullets_.size(); ++i) {
		auto&p = player_bullets_[i];
		p.y -= BULLET_SPEED;
		if (p.y < -10) { continue; }

		bool skip = false;
		for (auto& e : enemies_) {
			if (!e->dead()) {
				if (sqr(p.x - e->GetX()) + sqr(p.y - e->GetY()) < sqr(e->GetSize() / 2 + 8)) {
					e->hit(2);
					if (e->dead()) {
						score_ += multiple_;
					}
					skip = true;
					break;
				}
			}
		}
		if (skip) { continue; }

		player_bullets_[pre++] = player_bullets_[i];
	}
	player_bullets_.resize(pre);
}

void MainGame::UpdateEnemies() {
	int pre = 0;
	for (size_t i = 0; i < enemies_.size(); ++i) {
		if (!enemies_[i]->Update()) {
			continue;
		}

		enemies_[pre++] = enemies_[i];
	}
	enemies_.resize(pre);
}

void MainGame::UpdateEnemyBullets() {
	int pre = 0;
	float px = player_.GetX();
	float py = player_.GetY();

	bool flap = false;
	for (size_t i = 0; i < enemy_bullets_.size(); ++i) {
		auto& b = enemy_bullets_[i];
		b.x += b.dx;
		b.y += b.dy;
		b.dx += b.ddx;
		b.dy += b.ddy;
		b.da += 1;

		if (b.x < -30 || b.y < -30 || b.x > W + 30 || b.y > H + 30) {
			continue;
		}

		if (b.mode == 0 || b.mode == 2) {			
			if (sqr(b.x - px) + sqr(b.y - py) <= 144) {
				HitPlayer();
				px = -1000;
				py = -1000;
				continue;
			}

			if (b.mode == 0) {
				flap |= CheckFlapCollision(&b);
			}
		}
		else {
			// check hit enemy
			bool skip = false;
			for (auto& e : enemies_) {
				if (!e->dead()) {
					if (sqr(b.x - e->GetX()) + sqr(b.y - e->GetY()) < sqr(e->GetSize() / 2 + 8)) {
						e->hit(6);
						multiple_ += 10;
						if (e->dead()) {
							score_ += multiple_;
						}
						skip = true;
						break;
					}
				}
			}
			if (skip) { continue; }
		}

		if (pre != i) {
			enemy_bullets_[pre++] = enemy_bullets_[i];
		}
		else pre++;
	}
	enemy_bullets_.resize(pre);

	if (flap) {
		ref_sound_.play();
	}
}

void MainGame::RenderEnemyBullets() {
	for (auto &b : enemy_bullets_) {
		enemy_bullet_.setOrigin(16, 16);
		enemy_bullet_.setPosition(b.x, b.y);
		enemy_bullet_.setTextureRect(sf::IntRect(32 * b.type, 0, 32, 32));

		if (b.type == 2) {
			enemy_bullet_.setRotation(atan2(b.dy, b.dx) * 180 / PI + 90);
		} else if (b.type == 0) {
			enemy_bullet_.setRotation(atan2(b.dy, b.dx) * 180 / PI - 90);
		}
		else {
			enemy_bullet_.setRotation(b.da);
		}

		if (b.mode == 0) {
			enemy_bullet_.setColor(sf::Color(160, 160, 255, 255));
		}
		else if (b.mode == 1) {
			enemy_bullet_.setColor(sf::Color(160, 255, 160, 255));
		}
		else {
			enemy_bullet_.setColor(sf::Color(255, 80, 80, 255));
		}
		window->draw(enemy_bullet_);
	}

	char buf[1024];
	sprintf_s(buf, "SCORE: %d", score_);
	tscore_.setString(buf);
	sprintf_s(buf, "x%d", multiple_);
	tmultiple_.setString(buf);
	std::string life_string;
	for (int i = 0; i < life_; ++i) {
		life_string += "@";
	}
	tlife_.setString(life_string);
	window->draw(tlife_);
	window->draw(tscore_);
	window->draw(tmultiple_);
}

void MainGame::UpdateEffects() {
	int pre = 0;
	for (size_t i = 0; i < effects_.size(); ++i) {
		if (!effects_[i]->Update()) {
			continue;
		}

		effects_[pre++] = effects_[i];
	}
	effects_.resize(pre);
}

void MainGame::RenderEffects() {
	for (auto& e : effects_) {
		e->Render();
	}
}

bool MainGame::CheckFlapCollision(EnemyBullet* e) {
	sf::Vector2<float> mid, dir;
	player_.GetFlapInfo(&mid, &dir);

	sf::Vector2<float> dd(e->x - mid.x, e->y - mid.y);
	float rsqr = (BL+16) * (BL + 16);

	// calc dis:
	float tsqr  = abs(dir.x * dd.x + dir.y * dd.y);
	tsqr *= tsqr;

	if (tsqr > rsqr) { return false; }

	//printf("%.2f %.2f\n", dd.x*dd.x + dd.y*dd.y, tsqr);
	if (dd.x*dd.x + dd.y*dd.y - tsqr > 225) { return false; }
	// hit
	e->mode = 1;
	e->ddx *= .1;
	e->ddy *= .1;
	// ref R = I - 2N(N*I)
	sf::Vector2<float> norm(dir.y, -dir.x);
	float scale = -2 * (norm.x * e->dx + norm.y* e->dy);
	e->dx += norm.x * scale;
	e->dy += norm.y * scale;

	multiple_ += 1;
	return true;
}