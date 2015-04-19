#pragma once
#include "Module.h"
#include "Player.h"
#include "LevelDirector.h"
#include "Enemy.h"
#include "Effects.h"
#include "BackGround.h"

class MainGame :
	public Module
{
public:
	MainGame();
	~MainGame();

	void Init();
	void Update();
	void Render();


public:
	void GetPlayerPos(float* x, float*y) {
		*x = player_.GetX();
		*y = player_.GetY();
	}

	void EndGame(const char* reason);
	void StartFade() { fading_ = true; }

public:
	void AddPlayerBullet(float x, float y);
	void AddEnemy(shared_ptr<Enemy> enemy);
	void AddEnemyBullet(int type, float x, float y, float dx, float dy, float ddx = 0, float ddy = 0, bool no_flap = false);
	void AddEffects(shared_ptr<Effect> effect);

	void HitPlayer();
private:
	void UpdatePlayerBullets();
	void UpdateEnemies();
	void UpdateEnemyBullets();
	void RenderEnemyBullets();
	void UpdateEffects();
	void RenderEffects();

	struct EnemyBullet {
		int type;
		int mode;
		float x, y;
		float dx, dy;
		float ddx, ddy;
		float da;
	};

	bool CheckFlapCollision(EnemyBullet* e);

	Player player_;
	std::vector<sf::Vector2<float>> player_bullets_;
	sf::Sprite player_bullet_;
	sf::Sound player_bullet_sound_;
	sf::Sound player_hit_sound_;
	sf::Sound ref_sound_;

	std::vector<shared_ptr<Enemy>> enemies_;

	std::vector<EnemyBullet> enemy_bullets_;
	sf::Sprite enemy_bullet_;

	std::vector<shared_ptr<Effect>> effects_;

	LevelDirector level_;

	int miss_count_;
	int life_;

	int score_, multiple_;
	sf::Text tscore_, tmultiple_, tlife_;

	sf::Clock clock_;
	sf::Music bgm_;

	BackGround bg_;
	bool fading_;
};
