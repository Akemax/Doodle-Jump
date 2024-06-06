#pragma once
#include <Framework.h>

class Object
{
protected:
	Sprite* sprite = nullptr;					   // varibale for sprite
	float x, y;								       // object coordinates
	float originW, originH;				           // size for sprite

public:

	Object() { x = 0; y = 0; }
	Object(float _x, float _y) : x(_x), y(_y) { }
	~Object() { delete sprite; }

	virtual void Draw() const;					   // allow to draw sprite
	virtual void Update() = 0;
	bool LoadSprite(const char* imagePath);
};

