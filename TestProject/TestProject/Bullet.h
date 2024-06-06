#pragma once
#include "Object.h"
#include <cmath>
#include <algorithm>

extern int windowWidth;
extern const int EDGE;

class Bullet :  public Object
{
	const char pathBullet[36] = "../2022_win64/data/black_bubble.png";
	float speed = 3.0f;
	double angle;

	bool outOfScreen = false;

public:

	Bullet(float x, float y, float mouseX, float mouseY);

	float GetX() { return x; }
	float GetY() { return y; }
	float GetWidth() { return originW; }
	float GetHeight() { return originH; }

	bool GetIsOutOfScreen() { return outOfScreen; }

	void Update();
};

