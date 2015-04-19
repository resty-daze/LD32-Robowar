#include "LevelDirector.h"
#include "MainGame.h"
#include "Routers.h"

LevelDirector::LevelDirector()
{
}


LevelDirector::~LevelDirector()
{
}

void LevelDirector::Init() {
	progress_ = 0;
	tick_ = 0;
}

void LevelDirector::Update() {
	tick_ += 1;
	switch (progress_) {
	case 0: // Part 1
		part1();
		break;
	case 1: // Part 2
		part2();
		break;
	case 2:
		part3();
		break;
	case 3:
		part4();
		break;
	case 4:
		part5();
		break;
	case 5:
		part6();
		break;
	default:
		if (tick_ >= 600) {
			game_->EndGame("All Clear!!!");
		}
	}
}

void LevelDirector::Render() {
	// level shall render nothing
}

#define T(tick, action) if (tick_ == tick) { action; }
void LevelDirector::part1() {
	T(120, CreateEnemy1(make_shared<SimpleRouter>(250.0, 180, 4, -10, 100)));
	T(160, CreateEnemy1(make_shared<SimpleRouter>(350.0, 240, 4, -10, 105)));
	T(185, CreateEnemy1(make_shared<SimpleRouter>(270.0, 190, 4, -10, 110)));
	T(200, CreateEnemy1(make_shared<SimpleRouter>(220.0, 210, 4, -10, 105)));
	T(220, CreateEnemy1(make_shared<SimpleRouter>(210.0, 200, 4, -10, 95)));

	T(370, CreateEnemy1(make_shared<SimpleRouter>(150.0, 190, 6, -10, 120)));
	T(373, CreateEnemy1(make_shared<SimpleRouter>(200.0, 200, 7, -10, 150)));
	T(376, CreateEnemy1(make_shared<SimpleRouter>(250.0, 210, 6, -10, 100)));
	T(377, CreateEnemy1(make_shared<SimpleRouter>(300.0, 220, 4, -10, 80)));

	T(510, CreateEnemy1(make_shared<SimpleRouter>(140.0, 220, 4, -10, 100)));
	T(515, CreateEnemy1(make_shared<SimpleRouter>(180.0, 200, 5, -10, 110)));
	T(520, CreateEnemy1(make_shared<SimpleRouter>(220.0, 180, 4, -10, 120)));
	T(525, CreateEnemy1(make_shared<SimpleRouter>(260.0, 160, 5, -10, 130)));
	T(530, CreateEnemy1(make_shared<SimpleRouter>(300.0, 140, 4, -10, 140)));
	T(535, CreateEnemy1(make_shared<SimpleRouter>(350.0, 120, 5, -10, 150)));

	T(700, CreateEnemy2(make_shared<SimpleRouter>(200.0, 600, 5, -10, 200)));

	T(890, CreateEnemy1(make_shared<SimpleRouter>(100.0, 160, 4, -10, 130)));
	T(895, CreateEnemy1(make_shared<SimpleRouter>(125.0, 140, 5, -10, 140)));
	T(900, CreateEnemy1(make_shared<SimpleRouter>(150.0, 140, 4, -10, 140)));
	T(910, CreateEnemy1(make_shared<SimpleRouter>(225.0, 120, 5, -10, 150)));
	T(915, CreateEnemy1(make_shared<SimpleRouter>(250.0, 120, 4, -10, 150)));

	T(900, CreateEnemy2(make_shared<SimpleRouter>(100.0, 600, 4, -10, 220)));
	T(900, CreateEnemy2(make_shared<SimpleRouter>(300.0, 600, 5, -10, 220)));

	T(1000, CreateEnemy1(make_shared<SimpleRouter>(100.0, 160, 4, -10, 130)));
	T(1020, CreateEnemy1(make_shared<SimpleRouter>(125.0, 140, 5, -10, 140)));
	T(1040, CreateEnemy1(make_shared<SimpleRouter>(150.0, 140, 4, -10, 140)));
	T(1060, CreateEnemy1(make_shared<SimpleRouter>(225.0, 120, 5, -10, 150)));
	T(1080, CreateEnemy1(make_shared<SimpleRouter>(250.0, 120, 4, -10, 150)));

	T(1100, tick_ = 0;  progress_ = 1);
}

