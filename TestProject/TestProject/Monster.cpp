#include "Monster.h"
#include "Doodle.h"

void Monster::CheckCollision(Doodle* doodle)
{
    int monsterLeft = x;
    int monsterRight = x + originW;
    int monsterTop = y;
    int monsterBottom = y + originH;;

    int doodleLeft = doodle->GetX();
    int doodleRight = doodle->GetX() + doodle->GetWidth();
    int doodleTop = doodle->GetY();
    int doodleBottom = doodle->GetY() + doodle->GetHeight();

    if (doodleRight >= monsterLeft && doodleLeft <= monsterRight &&
        doodleBottom >= monsterTop && doodleTop <= monsterBottom) 
    {
        if (doodle->GetIsFalling() == true)
        {
            isDead = true;
        }
        else
        {
            doodle->DoodleDead();
        }

    }
}

void Monster::CheckCollision(Bullet* bullet)
{
    int monsterLeft = x;
    int monsterRight = x + originW;
    int monsterTop = y;
    int monsterBottom = y + originH;;

    int bulletLeft = bullet->GetX();
    int bulletRight = bullet->GetX() + bullet->GetWidth();
    int bulletTop = bullet->GetY();
    int bulletBottom = bullet->GetY() + bullet->GetHeight();

    if (bulletRight >= monsterLeft && bulletLeft <= monsterRight &&
        bulletBottom >= monsterTop && bulletTop <= monsterBottom)
    {
        isDead = true;
    }
}

void Monster::Update()
{
    x = platform->GetX() + offsetMonsterX;
	y = platform->GetY() - offsetMonsterY;
	Draw();
}
