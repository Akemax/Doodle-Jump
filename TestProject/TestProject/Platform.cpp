#include "Platform.h"

Platform::Platform(float x, float y) : Object(x, y)
{
	 this->LoadSprite("../2022_win64/data/platform-static.png"); 
	 setSpriteSize(sprite, 70, 15);
	 height = 15;
	 width = 70;
	 moveLeftOrRight = (rand() % 2 == 0);
}

void Platform::Update()
{
	if (moveLeftOrRight == 1)
	{
		x += speed;
	}
	else
	{
		x -= speed;
	}
	
	if (x <= 0 || x + width >= windowWidth)
	{
		ChangeDirection();
	}

//	if (monsterExist)
//	{
	//	attachedMonster->SetX(this->x + attachedMonster->GetOffsetX());
	//	attachedMonster->SetY(this->y - attachedMonster->GetOffsetY());
	//	attachedMonster->Draw();
	//}

}