void LevelDirector::part2() {
	T(1, printf("part 2\n"));
	T(100, CreateEnemy2(make_shared<SimpleRouter>(300.0, 600, 4, -10, 150)));
	T(200, CreateEnemy2(make_shared<SimpleRouter>(120.0, 600, 4, -10, 150)));
	T(240, CreateEnemy2(make_shared<SimpleRouter>(280.0, 600, 4, -10, 150)));
	T(450, CreateEnemy2(make_shared<SimpleRouter>(100.0, 600, 4, -10, 220)));
	T(450, CreateEnemy2(make_shared<SimpleRouter>(300.0, 600, 4, -10, 220)));
	int t = 0;
	for (int i = 150; i < 600; i += 30) {
		// float x, float y, float dx, float dy, float ddx, float ddy, int strong_fs
		t++;
		T(i, CreateEnemy1(make_shared<DirectRoute>(W + 40 + i % 21, i % 100 + 30, -5, 0, 0, -0.01, 100), t % 2 == 0));
	}

	T(600, CreateEnemy2(make_shared<SimpleRouter>(100.0, 450, 4, -10, 220)));
	T(600, CreateEnemy2(make_shared<SimpleRouter>(200.0, 450, 4, -10, 220)));
	T(600, CreateEnemy2(make_shared<SimpleRouter>(300.0, 450, 4, -10, 220)));

	T(900, CreateEnemy2(make_shared<SimpleRouter>(80.0, 450, 4, -10, 140)));
	T(910, CreateEnemy2(make_shared<SimpleRouter>(160.0, 450, 4, -10, 140)));
	T(920, CreateEnemy2(make_shared<SimpleRouter>(240.0, 450, 4, -10, 140)));
	T(930, CreateEnemy2(make_shared<SimpleRouter>(320.0, 450, 4, -10, 140)));

	T(1210, CreateEnemy2(make_shared<SimpleRouter>(80.0, 450, 4, -10, 140)));
	T(1200, CreateEnemy2(make_shared<SimpleRouter>(160.0, 450, 4, -10, 140)));
	T(1190, CreateEnemy2(make_shared<SimpleRouter>(240.0, 450, 4, -10, 140)));
	T(1180, CreateEnemy2(make_shared<SimpleRouter>(320.0, 450, 4, -10, 140)));


	for (int i = 1200; i < 1400; i += 30) {
		// float x, float y, float dx, float dy, float ddx, float ddy, int strong_fs
		t++;
		T(i, CreateEnemy1(make_shared<DirectRoute>(W + 40 + i % 21, i % 100 + 30, -5, 0, 0, -0.01, 100), t % 2 == 0));
	}
	T(1500, tick_ = 0; progress_ = 2);
}

void LevelDirector::part3() {
	T(1, printf("part 3\n"));
	if (tick_ == 150) {
		//float x, float y, int strong_frames;
		w_enemy_ = CreateEnemy4(make_shared<BigFlyerRouter>(200, -100, 180));
		return;
	}

	if (tick_ > 240 && !w_enemy_.lock()) {
		tick_ = 0;  progress_ = 3;
	}
}

void LevelDirector::part4() {
	T(1, printf("part 4\n"));

	int t = 0;
	for (int i = 150; i < 600; i += 15) {
		// float x, float y, float dx, float dy, float ddx, float ddy, int strong_fs
		t++;
		T(i, CreateEnemy1(make_shared<DirectRoute>(W + 40 + 5 * (i % 23), i % 100 + 30, -5, 0, 0, -0.01, 20), t % 2 == 0));
	}

	T(300, CreateEnemy2(make_shared<SimpleRouter>(280.0, 450, 4, -10, 120)));

	// float x, float dy, float a_scale, int strong_frames
	T(500, CreateEnemy3(make_shared<SnakeRouter1>(100, 400, -0.008, 180)));
	T(680, CreateEnemy3(make_shared<SnakeRouter1>(320, 250, 0.01, 180)));


	T(1600, CreateEnemy2(make_shared<SimpleRouter>(300.0, 450, 4, -10, 120)));
	T(1800, CreateEnemy3(make_shared<SnakeRouter1>(100, 100, -0.002, 180)));

	for (int i = 1800; i < 2100; i += 23) {
		// float x, float y, float dx, float dy, float ddx, float ddy, int strong_fs
		t++;
		T(i, CreateEnemy1(make_shared<DirectRoute>(W + 40 + 5 * (i % 23), i % 100 + 30, -5, 0, 0, -0.01, 20), t % 2 == 0));
	}

	T(2500, tick_ = 0; progress_ = 4);
}

