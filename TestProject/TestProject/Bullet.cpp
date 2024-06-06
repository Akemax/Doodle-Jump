#include "Bullet.h"
#include <iostream>

Bullet::Bullet(float x, float y, float mouseX, float mouseY) : Object(x, y)
{
	 this->LoadSprite(pathBullet); 
	 angle = atan2(mouseY - y, mouseX - x);
     originH = 10;
     originW = 10;
}

void Bullet::Update()
{
	x += static_cast<float>(speed * cos(angle));
	y += static_cast<float>(speed * sin(angle));

    if (x <= EDGE)
    {
        x = windowWidth;
    }
    else if (x >= windowWidth)
    {
        x = EDGE;
    }
    if (y < 0)
    {
        outOfScreen = true;
    }
}
