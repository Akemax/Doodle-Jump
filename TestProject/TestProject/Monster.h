#pragma once
#include "Object.h"
#include "Platform.h"
#include <iostream>

class Doodle;
class Bullet;

class Monster :  public Object
{
	bool monsterExist = true;
	bool isDead = false;

	int offsetMonsterX = -5;
	int offsetMonsterY = 50;

	Platform* platform;

public:
	Monster(float x, float y) : Object(x, y) { this->LoadSprite("../2022_win64/data/monsterBig.png"); originW = 80; originH = 50; }

	float GetX() { return x; }
	float GetY() { return y; }
	float GetHeight() { return originH; }
	float GetWidth() { return originW; }
	void SetX(float newX) { x = newX; }
	void SetY(float newY) { y = newY; }
	int GetOffsetX() { return offsetMonsterX; }
	int GetOffsetY() { return offsetMonsterY; }

	void SetMonsterExist(bool monsterExistNew) { monsterExist = monsterExistNew; }

	void CheckCollision(Doodle* doodle);
	void CheckCollision(Bullet* bullet);

	void AttachPlatform(Platform* platformNew) { platform = platformNew; }

	void Update();
	bool IsDead() { return isDead; }
};