void LevelDirector::part5() {
	T(1, printf("part 5\n"));

	if (tick_ == 50) {
		//float x, float y, int strong_frames;
		w_enemy_ = CreateEnemy4(make_shared<BigFlyerRouter>(200, -100, 180));
		return;
	}

	T(400, CreateEnemy3(make_shared<SnakeRouter1>(100, 300, -0.008, 180)));
	T(450, CreateEnemy3(make_shared<SnakeRouter1>(320, 250, 0.01, 180)));

	if (tick_ > 240 && !w_enemy_.lock()) {
		tick_ = 0;  progress_ = 5;
	}
}

void LevelDirector::part6() {
	T(1, printf("part 6\n"));
	T(300, game_->AddEffects(make_shared<WarningEffect>()));
	T(300, PlaySoundEffect(se::warn));

	if (tick_ == 900) {
		//float x, float y, int strong_frames;
		w_enemy_ = CreateBoss();
		return;
	}

	if (tick_ > 1200 && !w_enemy_.lock()) {
		tick_ = 0;  progress_ = 6;
		game_->StartFade();
	}
}


// ----------------- Enemies -------------------
class Enemy1Shooter : public Shooter {
public:
	explicit Enemy1Shooter(bool spec) {
		cool_ = 45;
		spec_ = spec;
	}

	void Update(float x, float y, MainGame* game) {
		if (cool_ == 0) {
			if (x > 5 && x < W && y > 5 && y < H - 100) {
				game->AddEnemyBullet(0, x - 7, y + 7, 0, 4, 0, 0, spec_);
				cool_ = 45;
			}
			else {
				cool_ = 30;
			}
		}
		else {
			cool_ -= 1;
		}
	}
private:
	int cool_;
	bool spec_;
};

std::vector<sf::IntRect> ani48{sf::IntRect(0, 0, 48, 48), sf::IntRect(0, 48, 48, 48)};
void LevelDirector::CreateEnemy1(shared_ptr<Router> router, bool spec) {
	game_->AddEnemy(make_shared<Enemy>(1, 48, tex::enemy1, ani48, router, make_shared<Enemy1Shooter>(spec)));
}

class Enemy2Shooter : public Shooter {
public:
	Enemy2Shooter() {
		cool_ = 20;
		cool2_ = 0;
		start_ = false;
		flap_ = true;
	}

	void Update(float x, float y, MainGame* game) {
		if (cool_ == 0) {
			if (!start_) {
				if (x > 5 && x < W && y > 5 && y < H - 100) {
					start_ = true;
					cool_ = 10;
					cool2_ = 15;
					scnt_ = 0;
				}
				else {
					cool_ = 20;
				}
			}
			else {
				cool_ = 40;
				int n = 12;
				for (int i = 0; i < n; ++i) {
					float angle = 2 * PI / n * i;
					float v = 2;
					float ca = cos(angle);
					float sa = sin(angle);
					game->AddEnemyBullet(1, x, y + 16, ca * v, sa * v);
				}
			}
		}
		else {
			cool_ -= 1;
		}

		if (start_) {
			if (cool2_ == 0) {
				float px, py;
				game->GetPlayerPos(&px, &py);
				float dx = px - (x - 10);
				float dy = py - (y + 16);
				float r = sqrt(dx * dx + dy * dy);
				float v = 3;
				if (!flap_) {
					v = 2;
				}
				game->AddEnemyBullet(0, x - 10, y + 16, dx / r * v, dy /r * v, 0, 0, !flap_);

				 dx = px - (x + 10);
				 dy = py - (y + 16);
				 r = sqrt(dx * dx + dy * dy);
				game->AddEnemyBullet(0, x + 10, y + 16, dx / r * v, dy / r * v, 0, 0, !flap_);

				cool2_ = 3;
				if (++scnt_ >= 5) {
					scnt_ = 0;
					cool2_ = 60 + flap_ * 25;
					flap_ = !flap_;
				}
			}
			else {
				cool2_ -= 1;
			}
		}
	}
private:
	int cool_;
	int cool2_;
	int scnt_;
	bool start_;
	bool flap_;
};

