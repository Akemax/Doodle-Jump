#pragma once
#include <Framework.h>
#include "Object.h"
#include <stdlib.h>

extern int windowWidth;

class Platform : public Object
{
    int height, width;
    float speed = 0.1f;

    bool moveLeftOrRight;
    bool monsterExist;

   // Monster* attachedMonster;

public:

    Platform(float x, float y);

    float GetX() { return x; }
    float GetY() { return y; }
    void SetX(float newX) { x = newX; }
    void SetY(float newY) { y = newY; }

    int GetLeft() const { return x; }
    int GetRight() const { return x + width; }
    int GetTop() const { return y; }
    int GetBottom() const { return y + height; }
    void ChangeDirection() { moveLeftOrRight = !moveLeftOrRight; }
   // void AttachMonster(Monster* monster, bool IsMonsterExist) { attachedMonster = monster; monsterExist = IsMonsterExist;  }

	void Update();
};

