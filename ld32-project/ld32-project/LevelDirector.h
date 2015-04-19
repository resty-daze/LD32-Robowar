#pragma once

#include "Enemy.h"

class MainGame;
class LevelDirector
{
public:
	LevelDirector();
	~LevelDirector();

	void SetMainGame(MainGame* game) { game_ = game; }

	void Init();
	void Update();
	void Render();

private:
	void part1();
	void part2();
	void part3();
	void part4();
	void part5();
	void part6();
		

private:
	void CreateEnemy1(shared_ptr<Router> router, bool spec = false);
	void CreateEnemy2(shared_ptr<Router> router);
	void CreateEnemy3(shared_ptr<Router> router);
	shared_ptr<Enemy> CreateEnemy4(shared_ptr<Router> router);
	shared_ptr<Enemy> CreateBoss();

	MainGame* game_;
	int progress_;
	int tick_;

	weak_ptr<Enemy> w_enemy_;
};