std::vector<sf::IntRect> ani64{ sf::IntRect(0, 0, 64, 64), sf::IntRect(0, 64, 64, 64) };
void LevelDirector::CreateEnemy2(shared_ptr<Router> router) {
	game_->AddEnemy(make_shared<Enemy>(20, 64, tex::enemy2, ani64, router, make_shared<Enemy2Shooter>()));
}


class BodyFollowRouter : public Router {
public:
	BodyFollowRouter(weak_ptr<Enemy> target, float dist) 
		: target_(target), dist_(dist) {
		first_ = true;
	}

	float GetX() const { return x_; }
	float GetY() const { return y_; }
	bool Strong() const { return true; }

	bool Update() {
		auto target = target_.lock();
		if (!target) {
			return false;
		}

		if (first_) {
			first_ = false;
			x_ = target->GetX();
			y_ = target->GetY(); 
			return true;
		}

		float tx = target->GetX();
		float ty = target->GetY();

		float target_dist = sqr(x_ - tx) + sqr(y_ - ty);
		if (target_dist < dist_ * dist_) {
			return true;
		}

		target_dist = sqrt(target_dist);
		// calc direction
		float dx = tx - x_;
		float dy = ty - y_;

		x_ += dx / target_dist * (target_dist - dist_);
		y_ += dy / target_dist * (target_dist - dist_);

		return true;
	}
private:
	bool first_;
	float x_, y_;
	weak_ptr<Enemy> target_;
	float dist_;
};
std::vector<sf::IntRect> bodyAni{ sf::IntRect(96, 0, 48, 48), sf::IntRect(96, 48, 48, 48), sf::IntRect(96 + 48, 0, 48, 48) };

class SnakeHeadShooter : public Shooter {
public:
	SnakeHeadShooter() {
		cd_ = 60;
		cnt_ = 0;
	}

	void Update(float x, float y, MainGame* game) {
		if (cd_ == 0) {
			cd_ = 20;
			if (++cnt_ == 3) {
				cd_ = 90;
				cnt_ = 0;
			}

			float angle = atan2(y - ly_, x - lx_);
			float v = 2.5;
			float ca = cos(angle);
			float sa = sin(angle);
			game->AddEnemyBullet(0, x, y, ca * v, sa * v, 0, 0, true);

			ca = cos(angle+1);
			sa = sin(angle+1);
			game->AddEnemyBullet(0, x, y, ca * v, sa * v, 0, 0, false);

			ca = cos(angle-1);
			sa = sin(angle-1);
			game->AddEnemyBullet(0, x, y, ca * v, sa * v, 0, 0, false);
		}
		else {
			cd_ -= 1;
		}
		lx_ = x;
		ly_ = y;
	}

private:
	int cd_;
	int cnt_;
	float lx_, ly_;
};

class SnakeBodyShooter : public Shooter {
public:
	SnakeBodyShooter() {
		cd_ = 60;
	}

	void Update(float x, float y, MainGame* game) {
		if (cd_ == 0) {
			cd_ = 60;
			float px, py;
			game->GetPlayerPos(&px, &py);
			float dx = px - x;
			float dy = py - y;
			float r = sqrt(dx * dx + dy * dy);
			float v = 1.2;
			game->AddEnemyBullet(2, x, y, dx / r * v, dy / r * v, dx / r * 0.03, dy / r * 0.03);
		} else {
			cd_ -= 1;
		}
	}
private:
	int cd_;
};


