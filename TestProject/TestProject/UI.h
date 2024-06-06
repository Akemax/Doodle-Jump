#pragma once
#include "Object.h"
#include <unordered_map>
#include <string>

extern int windowWidth, windowHeight;

class UI :  public Object
{
	std::unordered_map<int, Sprite*> digitSprites;

public:
	UI(float x, float y);

	void Update() {}
	void DrawScore(int score);
	void DrawUI(int score, int numberPlatforms, int lifes);
};