void LevelDirector::CreateEnemy3(shared_ptr<Router> router) {
	// Snake:
	// Head
	shared_ptr<Enemy> enemy = make_shared<Enemy>(60, 64, tex::enemy3, ani64, router, make_shared<SnakeHeadShooter>());
	game_->AddEnemy(enemy);
	// Body
	for (int i = 0; i < 6; ++i) {
		enemy = make_shared<Enemy>(30, 48, tex::enemy3, bodyAni, make_shared<BodyFollowRouter>(enemy, 50), make_shared<SnakeBodyShooter>());
		game_->AddEnemy(enemy);
	}
}

class Enemy4Shooter : public Shooter {
public:
	Enemy4Shooter() {
		stage_ = 0;
		cd_ = 0;
		dx_ = -20;
		ct1_ = ct2_ = 0;
	}

	void Update(float x, float y, MainGame* game) {
		switch (stage_) {
		case 0:
			if (y > 60) {
				stage_ = 1;
				cd_ = 30;
			}
			break;
		case 1:
			if (cd_ == 0) {
				int n = 4;
				for (int i = 0; i <= n; ++i) {
					float angle = PI / n * i;
					float v = 3;
					float ca = cos(angle);
					float sa = sin(angle);
					game->AddEnemyBullet(1, x + dx_, y + 40, ca * v, sa * v);
				}

				ct1_ = ct1_ + 1;
				if (ct1_ < 6) {
					cd_ = 4;
				}
				else {
					ct1_ = 0;
					ct2_++;
					dx_ = -dx_;
					if (ct2_ >= 4)  {
						stage_ = 2;
						cd_ = 15;
						ct2_ = 0;
						adt_ = 0;
						cd2_ = 30;
					}
					cd_ = 20;
				}
			}
			else {
				cd_ -= 1;
			}
			break;
		case 2:
			if (cd_ == 0) {
				int n = 12;
				for (int i = 0; i < n; ++i) {
					float angle = 2 * PI / n * i + adt_;
					float v = 1.5;
					float ca = cos(angle);
					float sa = sin(angle);
					game->AddEnemyBullet(1, x, y + 40, ca * v, sa * v, 0, 0, true);
				}

				adt_ += PI / n * 0.7;
				cd_ = 20;
			}
			else cd_ -= 1;

			if (cd2_ == 0) {
				int n = 8;
				for (int i = 0; i < n; ++i) {
					float angle = PI* 4 / 7 + PI / 8 / n * i;
					float v = 5;
					float ca = cos(angle);
					float sa = sin(angle);
					game->AddEnemyBullet(0, x - 30, y + 40, ca * v, sa * v, 0, 0);
					game->AddEnemyBullet(0, x + 30, y + 40, -ca * v, sa * v, 0, 0);
				}
				cd2_ = 10;
			}
			else {
				cd2_ -= 1;
			}
			break;
		}
	}

private:
	int stage_;
	int cd_;
	int cd2_;
	int dx_;
	int ct1_;
	int ct2_;
	float adt_;
};

std::vector<sf::IntRect> Ene4{ sf::IntRect(0, 0, 96, 96) };
shared_ptr<Enemy> LevelDirector::CreateEnemy4(shared_ptr<Router> router) {
	shared_ptr<Enemy> enemy = make_shared<Enemy>(300, 96, tex::enemy4, Ene4, router, make_shared<Enemy4Shooter>());
	game_->AddEnemy(enemy);
	return enemy;
}

class BossShooter : public Shooter {
public:
	BossShooter() {
		cd1_ = 60;
		mode_ = 0;
	}

	void Update(float x, float y, MainGame* game) {
		switch (mode_) {
		case 0:
			cd1_ -= 1;
			if (cd1_ <= 0) {
				mode_ = 1;
				cd1_ = 2;
				ct1_ = 0;
				ct2_ = 0;
				adt_ = 0;
				vadt_ = 0.08;
				v1_ = 3;
				cd2_ = 0;
				ct3_ = 0;
			}
			break;

		case 1:
			mode1(x, y, game); 
			break;

		case 2:
			mode2(x, y, game);
			break;
		}
	}

private:

	void mode1(float x, float y, MainGame* game) {
		if (cd1_ == 0) {
			int n = 5;
			for (int i = 0; i < n; ++i) {
				float angle = adt_ + 2 * PI / n * i;
				game->AddEnemyBullet(1, x, y, cos(angle) * v1_, sin(angle) * v1_, 0, 0, true);
			}
			cd1_ = 2;
			adt_ += vadt_;
			ct1_ += 1;
			v1_ += 0.1;
			if (ct1_ > 10) {
				ct1_ = 0;
				ct2_++;
				cd1_ = 25;
				adt_ += PI / 6;
				v1_ = 3;
				vadt_ = -vadt_;
			}
		}
		else {
			cd1_ -= 1;
		}

		if (ct2_ >= 8) {
			if (cd2_ == 0) {
				cd2_ = 4;
				ct3_ = ct3_ + 1;
				float sx = x;
				float sy = y + 40;
				if (ct3_ / 4 == 0) {
					sx -= 60;
				}
				else {
					sx += 60;
				}

				if (ct3_ == 8) {
					ct3_ = 0;
					cd2_ = 45;
				}

				float px, py;
				game->GetPlayerPos(&px, &py);
				float dangle = atan2(py - sy, px - sx);
				int n = 2;
				float v = 4.5;
				for (int i = -n; i <= n; ++i) {
					float angle = dangle + PI / 8 / (2 * n + 1) * i;
					game->AddEnemyBullet(0, sx, sy, cos(angle) * v, sin(angle) * v);
				}
			}
			else {
				cd2_ -= 1;
			}
		}

		if (ct2_ > 18) {
			mode_ = 2;
			cd1_ = 2;
			ct1_ = 0;
			ct2_ = 0;
			adt_ = 0;
			vadt_ = 0.08;
			v1_ = 3;
			cd2_ = 0;
			ct3_ = 0;
		}
	}

	void mode2(float x, float y, MainGame* game) {
		if (cd1_ == 0) {
			int n = 5;
			for (int i = 0; i < n; ++i) {
				float angle = adt_ + 2 * PI / n * i;
				game->AddEnemyBullet(1, x, y, cos(angle) * v1_, sin(angle) * v1_, 0, 0, false);
			}
			cd1_ = 2;
			adt_ += vadt_;
			ct1_ += 1;
			v1_ += 0.1;
			if (ct1_ > 10) {
				ct1_ = 0;
				ct2_++;
				cd1_ = 25;
				adt_ += PI / 6;
				v1_ = 3;
				vadt_ = -vadt_;
			}
		}
		else {
			cd1_ -= 1;
		}

		if (ct2_ >= 8) {
			if (cd2_ == 0) {
				cd2_ = 4;
				ct3_ = ct3_ + 1;
				float sx = x;
				float sy = y + 40;
				if (ct3_ / 4 == 0) {
					sx -= 60;
				}
				else {
					sx += 60;
				}

				if (ct3_ == 8) {
					ct3_ = 0;
					cd2_ = 45;
				}

				float px, py;
				game->GetPlayerPos(&px, &py);
				float dangle = atan2(py - sy, px - sx);
				int n = 2;
				float v = 4.5;
				for (int i = -n; i <= n; ++i) {
					float angle = dangle + PI / 8 / (2 * n + 1) * i;
					game->AddEnemyBullet(0, sx, sy, cos(angle) * v, sin(angle) * v, 0, 0, true);
				}
			}
			else {
				cd2_ -= 1;
			}
		}

		if (ct2_ > 12) {
			mode_ = 1;
			cd1_ = 2;
			ct1_ = 0;
			ct2_ = 0;
			adt_ = 0;
			vadt_ = 0.08;
			v1_ = 3;
			cd2_ = 0;
			ct3_ = 0;
		}
	}

	int mode_;
	int ct1_, ct2_, ct3_;
	int cd1_, cd2_, cd3_;
	float adt_, vadt_;
	float v1_;
};

std::vector<sf::IntRect> EneBoss{ sf::IntRect(0, 0, 160, 100) };
shared_ptr<Enemy> LevelDirector::CreateBoss() {
	shared_ptr<Enemy> enemy = make_shared<Enemy>(1200, 130, tex::ufo, EneBoss, make_shared<BigFlyerRouter>(200, -100, 300), make_shared<BossShooter>(), true);
	game_->AddEnemy(enemy);
	return enemy;
}